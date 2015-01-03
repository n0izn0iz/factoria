#include <SDL2/SDL.h>
#include <SDL2/SDL2_rotozoom.h>

#include "assert.h"
#include "graphics/graphics.h"
#include "logic/player.h"
#include "misc/strjoin.h"
#include "graphics/sprite.h"
#include "logic/turret.h"
#include "graphics/drawgrid.h"
#include "logic/energybuildings.h"
#include <stdlib.h>

#define LIFEBAR_WIDTH 5

static t_anim*		create_mob_anim(SDL_Surface* surface)
{
	t_anim*		anim;
	t_sprite*	sprite;
	unsigned int			i;
	int			sw, sh;

	sw = sh = 48;
	anim = malloc(sizeof(t_anim));
	anim->framecount = 8;
	anim->framearray = malloc(sizeof(t_sprite) * 8);
	i = 0;
	while (i < anim->framecount)
	{
		sprite = anim->framearray + i;
		sprite->surface = surface;
		sprite->rect.x = sw * (i % 4);
		sprite->rect.y = sh * (i / 4);
		sprite->rect.w = sw;
		sprite->rect.h = sh;
		sprite->ox = sw / 2;
		sprite->oy = sh / 2;
		i++;
	}
	return (anim);
}

static void			gfx_loadsprites(t_gfx *gfx)
{
	static t_playersprite playersprite;
	SDL_Surface	*image;
	int sw;
	int sh;

	gfx->playersprite = &playersprite;
	image = sdlh_loadandconvert("soldier.png");
	sw = image->w / 9;
	sh = 30;
	gfx->playersprite->right = sprite_create(image, 0, sh * 2, sw / 2, sh / 2, sw, sh);
	gfx->playersprite->left = sprite_create(image, 0, sh * 3, sw / 2, sh / 2, sw, sh);
	gfx->playersprite->back = sprite_create(image, 0,  sh, sw / 2, sh / 2, sw, sh);
	gfx->playersprite->front = sprite_create(image, 0, 0, sw / 2, sh / 2, sw, sh);
	image = sdlh_loadandconvert("alien.png");
	sw = 48;
	sh = 48;
	gfx->mobanim = create_mob_anim(image);
	gfx->mobanim->surface = image;
	image = sdlh_loadandconvert("turret.png");
	sw = 38;
	sh = 38;
	gfx->turretsprite = sprite_create(image, 0, 0, sw / 2, sh / 2, sw, sh);
	image = sdlh_loadandconvert("soil3.png");
	sw = image->w;
	sh = image->h;
	gfx->soilsprite = sprite_create(image, 0, 0, sw / 2, sh / 2, sw, sh);
	image = sdlh_loadandconvert("ship.png");
	sw = image->w;
	sh = image->h;
	gfx->shipsprite = sprite_create(image, 0, 0, sw / 2, sh / 2, sw, sh);
	image = sdlh_loadandconvert("solarpan.png");
	sw = image->w;
	sh = image->h;
	gfx->solarpansprite = sprite_create(image, 0, 0, sw / 2, sh / 2, sw, sh);
	image = sdlh_loadandconvert("generator.png");
	sw = image->w;
	sh = image->h;
	gfx->batsprite = sprite_create(image, 0, 0, sw / 2, sh / 2, sw, sh);
}

static void		mixsprite(SDL_Surface *dest, t_sprite* sprite, int x, int y, double scale)
{
	SDL_Rect destrect;

	destrect.x = x - (sprite->ox / scale);
	destrect.y = -y - (sprite->oy / scale);
	destrect.w = sprite->rect.w / scale;
	destrect.h = sprite->rect.h / scale;
	if (scale > 1)
		SDL_BlitScaled(sprite->surface, &(sprite->rect), dest, &destrect);
	else
		SDL_BlitSurface(sprite->surface, &(sprite->rect), dest, &destrect);
}

static void			gfx_drawlife(t_sdlh* sdlh, int x, int y, int scale, int width, int life, int maxlife)
{
	int i;
	int j;

	i = x;
	while (i < x + maxlife * scale / 2)
	{
		j = y;
		while (j < y + width)
		{
			if (width > 2 && (i == x || j == y || j == y + width - 1 || i == x + maxlife * scale / 2 - 1))
				sdlh_putpixel(sdlh, i, -j, 0x000000);
			else if (i - x < life * scale / 2)
				sdlh_putpixel(sdlh, i, -j, 0x00FF00);
			else
				sdlh_putpixel(sdlh, i, -j, 0xFF0000);
			j++;
		}
		i++;
	}
}

