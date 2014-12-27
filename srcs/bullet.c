#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include "bullet.h"

# define BULLET_VELOCITY 5

t_bullet*	bullet_createlist(int ox, int oy, float dx, float dy)
{
	t_bullet *newlist;

	newlist = (t_bullet*)malloc(sizeof(t_bullet));
	newlist->ox = ox;
	newlist->oy = oy;
	newlist->dx = dx;
	newlist->dy = dy;
	newlist->next = NULL;
	return (newlist);
}

void		bullet_add(t_bullet** list, int ox, int oy, int dx, int dy)
{
	t_bullet	*first;
	if ((*list) == NULL)
	{
		*list = bullet_createlist(ox, oy, dx, dy);
		return ;
	}
	first = *list;
	while ((*list)->next)
		*list = (*list)->next;
	(*list)->next = bullet_createlist(ox, oy, dx, dy);
	*list = first;
}

bool		bullet_updateone(t_bullet *bullet)
{
	float			vectorsize;
	float			unitx;
	float			unity;
	int				trailx;
	int				traily;
	int				movx;
	int				movy;

	vectorsize = sqrt(((bullet->dx - bullet->ox) * (bullet->dx - bullet->ox)) + ((bullet->dy - bullet->oy) * (bullet->dy - bullet->oy)));
	if (vectorsize < BULLET_VELOCITY * 2)
		return (true);
	unitx = (float)(bullet->dx - bullet->ox) / vectorsize;
	unity = (float)(bullet->dy - bullet->oy) / vectorsize;
	movx = unitx * BULLET_VELOCITY;
	movy = unity * BULLET_VELOCITY;
	trailx = bullet->ox + movx;
	traily = bullet->oy + movy;
	bullet->ox = trailx;
	bullet->oy = traily;
	return (false);
}

void		bullet_update(t_bullet** list)
{
	t_bullet	*it;
	t_bullet	*prev;

	it = *list;
	prev = NULL;
	while (it != NULL)
	{
		if (it->next == NULL)
		{
			if (bullet_updateone(it))
			{
				free(it);
				if (prev == NULL)
					*list = NULL;
				else
					prev->next = NULL;
			}
			return ;
		}
		else if (bullet_updateone(it))
		{
			if (prev == NULL)
			{
				prev = it->next;
				free(it);
				it = prev;
				*list = it;
				prev = NULL;
			}
			else
			{
				prev->next = it->next;
				free(it);
				it = prev->next;
			}
		}
		else
		{
			prev = it;
			it = it->next;
		}
	}
}
