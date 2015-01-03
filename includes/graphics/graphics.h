#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdbool.h>
#include "graphics/animation.h"
#include "misc/sdlhandler.h"
#include "graphics/playerrend.h"
#include "graphics/sprite.h"
#include "graphics/fonts.h"
#include "logic/turret.h"
#include "logic/bullet.h"
#include "logic/player.h"
#include "logic/mob.h"
#include "logic/energybuildings.h"

typedef struct	s_gfx
{
	t_sdlh				*sdlh;
	t_playersprite		*playersprite;
	t_sprite			*turretsprite;
	t_sprite			*soilsprite;
	t_sprite			*solarpansprite;
	t_sprite			*shipsprite;
	t_sprite			*batsprite;
	t_anim				*mobanim;
	int					camx;
	int					camy;
}				t_gfx;

void		gfx_init(t_gfx *gfx);
void		gfx_update(t_gfx *gfx, t_turret *turrets, int turretcount, t_bullet *bullets, t_player *player, t_mob* mobs, t_solarpan* panels, t_batbuilding* bats, int scale, int time, bool shoulddrawgrid, int energylvl);
void		gfx_cleanup(t_gfx* gfx);

#endif
