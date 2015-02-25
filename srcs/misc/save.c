#include "misc/save.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "logic/turret.h"

void	save_exportturrets(SDL_RWops* file, t_turret* turrets, int turretcount)
{
	int i;

	SDL_RWwrite(file, &turretcount, sizeof(int), 1);
	i = 0;
	while (i < turretcount)
	{
		SDL_RWwrite(file, turrets + i, sizeof(t_turret), 1);
		SDL_RWwrite(file, turrets[i].csm, sizeof(t_consumer), 1);
		i++;
	}
}

void	save_importturrets(SDL_RWops* file, t_turret** turrets, int* turretcount, t_nrgnetwork* nrgnet)
{
	int			i;
	t_turret	tmpturret;
	t_turret*	turret;
	t_consumer	tmpcsm;

	SDL_RWread(file, turretcount, sizeof(int), 1);
	i = 0;
	while (i < *turretcount)
	{
		SDL_RWread(file, &tmpturret, sizeof(t_turret), 1);
		SDL_RWread(file, &tmpcsm, sizeof(t_consumer), 1);
		turret_add(turrets, tmpturret.x, tmpturret.y, &i, 0, &nrgnet);
		turret = *turrets + i - 1;
		turret->angle = tmpturret.angle;
		turret->targetangle = tmpturret.targetangle;
		turret->lastshot = tmpturret.lastshot;
		turret->csm->buffer = tmpcsm.buffer;
	}
}

void	save_exportpanels(SDL_RWops* file, t_solarpan* panels, int panelcount)
{
	SDL_RWwrite(file, &panelcount, sizeof(int), 1);
	while (panels)
	{
		SDL_RWwrite(file, panels, sizeof(t_solarpan), 1);
		SDL_RWwrite(file, panels->gen, sizeof(t_generator), 1);
		panels = panels->next;
	}
}

void	save_importpanels(SDL_RWops* file, t_solarpan** panels, t_nrgnetwork* nrgnet)
{
	int			i;
	int			panelcount;
	t_solarpan	tmppan;
	t_generator	tmpgen;

	SDL_RWread(file, &panelcount, sizeof(int), 1);
	i = 0;
	while (i < panelcount)
	{
		SDL_RWread(file, &tmppan, sizeof(t_solarpan), 1);
		SDL_RWread(file, &tmpgen, sizeof(t_generator), 1);
		solarpan_add(panels, tmppan.x, tmppan.y, &nrgnet);
		i++;
	}
}

void	save_exportbats(SDL_RWops* file, t_batbuilding* batbuild, int batcount)
{
	SDL_RWwrite(file, &batcount, sizeof(int), 1);
	while (batbuild)
	{
		SDL_RWwrite(file, batbuild, sizeof(t_batbuilding), 1);
		SDL_RWwrite(file, batbuild->bat, sizeof(t_battery), 1);
		batbuild = batbuild->next;
	}
}

void	save_importbats(SDL_RWops* file, t_batbuilding** batbuild, t_nrgnetwork* nrgnet)
{
	int				i;
	int				batbuildcount;
	t_batbuilding	tmpbatbuild;
	t_battery		tmpbat;
	t_battery*		bat;

	SDL_RWread(file, &batbuildcount, sizeof(int), 1);
	bat = NULL;
	i = 0;
	while (i < batbuildcount)
	{
		SDL_RWread(file, &tmpbatbuild, sizeof(t_batbuilding), 1);
		SDL_RWread(file, &tmpbat, sizeof(t_battery), 1);
		batbuilding_add(batbuild, tmpbatbuild.x, tmpbatbuild.y, &nrgnet);
		if (bat == NULL)
			bat = nrgnet->batteries;
		else
			bat = bat->next;
		bat->level = tmpbat.level;
		i++;
	}
}

void	save_create(const char *path, const t_game* game)
{
	SDL_RWops*		file;
	int				tmp;
	t_bullet*		bullet;
	t_mob*			mob;

	file = SDL_RWFromFile(path, "w");
	SDL_RWwrite(file, &(game->shouldsave), sizeof(bool), 1);
	SDL_RWwrite(file, game, sizeof(t_game), 1);
	SDL_RWwrite(file, game->player, sizeof(t_player), 1);

	save_exportturrets(file, game->turrets, game->turretcount);
	save_exportpanels(file, game->panels, solarpan_getcount(game->panels));
	save_exportbats(file, game->bats, batbuilding_getcount(game->bats));

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
	t_mob*			prevmob;
	t_mob*			firstmob;
	int				i;
	int				j;
	bool			usesave;

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

	save_importturrets(file, &game->turrets, &game->turretcount, game->nrgnet);
	save_importpanels(file, &game->panels, game->nrgnet);
	save_importbats(file, &game->bats, game->nrgnet);

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
		firstmob=NULL;
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
