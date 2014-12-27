#ifndef SPRITE_H
# define SPRITE_H

typedef struct		s_sprite
{
	const SDL_Surface*	surface;
	int					ox;
	int					oy;
	int					width;
	int					height;
}						t_sprite;

t_sprite*			sprite_create(const SDL_Surface* surface, int ox, int oy, int width, int height);
uint32_t			sprite_getpixel(const t_sprite *sprite, int x, int y);

#endif
