#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#include "game.h"
#include "graphics.h"
#include "xp_sleep.h"

int		main(void)
{
	t_sdlh	sdlh;
	t_gfx	gfx;
	t_game	game;

	game_create(&game, &sdlh, &gfx);
	while(!sdlh.quitflag)
	{
		sdlh_handle_events(&sdlh);
		game_update(&game);
		gfx_update(&game);
		sdlh_update_window(&sdlh);
		Sleep(5);
	}
	sdlh_cleanup(&sdlh);
	return (0);
}
