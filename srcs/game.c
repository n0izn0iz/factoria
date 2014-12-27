#include <stdlib.h>
#include <stdbool.h>

#include "game.h"
#include "graphics.h"
#include "turret.h"

void	game_create(t_game *game, t_sdlh *sdlh, t_gfx *gfx)
{
	game->sdlh = sdlh;
	game->gfx = gfx;
	sdlh_init(sdlh);
	gfx_loadsprites(game);
	game->player.x = 0;
	game->player.y = 0;
	game->turretcount = 0;
	game->tickcount = 0;
	game->bullets = NULL;
}

void	game_update(t_game *game)
{
	int			playerx;
	int			playery;

	playerx = game->player.x;
	playery = game->player.y;
	if (game->sdlh->turretflag == true)
	{
		turret_add(&(game->turrets), playerx, playery, &(game->turretcount), game->tickcount);
		printf("Added turret at: x%i y%i\n", playerx, playery);
		game->sdlh->turretflag = false;
	}
	turret_inrange(&(game->turrets), &(game->bullets), playerx, playery, game->tickcount, game->turretcount);
	bullet_update(&(game->bullets));
	game->player.x += game->sdlh->mov_x;
	game->player.y += game->sdlh->mov_y;
	game->tickcount += 1;
}
