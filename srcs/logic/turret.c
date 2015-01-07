#include <stdlib.h>
#include <math.h>
#include "logic/turret.h"
#include "logic/bullet.h"
#include "misc/grid.h"
#include "misc/intersect.h"
#include "logic/energy.h"

#define TURRET_RANGE		300
#define TURRET_SHOOT_FREQ	40
#define TURRET_ANGMOMENT	0.1
#define TURRET_DMG			15
#define TURRET_KNOCKBACK	10
#define TURRET_VELOCITY		70

void			turret_add(t_turret** array, int x, int y, int *size, int time, t_nrgnetwork **nrgnet)
{
	int		i;
	int		j;
	t_turret*		temparray;

	i = *size;
	if (i % EXPAND_SIZE == 0)
	{
		temparray = (t_turret*)malloc(sizeof(t_turret) * (i + EXPAND_SIZE));
		j = 0;
		while(j < i)
		{
			temparray[j] = (*array)[j];
			j++;
		}
		if (j < 0)
			free(*array);
		*array = temparray;
	}
	temparray = (*array) + i;
	if (x > 0)
		temparray->x = x - (x % GRID_SIZE) + (GRID_SIZE / 2);
	else
		temparray->x = x - (x % GRID_SIZE) - (GRID_SIZE / 2);
	if (y > 0)
		temparray->y = y - (y % GRID_SIZE) + (GRID_SIZE / 2);
	else
		temparray->y = y - (y % GRID_SIZE) - (GRID_SIZE / 2);
	temparray->lastshot = time;
	temparray->csm = nrg_addnode(nrgnet, NT_CONSUMER, x, y, NRG_RANGE);
	temparray->csm->buffer = -TURRET_NRGCONS;
	i++;
	*size = i;
}

static void		updateangle(t_turret* turret, double x, double y)
{
	double vec_x, vec_y, vec_len, vec_ux, vec_uy;

	vec_x = x - turret->x;
	vec_y = y - turret->y;
	vec_len = vec2d_len(vec_x, vec_y);
	vec_ux = vec_x / vec_len;
	vec_uy = vec_y / vec_len;
	turret->targetangle = atan2(vec_uy, vec_ux) - atan2(-1, 0);
	if (turret->angle < turret->targetangle)
	{
		if (turret->targetangle - turret->angle <= M_PI)
		{
			turret->angle += TURRET_ANGMOMENT;
			if (turret->angle > turret->targetangle)
				turret->angle = turret->targetangle;
			return ;
		}
		else
			turret->angle += (2 * M_PI) - TURRET_ANGMOMENT;
		if (turret->angle < turret->targetangle)
			turret->angle = turret->targetangle;
		return ;
	}
	else if (turret->angle > turret->targetangle)
	{
		if (turret->angle - turret->targetangle < M_PI)
		{
			turret->angle -= TURRET_ANGMOMENT;
			if (turret->angle < turret->targetangle)
				turret->angle = turret->targetangle;
			return ;
		}
		else
			turret->angle -= (2 * M_PI) + TURRET_ANGMOMENT;
		if (turret->angle > turret->targetangle)
			turret->angle = turret->targetangle;
		return ;
	}
}

void			turret_inrange(t_turret** array, t_bullet **bullet, int x, int y, int time, int size)
{
	t_turret*	tmp;
	int			i;
	float		lenght;

	i = 0;
	while (i < size)
	{
		tmp = (*array) + i;
		lenght = sqrt(((x - tmp->x) * (x - tmp->x)) + ((y - tmp->y) * (y - tmp->y)));
		if (lenght < TURRET_RANGE && time > tmp->lastshot + TURRET_SHOOT_FREQ)
		{
			updateangle(tmp, x, y);
			if (tmp->csm->buffer == 0 && tmp->angle == tmp->targetangle)
			{
				tmp->csm->buffer -= TURRET_NRGCONS;
				bullet_add(bullet, tmp->x, tmp->y, x, y, TURRET_DMG, TURRET_KNOCKBACK, TURRET_VELOCITY);
				tmp->lastshot = time;
			}
		}
		i++;
	}
}
