#include "events.h"
#include <SDL2/SDL.h>
#include <stdio.h>

t_evnh*		events_create()
{
	t_evnh*	env;

	env = malloc(sizeof(t_evnh));
	if (env != NULL)
	{
		env->quitflag = false;
		env->spawnmobflag = false;
		env->turretflag = false;
		env->healflag = false;
		env->drawgrid = false;
		env->solarpanelflag = false;
		env->batteryflag = false;
		env->mov_x = 0;
		env->mov_y = 0;
		env->scale = 1;
	}
	return (env);
}

void		events_update(t_evnh* env)
{
	SDL_Event e;
	const Uint8* kstate;
	
	while(SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
			env->quitflag = true;
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_t)
			env->turretflag = true;
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_h)
			env->healflag = true;
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_m)
			env->spawnmobflag = true;
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_g)
			env->drawgrid = !env->drawgrid;
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_KP_MINUS)
			env->scale += env->scale < 4 ? 1 : 0;
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_KP_PLUS)
			env->scale -= env->scale > 1 ? 1 : 0;
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_p)
			env->solarpanelflag = true;
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_b)
			env->batteryflag = true;
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
