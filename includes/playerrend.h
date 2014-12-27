#ifndef PLAYERREND_H
# define PLAYERREND_H

#include "sprite.h"

typedef struct	s_playersprite
{
	t_sprite *front;
	t_sprite *back;
	t_sprite *right;
	t_sprite *left;
}				t_playersprite;

#endif
