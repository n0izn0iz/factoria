#include <stdlib.h>
#include <math.h>
#include "turret.h"
#include "bullet.h"

#define EXPAND_SIZE 32
#define TURRET_RANGE 500
#define SHOOT_FREQ 15

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
	(*array)[i].x = x;
	(*array)[i].y = y;
	(*array)[i].lastshot = time;
	i++;
	*size = i;
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
				bullet_add(bullet, tmp->x, tmp->y, x, y);
				tmp->lastshot = time;
			}
		}
		i++;
	}
}
