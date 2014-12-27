#include <SDL2/SDL.h>

#include "graphics.h"
#include "player.h"
#include "strjoin.h"
#include "game.h"
#include "sprite.h"
#include "turret.h"

void		gfx_loadsprites(t_game *game)
{
	static t_playersprite playersprite;
	SDL_Surface	*image;
	int sw;
	int sh;

	game->gfx->playersprite = &playersprite;
	image = sdlh_loadandconvert("soldier.jpg");
	sw = image->w / 9;
	sh = 30;
	game->gfx->playersprite->right = sprite_create(image, 0, sh * 2, sw, sh);
	game->gfx->playersprite->left = sprite_create(image, 0, sh * 3, sw, sh);
	game->gfx->playersprite->back = sprite_create(image, 0,  sh, sw, sh);
	game->gfx->playersprite->front = sprite_create(image, 0, 0, sw, sh);
	image = sdlh_loadandconvert("turret.png");
	sw = image->w / 12;
	sh = image->h / 3;
	game->gfx->turretsprite = sprite_create(image, 0, 0, sw, sh);
}

static float	whitetoalpha(uint32_t color, const SDL_PixelFormat* format)
{
	uint8_t		r, g, b, a;
	float		alpha;

	SDL_GetRGBA(color, format, &r, &g, &b, &a);
	alpha = ((((float)r / 0xFF) + ((float)g / 0xFF) + ((float)b / 0xFF)) / 3);
	if (alpha > 0.6f)
		alpha = 1.f;
	else
		alpha = 0.f;
	return (alpha);
}

static void	mixsprite(t_game *game, t_sprite* sprite, int x, int y, int scale)
{
	uint32_t	color;
	float		alpha;
	int ix, iy;

	ix = 0;
	while (ix < (sprite->width * scale))
	{
		iy = 0;
		while (iy < (sprite->height * scale))
		{
			color = sprite_getpixel(sprite, ix / scale, iy / scale);
			alpha = whitetoalpha(color, sprite->surface->format);
			sdlh_mixpixel(game->sdlh, ix + x, iy - y, color, alpha);
			iy++;
		}
		ix++;
	}
}

void		gfx_drawbullet(t_bullet	*bullet, t_game *game)
{
	t_point orig;
	t_point dest;
	float		bullettrail = 4;

	orig.x = bullet->ox - ((bullet->dx - bullet->ox) / bullettrail);
	orig.y = bullet->oy - ((bullet->dy - bullet->oy) / bullettrail);
	orig.color = 0x0;
	dest.x = bullet->ox;
	dest.y = bullet->oy;
	dest.color = 0xFFFFFF;
	plot_line(orig, dest, game->sdlh);
	sdlh_putpixel(game->sdlh, bullet->ox, -bullet->oy, 0xFFFFFF);
}

void		gfx_update(t_game *game)
{
	unsigned int			x;
	unsigned int			y;
	t_sprite	*sprite;
	t_turret	*turret;
	t_bullet	*bullet;

	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			sdlh_putpixel(game->sdlh, x, y, 0x0);
			y++;
		}
		x++;
	}
	if (game->sdlh->mov_x > 0)
		sprite = game->gfx->playersprite->right;
	else if (game->sdlh->mov_x < 0)
		sprite = game->gfx->playersprite->left;
	else if (game->sdlh->mov_y > 0)
		sprite = game->gfx->playersprite->back;
	else if (game->sdlh->mov_y < 0)
		sprite = game->gfx->playersprite->front;
	else
		sprite = game->gfx->playersprite->front;
	x = 0;
	while (x < (unsigned int)game->turretcount)
	{
		turret = game->turrets + x;
		mixsprite(game, game->gfx->turretsprite, turret->x, turret->y, 1);
		x++;
	}
	mixsprite(game, sprite, game->player.x, game->player.y, 2);
	bullet = game->bullets;
	while (bullet)
	{
		gfx_drawbullet(bullet, game);
		bullet = bullet->next;
	}
}