static void			gfx_drawenergy(t_sdlh* sdlh, int nrglvl, int x, int y, int scale, int width)
{
	int i;
	int j;
	i = x;
	while (i < x + width)
	{
		j = y;
		while (j < y + nrglvl * scale / 100)
		{
			if (width > 2 && (i == x || j == y || i == x + width - 1 || j == y + nrglvl * scale / 100 - 1))
				sdlh_putpixel(sdlh, i, -j, 0x000000);
			else if (nrglvl >= 5000)
				sdlh_putpixel(sdlh, i, -j, 0x5555FF);
			else
				sdlh_putpixel(sdlh, i, -j, 0xFF0000);
			j++;
		}
		i++;
	}
}

static void			gfx_drawsoil(t_sprite* soilsprite, SDL_Surface* dest, int winx, int winy, int scale)
{
	int numw, numh;
	int x, y;

	numw = dest->w * scale / soilsprite->rect.w;
	numh = dest->h * scale / soilsprite->rect.h;
	x = 0;
	while (x <= numw)
	{
		y = 0;
		while (y <= numh)
		{
			mixsprite(dest, soilsprite, x * soilsprite->rect.w / scale - (winx % (soilsprite->rect.w / scale) + (soilsprite->ox / scale)), y * soilsprite->rect.h / scale - (WIN_HEIGHT + winy % (soilsprite->rect.h / scale) - (soilsprite->oy / scale)), scale);
			y++;
		}
		x++;
	}
}

static void			gfx_drawbullet(t_bullet	*bullet, t_sdlh *sdlh, int scale, int winx, int winy)
{
	t_point orig;
	t_point dest;
	float		bullettrail = 4 * scale;

	orig.x = bullet->ox / scale - winx - ((bullet->dx - bullet->ox) / scale / bullettrail);
	orig.y = bullet->oy / scale - winy - ((bullet->dy - bullet->oy) / scale / bullettrail);
	orig.color = 0xFFEE55;
	dest.x = bullet->ox / scale - winx;
	dest.y = bullet->oy / scale - winy;
	dest.color = 0x0;
	plot_line(orig, dest, sdlh);
	orig.x += 1;
	orig.y += 1;
	dest.x += 1;
	dest.y += 1;
	plot_line(orig, dest, sdlh);
	sdlh_putpixel(sdlh, dest.x, -dest.y, 0xFFFFFF);
}

