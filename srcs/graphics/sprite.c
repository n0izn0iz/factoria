#include <stdlib.h>
#include <SDL.h>
#include "graphics/sprite.h"

t_sprite*			sprite_create(SDL_Surface* surface, int tox, int toy, int sox, int soy, int width, int height)
{
	t_sprite *new;

	new = (t_sprite*)malloc(sizeof(t_sprite));
	new->surface = surface;
	new->ox = sox;
	new->oy = soy;
	new->rect.x = tox;
	new->rect.y = toy;
	new->rect.w = width;
	new->rect.h = height;
	return (new);
}

uint32_t		sprite_getpixel(const t_sprite *sprite, int x, int y)
{
	uint32_t color;
	const SDL_Surface *surface;

	surface = sprite->surface;
	color = *(uint32_t*)(((uint8_t*)surface->pixels) + ((sprite->rect.x + x) * surface->format->BytesPerPixel) + ((sprite->rect.y + y) * surface->pitch));
	return (color);
}
