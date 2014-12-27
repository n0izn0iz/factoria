/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeier <nmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 15:44:59 by nmeier            #+#    #+#             */
/*   Updated: 2014/11/29 16:56:45 by nmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "sdlhandler.h"

static void		ft_swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int		swap_quadrant(int *steep, t_point *apt, t_point *bpt)
{
	if ((*steep = (abs(bpt->y - apt->y) > abs(bpt->x - apt->x))))
	{
		ft_swap(&(apt->x), &(apt->y));
		ft_swap(&(bpt->x), &(bpt->y));
	}
	if (apt->x > bpt->x)
	{
		ft_swap(&(apt->x), &(bpt->x));
		ft_swap(&(apt->y), &(bpt->y));
		ft_swap(&(apt->color), &(bpt->color));
	}
	if (apt->y < bpt->y)
		return (1);
	else
		return (-1);
}

static int		prep_vars(t_point *dp, t_point *it, t_point *apt, t_point *bpt)
{
	dp->x = bpt->x - apt->x;
	dp->y = abs(bpt->y - apt->y);
	it->x = apt->x - 1;
	it->y = apt->y;
	return (dp->x / 2);
}

void			plot_line(t_point apt, t_point bpt, t_sdlh *sdlh)
{
	t_point	dp;
	t_point	it;
	t_point	misc;
	float	gain;

	misc.y = swap_quadrant(&(misc.z), &apt, &bpt);
	misc.x = prep_vars(&dp, &it, &apt, &bpt);
	while (++it.x <= bpt.x)
	{
		gain = (float)(it.x - apt.x) / (bpt.x - apt.x);
		if (misc.z)
			sdlh_putpixel(sdlh, it.y, -it.x, colmix(apt.color, bpt.color, gain));
		else
			sdlh_putpixel(sdlh, it.x, -it.y, colmix(apt.color, bpt.color, gain));
		misc.x -= dp.y;
		if (misc.x < 0)
		{
			it.y += misc.y;
			misc.x += dp.x;
		}
	}
}