static void		gfx_drawmobs(t_sdlh* sdlh, t_anim* anim, t_mob* mobs, int scale, int winx, int winy, int time)
{
	SDL_Surface*	tmpsurface;
	SDL_Surface*	rotsurface;
	t_sprite*		rotsprite;
	t_sprite*		mobsprite;

	while (mobs)
	{
		mobsprite = anim->framearray + anim_frameindex(anim, time, 5);
		tmpsurface = SDL_CreateRGBSurface(0, mobsprite->rect.w, mobsprite->rect.h, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
		SDL_BlitSurface(mobsprite->surface, &(mobsprite->rect), tmpsurface, NULL);
		rotsurface = rotozoomSurface(tmpsurface, mobs->angle / M_PI * 180.0, 1.0, 1);
		SDL_FreeSurface(tmpsurface);
		rotsprite = sprite_create(rotsurface, 0, 0, rotsurface->w / 2, rotsurface->h / 2, rotsurface->w, rotsurface->h);
		mixsprite(sdlh->surface, rotsprite, mobs->x / scale - winx, mobs->y / scale - winy, scale);
		SDL_FreeSurface(rotsprite->surface);
		free(rotsprite);
		if (mobs->life < MOB_MAXLIFE)
			gfx_drawlife(sdlh, mobs->x / scale - winx - (MOB_MAXLIFE / 4), \
			mobs->y / scale - winy + mobsprite->oy - mobsprite->rect.h, 1, \
			LIFEBAR_WIDTH / scale, mobs->life / scale, MOB_MAXLIFE / scale);
		mobs = mobs->next;
	}
}

static void		gfx_drawturret(t_sdlh* sdlh, t_sprite* sprite, t_turret* turret, int scale, int winx, int winy)
{
	SDL_Surface*	rotsurface;
	t_sprite*		rotsprite;

	rotsurface = rotozoomSurface(sprite->surface, turret->angle / M_PI * 180.0 + 180.0, 1.0, 1);
	rotsprite = sprite_create(rotsurface, 0, 0, rotsurface->w / 2, rotsurface->h / 2, rotsurface->w, rotsurface->h);
	mixsprite(sdlh->surface, rotsprite, turret->x / scale - winx, turret->y / scale - winy, scale);
	SDL_FreeSurface(rotsurface);
	free(rotsprite);
}

void			gfx_init(t_gfx *gfx)
{
	static t_sdlh sdlh;

	gfx->sdlh = &sdlh;
	fonts_init();
	sdlh_init(gfx->sdlh);
	gfx_loadsprites(gfx);
	gfx->camx = 0;
	gfx->camy = 0;
}

void		gfx_update(t_gfx *gfx, t_turret *turrets, int turretcount, t_bullet *bullets, t_player *player, t_mob* mobs, t_solarpan* panels, t_batbuilding* bats, int scale, int time, bool shoulddrawgrid, int energylvl)
{
	unsigned int			x;
	unsigned int			y;
	t_sprite	*sprite;
	t_turret	*turret;
	t_bullet	*bullet;
	int winx;
	int winy;
	SDL_Surface*	testtext;
	static double fps = 0;
	static uint32_t lastframe = 0;
	char	str[20];

	gfx->camx = player->x / scale;
	gfx->camy = player->y / scale;
	winx = gfx->camx - (WIN_WIDTH / 2);
	winy = gfx->camy + (WIN_HEIGHT / 2);
	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			sdlh_putpixel(gfx->sdlh, x, y, 0x0);
			y++;
		}
		x++;
	}
	if (player->direction == DIR_EAST)
		sprite = gfx->playersprite->right;
	else if (player->direction == DIR_WEST)
		sprite = gfx->playersprite->left;
	else if (player->direction == DIR_NORTH)
		sprite = gfx->playersprite->back;
	else if (player->direction == DIR_SOUTH)
		sprite = gfx->playersprite->front;
	else
		sprite = gfx->playersprite->front;
	gfx_drawsoil(gfx->soilsprite, gfx->sdlh->surface, winx, winy, scale);
	mixsprite(gfx->sdlh->surface, gfx->shipsprite, -winx, -winy, scale);
	x = 0;
	while (x < (unsigned int)turretcount)
	{
		turret = turrets + x;
		gfx_drawturret(gfx->sdlh, gfx->turretsprite, turret, scale, winx, winy);
		x++;
	}
	while (panels)
	{
		mixsprite(gfx->sdlh->surface, gfx->solarpansprite, panels->x / scale - winx, panels->y / scale - winy, scale);
		panels = panels->next;
	}
	while (bats)
	{
		mixsprite(gfx->sdlh->surface, gfx->batsprite, bats->x / scale - winx, bats->y / scale - winy, scale);
		bats = bats->next;
	}
	gfx_drawmobs(gfx->sdlh, gfx->mobanim, mobs, scale, winx, winy, time);
	mixsprite(gfx->sdlh->surface, sprite, player->x / scale - winx, player->y / scale - winy, scale);
	bullet = bullets;
	while (bullet)
	{
		gfx_drawbullet(bullet, gfx->sdlh, scale, winx, winy);
		bullet = bullet->next;
	}
	if (shoulddrawgrid)
		drawgrid(gfx->sdlh, player->x % GRID_SIZE, player->y % GRID_SIZE);
	gfx_drawlife(gfx->sdlh, 0, -WIN_HEIGHT + 1, 2, LIFEBAR_WIDTH, player->life, PLAYER_MAXLIFE);
	gfx_drawenergy(gfx->sdlh, energylvl, WIN_WIDTH - 10, -WIN_HEIGHT + 1, 1, 10);
	fps = (fps * 0.9) + ((1000.0 / (SDL_GetTicks() - lastframe)) * 0.1);
	lastframe = SDL_GetTicks();
	snprintf(str, 20, "FPS:%.0f", fps);
	testtext = fonts_texttosurface(str, "fonts/8bit.ttf", 0x000, gfx->sdlh->surface->format);
	SDL_BlitSurface(testtext, NULL, gfx->sdlh->surface, NULL);
	SDL_FreeSurface(testtext);
	sdlh_update_window(gfx->sdlh);
}

void		gfx_cleanup(t_gfx* gfx)
{
	anim_destroy(gfx->mobanim);
	sdlh_cleanup(gfx->sdlh);
}
