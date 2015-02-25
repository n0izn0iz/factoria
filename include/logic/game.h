#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "qtree/qtree.h"
#include "graphics/graphics.h"
#include "logic/player.h"
#include "logic/turret.h"
#include "logic/bullet.h"
#include "logic/energy.h"
#include "logic/energybuildings.h"
#include "logic/mob.h"
#include "events/events.h"
#include "misc/ticks.h"

typedef struct		s_game
{
	bool			running;
	t_ticker		ticker;
	t_events*		events;
	t_fpoint		worldsize;
	t_gfx*			gfx;
	t_player*		player;
	t_turret*		turrets;
	t_bullet*		bullets;
	t_mob*			mobs;
	t_nrgnetwork*	nrgnet;
	t_solarpan*		panels;
	t_batbuilding*	bats;
	t_qtree*		qtree;
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
