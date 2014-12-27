#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include "sdlhandler.h"
#include "player.h"
#include "graphics.h"
#include "turret.h"
#include "bullet.h"

typedef struct		s_point
{
	int x;
	int y;
	int z;
	int color;
}					t_point;

typedef struct		s_game
{
	bool			running;
	t_sdlh		*sdlh;
	t_gfx		*gfx;
	t_player	player;
	t_turret	*turrets;
	t_bullet	*bullets;
	int			turretcount;
	unsigned int	tickcount;
}					t_game;

void	game_create(t_game *game, t_sdlh *sdlh, t_gfx *gfx);
void	game_update(t_game *game);

#endif
