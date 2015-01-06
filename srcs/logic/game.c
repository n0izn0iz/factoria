#include "logic/game.h"
#include "misc/events.h"
#include "misc/xp_sleep.h"
#include <time.h>
#include <stdlib.h>
#include <SDL.h>
#include <stdio.h>
#include <math.h>

#define RAD(x) ((x) * M_PI / 180.f)
#define SPAWN_RADIUS 2000

t_game*		game_create(void)
{
	t_game*			game;
	static t_gfx	gfx;

	game = malloc(sizeof(t_game));
	if (game != NULL)
	{
		game->gfx = &gfx;
		game->player = malloc(sizeof(t_player));
		gfx_init(&gfx);
		game->events = events_create();
		game->player->x = 0;
		game->player->y = 0;
		game->player->life = PLAYER_MAXLIFE;
		game->turretcount = 0;
		game->tickcount = 0;
		game->bullets = NULL;
		game->mobs = NULL;
		game->running = true;
		game->lastspawn = 0;
		game->spawnfreq = 100;
		game->shouldsave = true;
		game->nrgnet = NULL;
		nrg_addnetwork(&game->nrgnet, NULL, NULL, NULL);
		game->panels = NULL;
		game->bats = NULL;
		srand(time(NULL));
		game->player->score = 0;
	}
	return (game);
}

static void	game_spawnmobs(t_game *game)
{
	int angle;
	int xoff;
	int yoff;

	if (game->lastspawn + game->spawnfreq < (int)game->tickcount)
	{
		angle = rand() % 360;
		xoff = SPAWN_RADIUS * cos(RAD(angle)) + game->player->x;
		yoff = SPAWN_RADIUS * sin(RAD(angle)) + game->player->y;
		mob_add(&(game->mobs), xoff, yoff, game->tickcount);
		game->lastspawn = game->tickcount;
		game->spawnfreq -= 1;
		game->spawnfreq = game->spawnfreq < 2 ? 2 : game->spawnfreq;
	}
}

void		game_loop(t_game *game)
{
	int			playerx;
	int			playery;
	t_mob*		mob;

	events_update(game->events);
	if (game->events->quitflag == true)
		game->running = false;
	player_updatedirection(game->player, game->events->mov_x, game->events->mov_y);
	playerx = game->player->x;
	playery = game->player->y;
	game_spawnmobs(game);
	if (game->events->solarpanelflag == true)
	{
		solarpan_add(&game->panels, playerx, playery, game->nrgnet);
		game->events->solarpanelflag = false;
	}
	if (game->events->batteryflag == true)
	{
		batbuilding_add(&game->bats, playerx, playery, game->nrgnet);
		game->events->batteryflag = false;
	}
	nrg_updatenetwork(&game->nrgnet);
	if (game->events->spawnmobflag == true)
	{
		mob_add(&(game->mobs), playerx, playery, game->tickcount);
		game->events->spawnmobflag = false;
	}
	if (game->events->healflag == true)
	{
		game->player->life = PLAYER_MAXLIFE;
		game->events->healflag = false;
	}
	if (game->player->life <= 0)
	{
		printf("Game over!\n");
		game->shouldsave = false;
		game->running = false;
	}
	if (game->events->turretflag == true)
	{
		turret_add(&(game->turrets), playerx, playery, &(game->turretcount), game->tickcount, game->nrgnet);
		game->events->turretflag = false;
	}
	mob = game->mobs;
	while (mob)
	{
		turret_inrange(&(game->turrets), &(game->bullets), mob->x, mob->y, game->tickcount, game->turretcount);
		mob = mob->next;
	}
	bullet_update(&(game->bullets), game->player, game->mobs);
	mob_update(&(game->mobs), game->player, game->tickcount);
	gfx_update(game->gfx, game->turrets, game->turretcount, game->bullets, game->player, game->mobs, game->panels, game->bats, game->events->scale, game->tickcount, game->events->drawgrid, game->nrgnet->capacity);
	game->tickcount += 1;
}

void		game_destroy(t_game *game)
{
	gfx_cleanup(game->gfx);
	bullet_destroy(game->bullets);
	mob_destroy(game->mobs);
	free(game->turrets);
	free(game->events);
	free(game->player);
	free(game);
}
