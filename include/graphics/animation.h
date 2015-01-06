#ifndef ANIMATION_H
#define ANIMATION_H

#include "graphics/sprite.h"

typedef struct		s_anim
{
	t_sprite*		framearray;
	unsigned int	framecount;
	SDL_Surface*	surface;
}					t_anim;

inline unsigned int		anim_frameindex(t_anim* anim, int time, int frametime);
void					anim_destroy(t_anim* anim);

#endif
