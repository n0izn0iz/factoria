#include "logic/mob.h"
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "logic/player.h"
#include "misc/intersect.h"

static t_mob*	mob_createlist(double x, double y, int time)
{
	t_mob *newlist;
	static unsigned int counter = 0;

	newlist = (t_mob*)malloc(sizeof(t_mob));
	newlist->x = x;
	newlist->y = y;
	newlist->birthtime = time;
	newlist->lasthit = time;
	newlist->life = MOB_MAXLIFE;
	newlist->next = NULL;
	newlist->id = counter;
	counter += 1;
	return (newlist);
}

int			mob_getcount(t_mob* mobs)
{
	int i;

	i = 0;
	while (mobs)
	{
		i++;
		mobs = mobs->next;
	}
	return (i);
}

void		mob_add(t_mob** list, double x, double y, int time)
{
	t_mob	*first;

	if ((*list) == NULL)
	{
		*list = mob_createlist(x, y, time);
		return ;
	}
	first = *list;
	while ((*list)->next)
		*list = (*list)->next;
	(*list)->next = mob_createlist(x, y, time);
	*list = first;
}

static void		mob_updateangle(t_mob *mob, double dir_x, double dir_y)
{
	double vec_x, vec_y, vec_len, vec_ux, vec_uy;

	vec_x = dir_x - mob->x;
	vec_y = dir_y - mob->y;
	vec_len = vec2d_len(vec_x, vec_y);
	vec_ux = vec_x / vec_len;
	vec_uy = vec_y / vec_len;
	mob->angle = atan2(vec_uy, vec_ux) - atan2(-1, 0);
}

static void		mob_moveto(t_mob *mob, double x, double y, double speed, double* newx, double* newy)
{
	double vectorlenght, unitx, unity, movx, movy;

	vectorlenght = vec2d_len(x - mob->x, y - mob->y);
	unitx = (x - mob->x) / vectorlenght;
	unity = (y - mob->y) / vectorlenght;
	movx = unitx * speed;
	movy = unity * speed;
	*newx = mob->x + movx;
	*newy = mob->y + movy;
}

void		mob_destroy(t_mob* list)
{
	t_mob* tmp;

	while (list)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
}

static bool		mob_updateone(t_mob *mob, t_mob* othermobs, t_player* player, int time)
{
	double		vectorsize;
	double		trailx;
	double		traily;
	double		newmovx;
	double		newmovy;

	mob_updateangle(mob, player->x, player->y);
	vectorsize = vec2d_len(player->x - mob->x, player->y - mob->y);
	if (vectorsize > MOB_SIZE + PLAYER_SIZE / 2.0)
	{
		mob_moveto(mob, player->x, player->y, 2.0, &trailx, &traily);
		while (othermobs)
		{
			if (mob->id != othermobs->id && circleintersect(trailx, traily, MOB_SIZE, othermobs->x, othermobs->y, MOB_SIZE, &newmovx, &newmovy))
			{
				trailx = newmovx;
				traily = newmovy;
			}
			othermobs = othermobs->next;
		}
		mob->x = trailx;
		mob->y = traily;
	}
	else if (mob->lasthit + MOB_HITFREQ < time)
	{
		player->life -= MOB_DMG;
		mob->lasthit = time;
	}
	if (mob->life <= 0)
	{
		player->score += 1;
		return (true);
	}
	return (false);
}

void		mob_update(t_mob** list, t_player* player, int time)
{
	t_mob	*it;
	t_mob	*prev;

	it = *list;
	prev = NULL;
	while (it != NULL)
	{
		if (it->next == NULL)
		{
			if (mob_updateone(it, *list, player, time))
			{
				free(it);
				if (prev == NULL)
					*list = NULL;
				else
					prev->next = NULL;
			}
			return ;
		}
		else if (mob_updateone(it, *list, player, time))
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
