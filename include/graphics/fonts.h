#ifndef FONTS_H
#define FONTS_H

#include <SDL_ttf.h>

void			fonts_init();
SDL_Surface*	fonts_texttosurface(const char *str, const char *path, uint32_t color, SDL_PixelFormat* format);

#endif
