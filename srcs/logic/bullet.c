#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include "logic/bullet.h"
#include "misc/intersect.h"

static t_bullet*		bullet_createlist(int ox, int oy, int dx, int dy, int dmg, int knockback, int velocity)
{
	t_bullet *newlist;

	newlist = (t_bullet*)malloc(sizeof(t_bullet));
	newlist->ox = ox;
	newlist->oy = oy;
	newlist->dx = dx;
	newlist->dy = dy;
	newlist->dmg = dmg;
	newlist->velocity = velocity;
	newlist->knockback = knockback;
	newlist->next = NULL;
	return (newlist);
}

void					bullet_add(t_bullet** list, int ox, int oy, int dx, int dy, int dmg, int knockback, int velocity)
{
	t_bullet	*first;

	if ((*list) == NULL)
	{
		*list = bullet_createlist(ox, oy, dx, dy, dmg, knockback, velocity);
		return ;
	}
	first = *list;
	while ((*list)->next)
		*list = (*list)->next;
	(*list)->next = bullet_createlist(ox, oy, dx, dy, dmg, knockback, velocity);
	*list = first;
}

int						bullet_getcount(t_bullet* bullets)
{
	int i;

	i = 0;
	while (bullets)
	{
		i++;
		bullets = bullets->next;
	}
	return (i);
}

static bool		bullet_updateone(t_bullet *bullet, t_player* player, t_mob *mobs)
{
	double			vectorsize;
	double			unitx;
	double			unity;
	double			trailx;
	double			traily;
	double			movx;
	double			movy;

	vectorsize = sqrt(((bullet->dx - bullet->ox) * (bullet->dx - bullet->ox)) + ((bullet->dy - bullet->oy) * (bullet->dy - bullet->oy)));
	unitx = (float)(bullet->dx - bullet->ox) / vectorsize;
	unity = (float)(bullet->dy - bullet->oy) / vectorsize;
	movx = unitx * bullet->velocity;
	movy = unity * bullet->velocity;
	trailx = bullet->ox + movx;
	traily = bullet->oy + movy;
	while (mobs)
	{
		if (linecirleintersect(bullet->ox, bullet->oy, trailx, traily, mobs->x, mobs->y, MOB_SIZE))
		{
			mob_hit(mobs, bullet->ox, bullet->oy, bullet->knockback, bullet->dmg);
			return (true);
		}
		mobs = mobs->next;
	}
	if (linecirleintersect(bullet->ox, bullet->oy, trailx, traily, player->x, player->y, PLAYER_SIZE))
	{
		player->life -= bullet->dmg;
		return (true);
	}
	if (vectorsize < bullet->velocity)
		return (true);
	bullet->ox = trailx;
	bullet->oy = traily;
	return (false);
}

void		bullet_destroy(t_bullet* list)
{
	t_bullet*	tmp;

	while (list)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
}

void		bullet_update(t_bullet** list, t_player* player, t_mob* mobs)
{
	t_bullet	*it;
	t_bullet	*prev;

	it = *list;
	prev = NULL;
	while (it != NULL)
	{
		if (it->next == NULL)
		{
			if (bullet_updateone(it, player, mobs))
			{
				free(it);
				if (prev == NULL)
					*list = NULL;
				else
					prev->next = NULL;
			}
			return ;
		}
		else if (bullet_updateone(it, player, mobs))
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
