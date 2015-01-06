#ifndef TURRET_H
# define TURRET_H

#include "logic/bullet.h"
#include "logic/energy.h"

#define EXPAND_SIZE 32
#define TURRET_NRGCONS		5

typedef struct		s_turret
{
	int x;
	int y;
	int lastshot;
	double angle;
	double targetangle;
	t_consumer*	csm;
}					t_turret;

void			turret_add(t_turret** array, int x, int y, int *size, int time, t_nrgnetwork *nrgnet);
void			turret_inrange(t_turret** array, t_bullet **bullet, int x, int y, int time, int size);

#endif
