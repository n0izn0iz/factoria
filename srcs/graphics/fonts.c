#include "graphics/fonts.h"
#include <stdio.h>

void			fonts_init()
{
	if (TTF_Init() < 0)
		printf("%s\n", TTF_GetError());
	atexit(TTF_Quit);
}

SDL_Surface*	fonts_texttosurface(const char *str, const char *path, uint32_t color, SDL_PixelFormat* format)
{
	TTF_Font*		font;
	SDL_Surface*	surface;
	SDL_Color		sdlcolor;

	SDL_GetRGBA(color, format, &sdlcolor.r, &sdlcolor.g, &sdlcolor.b, &sdlcolor.a);
	font = TTF_OpenFont(path, 20);
	if (font == NULL)
		printf("%s\n", TTF_GetError());
	surface = TTF_RenderText_Blended(font, str, sdlcolor);
	if (surface == NULL)
		printf("%s\n", TTF_GetError());
	TTF_CloseFont(font);
	return (surface);
}
