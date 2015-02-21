#include "logic/game.h"
#include "misc/xp_sleep.h"
#include <time.h>
#include "resparser/resparser.h"
#include <stdlib.h>
#include <SDL.h>
#include <stdio.h>
#include <math.h>
#include <stdio.h>

#define RAD(x) ((x) * M_PI / 180.f)
#define SPAWN_RADIUS 2000

static void	_addturret(void* data)
{
	t_game* game;

	game = data;
	turret_add(&(game->turrets), game->player->x, game->player->y, &(game->turretcount), game->tickcount, &game->nrgnet);
}

static void	_addsolar(void* data)
{
	t_game* game;

	game = data;
	solarpan_add(&game->panels, game->player->x, game->player->y, &game->nrgnet);
}

static void	_addbattery(void* data)
{
	t_game* game;

	game = data;
	batbuilding_add(&game->bats, game->player->x, game->player->y, &game->nrgnet);
}

static void	_heal(void* data)
{
	t_game* game;

	game = data;
	game->player->life = PLAYER_MAXLIFE;
}

static void	_spawnmob(void* data)
{
	t_game* game;

	game = data;
	mob_add(&(game->mobs), game->player->x, game->player->y, game->tickcount, game->qtree);
}

t_game*		game_create(void)
{
	t_game*				game;
	t_frect				worldbounds;
	t_resnode*			bindings;
	t_array*			callbacks;

	game = (t_game*)malloc(sizeof(t_game));
	if (game != NULL)
	{
		srand(time(NULL));
		game->tickcount = 0;
		bindings = resparser_filetotree("res/bindings.res");
		game->events = events_alloc(bindings);
		callbacks = array_create(10);
		array_append(callbacks, events_callbackalloc("addturret", game, _addturret));
		array_append(callbacks, events_callbackalloc("addsolar", game, _addsolar));
		array_append(callbacks, events_callbackalloc("addbattery", game, _addbattery));
		array_append(callbacks, events_callbackalloc("heal", game, _heal));
		array_append(callbacks, events_callbackalloc("spawnmob", game, _spawnmob));
		events_registercallbackarray(game->events, callbacks);
		array_destroy(callbacks);
		game->worldsize = fpoint_create(5000, 5000);
		worldbounds = frect_create(fpoint_create(0, 0), game->worldsize);
		game->qtree = qtree_alloc(&worldbounds);
		game->player = player_alloc(0, 0, 0);
		game->gfx = gfx_alloc();
		game->bullets = NULL;
		game->mobs = NULL;
		game->lastspawn = 0;
		game->spawnfreq = 100;
		game->shouldsave = true;
		game->nrgnet = NULL;
		game->panels = NULL;
		game->bats = NULL;
		game->running = true;
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
		mob_add(&(game->mobs), xoff, yoff, game->tickcount, game->qtree);
		game->lastspawn = game->tickcount;
		game->spawnfreq -= 1;
		game->spawnfreq = game->spawnfreq < 2 ? 2 : game->spawnfreq;
	}
}

void		game_loop(t_game *game)
{
	t_mob*		mob;

	events_update(game->events);
	if (game->events->quitflag == true)
		game->running = false;
	player_updatedirection(game->player, game->events->mov_x, game->events->mov_y);
	game_spawnmobs(game);
	nrg_updatenetworks(&game->nrgnet);
	if (game->player->life <= 0)
	{
		printf("Game over!\n");
		game->shouldsave = false;
		game->running = false;
	}
	mob = game->mobs;
	while (mob)
	{
		turret_inrange(&(game->turrets), &(game->bullets), mob->x, mob->y, game->tickcount, game->turretcount);
		mob = mob->next;
	}
	bullet_update(&(game->bullets), game->player, game->mobs);
	mob_update(&(game->mobs), game->player, game->tickcount, game->qtree);
	gfx_update(game->gfx, game);
	game->tickcount += 1;
}

void		game_destroy(t_game *game)
{
	gfx_cleanup(game->gfx);
	bullet_destroy(game->bullets);
	mob_destroy(game->mobs, game->qtree);
	free(game->turrets);
	free(game->events);
	free(game->player);
	free(game);
}
