#include <SDL2/SDL.h>
#include <SDL2/SDL2_rotozoom.h>
#include <GL/glew.h>

#include "assert.h"
#include "graphics/graphics.h"
#include "logic/player.h"
#include "misc/strjoin.h"
#include "graphics/sprite.h"
#include "logic/turret.h"
#include "graphics/drawgrid.h"
#include "logic/energybuildings.h"
#include <stdlib.h>
#include <stdio.h>
#include "misc/intersect.h"
#include "graphics/treerenderer.h"
#include "logic/game.h"
#include "events/events.h"
#include "graphics/ground_renderer.h"
#include "graphics/turret_renderer.h"
#include "graphics/ship_renderer.h"
#include "graphics/bats_renderer.h"
#include "graphics/mobrenderer.h"

static void		zoom(void* data)
{
	t_gfxcontext*	context;

	context = data;
	context->zoom *= 2.0;
}
static void		dezoom(void* data)
{
	t_gfxcontext*	context;

	context = data;
	context->zoom /= 2.0;
}

static void		gridswitch(void* data)
{
	t_gfxcontext* context;

	context = data;
	context->drawgrid = !context->drawgrid;
}

static void		registercallbacks(t_gfx* gfx, t_events* events)
{
	events_registercallback(events, events_callbackalloc("zoom", &gfx->context, zoom));
	events_registercallback(events, events_callbackalloc("dezoom", &gfx->context, dezoom));
	events_registercallback(events, events_callbackalloc("gridswitch", &gfx->context, gridswitch));
}

void			gfx_init(t_gfx *gfx, t_events* events)
{
	static t_sdlh sdlh;
	t_gfxcontext* context;

	gfx->sdlh = &sdlh;
	fonts_init();
	sdlh_init(gfx->sdlh);
	SDL_GL_CreateContext(gfx->sdlh->window);
	glewInit();
	context = gfxcontext_alloc(resparser_filetotree("res/sprites.res"));  //memleak
	gfx->context = *context;
	free(context);
	gfx->camx = 0;
	gfx->camy = 0;
	registercallbacks(gfx, events);
}

t_gfx*			gfx_alloc(t_events* events)
{
	t_gfx* gfx;

	gfx = (t_gfx*)malloc(sizeof(t_gfx));
	if (gfx != NULL)
	{
		gfx_init(gfx, events);
	}
	return (gfx);
}

void		gfx_update(t_gfx *gfx, const t_game* game)
{
	gfx->context.camx = game->player->x;
	gfx->context.camy = game->player->y;
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	gfx_renderground(&gfx->context);
	rendership(&gfx->context);
	renderturrets(game->turrets, game->turretcount, &gfx->context);
	renderbats(&gfx->context, game->panels, game->bats);
	renderplayer(game->player, &gfx->context);
	rendermobs(&gfx->context, game->mobs);
	SDL_GL_SwapWindow(gfx->sdlh->window);
}

void		gfx_cleanup(t_gfx* gfx)
{
	sdlh_cleanup(gfx->sdlh);
}
