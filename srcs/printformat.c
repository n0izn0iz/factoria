#include <SDL2/SDL.h>
#include <stdio.h>

/*void		print_format(SDL_PixelFormat* format)
{

}*/

void		print_renflag(SDL_RendererFlags flag)
{
	if ((flag & SDL_RENDERER_SOFTWARE) == SDL_RENDERER_SOFTWARE)
		printf("SDL_RENDERER_SOFTWARE\n");
	if ((flag & SDL_RENDERER_ACCELERATED) == SDL_RENDERER_ACCELERATED)
		printf("SDL_RENDERER_ACCELERATED\n");
	if ((flag & SDL_RENDERER_PRESENTVSYNC) == SDL_RENDERER_PRESENTVSYNC)
		printf("SDL_RENDERER_PRESENTVSYNC\n");
	if ((flag & SDL_RENDERER_TARGETTEXTURE) == SDL_RENDERER_TARGETTEXTURE)
		printf("SDL_RENDERER_TARGETTEXTURE\n");
}
