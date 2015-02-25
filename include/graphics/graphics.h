#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdbool.h>
#include "misc/sdlhandler.h"
#include "graphics/playerrend.h"
#include "graphics/sprite.h"
#include "graphics/fonts.h"
#include "logic/turret.h"
#include "logic/bullet.h"
#include "logic/player.h"
#include "logic/mob.h"
#include "logic/energybuildings.h"
#include "graphics/gui.h"
#include "resparser/resparser.h"
#include "graphics/gfxcontext.h"

typedef struct s_game t_game;

typedef struct	s_gfx
{
	t_sdlh				*sdlh;
	t_gfxcontext		context;
	t_gui*				gui;
	int					camx;
	int					camy;
}				t_gfx;

t_gfx*		gfx_alloc();
void		gfx_update(t_gfx *gfx, const struct s_game* game);
void		gfx_cleanup(t_gfx* gfx);
void		gfx_mixsprite(SDL_Surface *dest, t_sprite* sprite, int x, int y, double scale);
void		gfx_drawgui(SDL_Surface* surface, t_gui* gui);
void		plot_worldline(SDL_Surface* surface, t_fpoint apt, uint32_t cola, t_fpoint bpt, uint32_t colb, t_fpoint campos, double zoom, t_ipoint winfalfsize);

#endif
