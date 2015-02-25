#ifndef SPRITE_H
# define SPRITE_H

#include <SDL2/SDL.h>

typedef struct		s_sprite
{
	SDL_Surface*		surface;
	SDL_Rect			rect;
	int					ox;
	int					oy;
}						t_sprite;

t_sprite*			sprite_create(SDL_Surface* surface, int tox, int toy, int sox, int soy, int width, int height);
uint32_t			sprite_getpixel(const t_sprite *sprite, int x, int y);

#endif
