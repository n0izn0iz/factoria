#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdbool.h>
#include "animation.h"
#include "sdlhandler.h"
#include "playerrend.h"
#include "sprite.h"
#include "turret.h"
#include "bullet.h"
#include "player.h"
#include "mob.h"

typedef struct	s_gfx
{
	t_sdlh				*sdlh;
	t_playersprite		*playersprite;
	t_sprite			*turretsprite;
	t_sprite			*soilsprite;
	t_anim				*mobanim;
	int					camx;
	int					camy;
}				t_gfx;

void		gfx_init(t_gfx *gfx);
void		gfx_update(t_gfx *gfx, t_turret *turrets, int turretcount, t_bullet *bullets, t_player *player, t_mob* mobs, int scale, int time, bool drawgrid);
void		gfx_cleanup(t_gfx* gfx);

#endif
