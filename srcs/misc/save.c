#include "misc/save.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "logic/turret.h"

void	save_create(const char *path, const t_game* game)
{
	SDL_RWops*		file;
	int				tmp;
	t_bullet*		bullet;
	t_mob*			mob;
	t_solarpan*		panel;
	t_batbuilding*	bat;

	file = SDL_RWFromFile(path, "w");
	SDL_RWwrite(file, &(game->shouldsave), sizeof(bool), 1);
	SDL_RWwrite(file, game, sizeof(t_game), 1);
	SDL_RWwrite(file, game->player, sizeof(t_player), 1);
	tmp = 0;
	while (tmp < game->turretcount)
	{
		SDL_RWwrite(file, game->turrets, sizeof(t_turret), 1);
		SDL_RWwrite(file, &game->turrets[tmp].csm->buffer, sizeof(int), 1);
		tmp++;
	}
	tmp = solarpan_getcount(game->panels);
	SDL_RWwrite(file, &tmp, sizeof(int), 1);
	panel = game->panels;
	while (panel)
	{
		SDL_RWwrite(file, panel, sizeof(t_solarpan), 1);
		panel = panel->next;
	}
	tmp = batbuilding_getcount(game->bats);
	SDL_RWwrite(file, &tmp, sizeof(int), 1);
	bat = game->bats;
	while (bat)
	{
		SDL_RWwrite(file, bat, sizeof(t_batbuilding), 1);
		SDL_RWwrite(file, &bat->bat->level, sizeof(int), 1);
		bat = bat->next;
	}
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
	t_game*			game;
	t_game*			save;
	SDL_RWops*		file;
	t_bullet*		prevbullet;
	t_bullet*		firstbullet;
	t_solarpan*		prevsolar;
	t_solarpan*		firstsolar;
	t_mob*			prevmob;
	t_mob*			firstmob;
	int				i;
	int				j;
	bool			usesave;
	t_consumer*		csm;
	t_battery*		bat;
	t_generator*	gen;
	t_batbuilding*	prevbatbuild;
	t_batbuilding*	firstbatbuild;

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
	i = 0;
	while (i < game->turretcount)
	{
		SDL_RWread(file, game->turrets + i, sizeof(t_turret), 1);
		nrg_addconsumer(&game->nrgnet->consumers, game->turrets[i].x, game->turrets[i].y, TURRET_NRGCONS);
		csm = game->nrgnet->consumers;
		while (csm->next)
			csm = csm->next;
		SDL_RWread(file, &csm->buffer, sizeof(int), 1);
		(game->turrets + i)->csm = csm;
		i++;
	}
	SDL_RWread(file, &j, sizeof(int), 1);
	if (j > 0)
	{
		i = 1;
		prevsolar = malloc(sizeof(t_solarpan));
		SDL_RWread(file, prevsolar, sizeof(t_solarpan), 1);
		nrg_addgenerator(&game->nrgnet->generators, prevsolar->x, prevsolar->y);
		gen = game->nrgnet->generators;
		prevsolar->gen = gen;
		firstsolar = prevsolar;
		while (i < j)
		{
			prevsolar->next = malloc(sizeof(t_solarpan));
			SDL_RWread(file, prevsolar->next, sizeof(t_solarpan), 1);
			nrg_addgenerator(&game->nrgnet->generators, prevsolar->next->x, prevsolar->next->y);
			gen = gen->next;
			prevsolar->next->gen = gen;
			prevsolar = prevsolar->next;
			i++;
		}
		prevsolar->next = NULL;
		game->panels = firstsolar;
	}
	SDL_RWread(file, &j, sizeof(int), 1);
	if (j > 0)
	{
		i = 1;
		prevbatbuild = malloc(sizeof(t_batbuilding));
		SDL_RWread(file, prevbatbuild, sizeof(t_batbuilding), 1);
		nrg_addbattery(&game->nrgnet->batteries, prevbatbuild->x, prevbatbuild->y);
		bat = game->nrgnet->batteries;
		prevbatbuild->bat = bat;
		firstbatbuild = prevbatbuild;
		while (i < j)
		{
			prevbatbuild->next = malloc(sizeof(t_batbuilding));
			SDL_RWread(file, prevbatbuild->next, sizeof(t_batbuilding), 1);
			nrg_addbattery(&game->nrgnet->batteries, prevbatbuild->next->x, prevbatbuild->next->y);
			bat = bat->next;
			SDL_RWread(file, &bat->level, sizeof(int), 1);
			prevbatbuild->next->bat = bat;
			prevbatbuild = prevbatbuild->next;
			i++;
		}
		prevbatbuild->next = NULL;
		game->bats = firstbatbuild;
	}
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
		else
			game->mobs = NULL;
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
