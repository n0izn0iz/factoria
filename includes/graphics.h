#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "playerrend.h"

struct s_game;

typedef struct	s_gfx
{
	t_playersprite		*playersprite;
	t_sprite			*turretsprite;
}				t_gfx;

void			gfx_update(struct s_game *game);
void			gfx_loadsprites(struct s_game *game);

#endif
