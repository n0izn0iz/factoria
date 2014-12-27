#include <stdio.h>
#include <SDL2/SDL_image.h>

#include "strjoin.h"
#include "sdlhandler.h"

#define LAST(k, n) ((k) & ((1<<(n))-1))
#define MID(k, m, n) LAST((k)>>(m),((n)-(m)))
#define SPRITES_DIR "sprites/"

static void		sdl_error(const char* str)
{
	fprintf(stderr, "%s: %s\n", str, SDL_GetError());
	exit(-1);
}

uint32_t		colmix(uint32_t cola, uint32_t colb, float gain)
{
	int rr;
	int gr;
	int br;

	rr = (MID(cola, 16, 24) * (1 - gain)) + (MID(colb, 16, 24) * gain);
	gr = (MID(cola, 8, 16) * (1 - gain)) + (MID(colb, 8, 16) * gain);
	br = (MID(cola, 0, 8) * (1 - gain)) + (MID(colb, 0, 8) * gain);
	return ((rr << 16) + (gr << 8) + br);
}

void			sdlh_init(t_sdlh*	env)
{
	if (SDL_Init(0))
		sdl_error("Unable to initialize SDL: %s\n");
	atexit(SDL_Quit);
	if ((env->window = SDL_CreateWindow("sdlh", 0, 0, WIN_WIDTH, WIN_HEIGHT, 0)) == NULL)
		sdl_error("Unable to create window: %s\n");
	if ((env->renderer = SDL_CreateRenderer(env->window, -1, 0)) == NULL)
		sdl_error("Unable to create renderer: %s\n");
	if ((env->texture = SDL_CreateTexture(env->renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STATIC, WIN_WIDTH, WIN_HEIGHT)) == NULL)
		sdl_error("Unable to create Texture: %s\n");
	env->quitflag = false;
	env->turretflag = false;
	env->mov_x = 0;
	env->mov_y = 0;
}

void			sdlh_putpixel(t_sdlh *sdlh, uint32_t x, uint32_t y, uint32_t pixel)
{
	if (y >= WIN_HEIGHT || x >= WIN_WIDTH)
		return ;
	sdlh->pixels[y * WIN_WIDTH + x] = pixel;
}

SDL_Surface*	sdlh_loadandconvert(char *name)
{
	SDL_Surface*	image;
	SDL_Surface*	conversion;
	char*			tmp;

	tmp = strjoin(SPRITES_DIR, name);
	image = IMG_Load(tmp);
	free(tmp);
	if (!image)
		fprintf(stderr, "%s\n", IMG_GetError());
	conversion = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_RGB888, 0);
	SDL_FreeSurface(image);
	return (conversion);
}

void			sdlh_mixpixel(t_sdlh *sdlh, uint32_t x, uint32_t y, uint32_t pixel, float gain)
{
	uint32_t	*currpixel;

	if (y >= WIN_HEIGHT || x >= WIN_WIDTH)
		return ;
	currpixel = sdlh->pixels + (y * WIN_WIDTH + x);
	*currpixel = colmix(pixel, *currpixel, gain);
}

void			sdlh_handle_events(t_sdlh*	env)
{
	SDL_Event e;
	const Uint8* kstate;
	
	while(SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
			env->quitflag = true;
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_t)
			env->turretflag = true;
	}
	kstate = SDL_GetKeyboardState(NULL);
	env->mov_x = 0;
	env->mov_y = 0;
	if (kstate[SDL_GetScancodeFromKey(SDLK_d)])
		env->mov_x += 1;
	if (kstate[SDL_GetScancodeFromKey(SDLK_q)])
		env->mov_x -= 1;
	if (kstate[SDL_GetScancodeFromKey(SDLK_z)])
		env->mov_y += 1;
	if (kstate[SDL_GetScancodeFromKey(SDLK_s)])
		env->mov_y -= 1;
}

void			sdlh_update_window(const t_sdlh*	env)
{
	SDL_UpdateTexture(env->texture, NULL, env->pixels, WIN_WIDTH * sizeof(uint32_t));
	SDL_RenderCopy(env->renderer, env->texture, NULL, NULL);
	SDL_RenderPresent(env->renderer);
}

void			sdlh_cleanup(t_sdlh*	env)
{
	SDL_DestroyTexture(env->texture);
	SDL_DestroyRenderer(env->renderer);
	SDL_DestroyWindow(env->window);
}

