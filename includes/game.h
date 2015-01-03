#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "events.h"
#include "graphics.h"
#include "player.h"
#include "turret.h"
#include "bullet.h"
#include "energy.h"
#include "energybuildings.h"
#include "mob.h"

typedef struct		s_game
{
	bool			running;
	t_evnh*			events;
	t_gfx*			gfx;
	t_player*		player;
	t_turret*		turrets;
	t_bullet*		bullets;
	t_mob*			mobs;
	t_nrgnetwork*	nrgnet;
	t_solarpan*		panels;
	t_batbuilding*	bats;
	void			(*func)(void);
	int				turretcount;
	unsigned int	tickcount;
	int				lastspawn;
	int				spawnfreq;
	bool			shouldsave;
}					t_game;

t_game*		game_create(void);
void		game_loop(t_game* game);
void		game_destroy(t_game *game);

#endif
