#ifndef TURRET_H
# define TURRET_H

#include "bullet.h"

typedef struct		s_turret
{
	int x;
	int y;
	int lastshot;
}					t_turret;

void			turret_add(t_turret** array, int x, int y, int *size, int time);
void			turret_inrange(t_turret** array, t_bullet **bullet, int x, int y, int time, int size);

#endif
