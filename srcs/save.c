#include "save.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "turret.h"

void	save_create(const char *path, const t_game* game)
{
	SDL_RWops*	file;
	int			tmp;
	t_bullet*	bullet;
	t_mob*		mob;

	file = SDL_RWFromFile(path, "w");
	SDL_RWwrite(file, &(game->shouldsave), sizeof(bool), 1);
	SDL_RWwrite(file, game, sizeof(t_game), 1);
	SDL_RWwrite(file, game->player, sizeof(t_player), 1);
	SDL_RWwrite(file, game->turrets, sizeof(t_turret), game->turretcount);
	tmp = bullet_getcount(game->bullets);
	SDL_RWwrite(file, &tmp, sizeof(int), 1);
	bullet = game->bullets;
	while (bullet)
	{
		SDL_RWwrite(file, bullet, sizeof(t_bullet), 1);
		bullet = bullet->next;
	}
	tmp = mob_getcount(game->mobs);
	SDL_RWwrite(file, &tmp, sizeof(int), 1);
	mob = game->mobs;
	while (mob)
	{
		SDL_RWwrite(file, mob, sizeof(t_mob), 1);
		mob = mob->next;
	}
	SDL_RWclose(file);
}

t_game*	save_load(const char *path, bool force, bool donew)
{
	t_game*		game;
	t_game*		save;
	SDL_RWops*	file;
	t_bullet*	prevbullet;
	t_bullet*	firstbullet;
	t_mob*		prevmob;
	t_mob*		firstmob;
	int			i;
	int			j;
	bool		usesave;

	file = SDL_RWFromFile(path, "r");
	game = game_create();
	if (file == NULL)
		return (game);
	SDL_RWread(file, &usesave, sizeof(bool), 1);
	if (force)
		usesave = true;
	if (!usesave || donew)
		return (game);
	save = malloc(sizeof(t_game));
	SDL_RWread(file, save, sizeof(t_game), 1);
	SDL_RWread(file, game->player, sizeof(t_player), 1);
	game->turretcount = save->turretcount;
	game->turrets = malloc(sizeof(t_turret) * (game->turretcount / EXPAND_SIZE + 1) * EXPAND_SIZE);
	SDL_RWread(file, game->turrets, sizeof(t_turret), game->turretcount);
	SDL_RWread(file, &j, sizeof(int), 1);
	if (j > 0)
	{
		i = 1;
		prevbullet = malloc(sizeof(t_bullet));
		SDL_RWread(file, prevbullet, sizeof(t_bullet), 1);
		firstbullet = prevbullet;
		while (i < j)
		{
			prevbullet->next = malloc(sizeof(t_bullet));
			SDL_RWread(file, prevbullet->next, sizeof(t_bullet), 1);
			prevbullet = prevbullet->next;
			i++;
		}
		prevbullet->next = NULL;
		game->bullets = firstbullet;
	}
	else
		game->bullets = NULL;
	if (force == false)
	{
		SDL_RWread(file, &j, sizeof(int), 1);
		if (j > 0)
		{
			i = 1;
			prevmob = malloc(sizeof(t_mob));
			SDL_RWread(file, prevmob, sizeof(t_mob), 1);
			firstmob = prevmob;
			while (i < j)
			{
				prevmob->next = malloc(sizeof(t_mob));
				SDL_RWread(file, prevmob->next, sizeof(t_mob), 1);
				prevmob = prevmob->next;
				i++;
			}
			prevmob->next = NULL;
		}
		game->mobs = firstmob;
	}
	else
	{
		game->player->life = PLAYER_MAXLIFE;
		game->mobs = NULL;
	}
	game->lastspawn = save->lastspawn;
	game->tickcount = save->tickcount;
	game->spawnfreq = save->spawnfreq;
	SDL_RWclose(file);
	free(save);
	return (game);
}
