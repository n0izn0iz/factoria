#include "misc/point.h"
#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "misc/sdlhandler.h"


static void		ft_uswap(unsigned int *a, unsigned int *b)
{
	unsigned int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void		ft_swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int		swap_quadrant(int *steep, t_ipoint *apt, uint32_t* cola, t_ipoint *bpt, uint32_t* colb)
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
		ft_uswap(cola, colb);
	}
	if (apt->y < bpt->y)
		return (1);
	else
		return (-1);
}

static int		prep_vars(t_ipoint *dp, t_ipoint *it, t_ipoint *apt, t_ipoint *bpt)
{
	dp->x = bpt->x - apt->x;
	dp->y = abs(bpt->y - apt->y);
	it->x = apt->x - 1;
	it->y = apt->y;
	return (dp->x / 2);
}

static void			__plot_line(t_ipoint apt, uint32_t cola, t_ipoint bpt, uint32_t colb, SDL_Surface* surface)
{
	t_ipoint	dp;
	t_ipoint	it;
	t_ipoint	misc;
	int			steep;
	float	gain;

	misc.y = swap_quadrant(&steep, &apt, &cola, &bpt, &colb);
	misc.x = prep_vars(&dp, &it, &apt, &bpt);
	while (++it.x <= bpt.x)
	{
		gain = (float)(it.x - apt.x) / (bpt.x - apt.x);
		if (steep)
			sdlh_putpixel(surface, it.y, it.x, colmix(cola, colb, gain));
		else
			sdlh_putpixel(surface, it.x, it.y, colmix(cola, colb, gain));
		misc.x -= dp.y;
		if (misc.x < 0)
		{
			it.y += misc.y;
			misc.x += dp.x;
		}
	}
}

void		plot_worldline(SDL_Surface* surface, t_fpoint apt, uint32_t cola, t_fpoint bpt, uint32_t colb, t_fpoint campos, double zoom, t_ipoint winfalfsize)
{
	t_ipoint iapt, ibpt;

	iapt = coord_worldtowindow(apt, campos, zoom, winfalfsize);
	ibpt = coord_worldtowindow(bpt, campos, zoom, winfalfsize);
	__plot_line(iapt, cola, ibpt, colb, surface);
}
