#ifndef PLAYERREND_H
# define PLAYERREND_H

#include "graphics/sprite.h"
#include "logic/player.h"
#include "graphics/gfxcontext.h"

typedef struct	s_playersprite
{
	t_sprite *front;
	t_sprite *back;
	t_sprite *right;
	t_sprite *left;
}				t_playersprite;

void			renderplayer(t_player* player, t_gfxcontext* context);

#endif
