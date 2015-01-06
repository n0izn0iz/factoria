#include "graphics/animation.h"

unsigned int		anim_frameindex(t_anim* anim, int time, int frametime)
{
	return (time % (frametime * anim->framecount) / frametime);
}

void					anim_destroy(t_anim* anim)
{
	SDL_FreeSurface(anim->surface);
	free(anim->framearray);
	free(anim);
}
