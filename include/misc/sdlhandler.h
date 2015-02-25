#ifndef SDLHANDLER_H
#define SDLHANDLER_H

#include <SDL2/SDL.h>
#include <stdint.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

typedef struct		s_point
{
	int x;
	int y;
	int z;
	int color;
}					t_point;

typedef struct	s_sdlh
{
	SDL_Window*		window;
	SDL_Renderer*	renderer;
	SDL_Texture*	texture;
	SDL_Surface*	surface;
	uint32_t		pixels[WIN_WIDTH * WIN_HEIGHT];
}				t_sdlh;

void			sdlh_init(t_sdlh*	env);
SDL_Surface*	sdlh_loadandconvert(char *path);
void			sdlh_putpixel(SDL_Surface* dest, uint32_t x, uint32_t y, uint32_t pixel);
void			sdlh_mixpixel(t_sdlh *sdlh, uint32_t x, uint32_t y, uint32_t pixel, float gain);
void			sdlh_update_window(const t_sdlh*	env);
void			sdlh_cleanup(t_sdlh*	env);
uint32_t		colmix(uint32_t cola, uint32_t colb, float gain);
void			plot_line(struct s_point apt, struct s_point bpt, t_sdlh *sdlh);


void		print_renflag(SDL_RendererFlags flag);

#endif
