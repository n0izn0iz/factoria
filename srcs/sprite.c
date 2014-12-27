#include <stdlib.h>
#include <SDL2/SDL.h>
#include "sprite.h"

t_sprite*		sprite_create(const SDL_Surface *surface, int ox, int oy, int width, int height)
{
	t_sprite *new;

	new = (t_sprite*)malloc(sizeof(t_sprite));
	new->surface = surface;
	new->ox = ox;
	new->oy = oy;
	new->width = width;
	new->height = height;
	return (new);
}

uint32_t		sprite_getpixel(const t_sprite *sprite, int x, int y)
{
	uint32_t color;
	const SDL_Surface *surface;

	surface = sprite->surface;
	color = *(uint32_t*)(((uint8_t*)surface->pixels) + ((sprite->ox + x) * surface->format->BytesPerPixel) + ((sprite->oy + y) * surface->pitch));
	return (color);
}
