#include <stdlib.h>
#include <math.h>
#include "turret.h"
#include "bullet.h"
#include "grid.h"
#include "intersect.h"

#define TURRET_RANGE 250
#define SHOOT_FREQ 5

void			turret_add(t_turret** array, int x, int y, int *size, int time)
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
	if (x > 0)
		(*array)[i].x = x - (x % GRID_SIZE) + (GRID_SIZE / 2);
	else
		(*array)[i].x = x - (x % GRID_SIZE) - (GRID_SIZE / 2);
	if (y > 0)
		(*array)[i].y = y - (y % GRID_SIZE) + (GRID_SIZE / 2);
	else
		(*array)[i].y = y - (y % GRID_SIZE) - (GRID_SIZE / 2);
	(*array)[i].lastshot = time;
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
	turret->angle = atan2(vec_uy, vec_ux) - atan2(-1, 0);
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
		if (lenght < TURRET_RANGE)
		{
			if (time > tmp->lastshot + SHOOT_FREQ)
			{
				updateangle(tmp, x, y);
				bullet_add(bullet, tmp->x, tmp->y, x, y, 8);
				tmp->lastshot = time;
			}
		}
		i++;
	}
}
