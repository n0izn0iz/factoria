#include "graphics/treerenderer.h"

#include "graphics/diskrenderer.h"
#include "graphics/graphics.h"
#include "qtree/srect.h"
#include "qtree/shapetype.h"

void	drawfrect(t_sdlh* sdlh, const t_frect* rect, const t_fpoint* campos, const t_ipoint* winfhalfsize, double zoom)
{
	/*int i, j;
	double ox, oy, top, bot, right, left, hfx, hfy;

	ox = (rect.origin.x * zoom) - (campos->x * zoom) + winoff->x;
	oy = (rect.origin.y * zoom) - (campos->y * zoom) + winoff->y;
	hfx = rect.halfsize.x * zoom;
	hfy = rect.halfsize.y * zoom;
	right = ox + hfx - 1.0;
	left = ox - hfx;
	bot = oy + hfy;
	top = oy - hfy - 1.0;
	if (fill == false)
	{
		i = 0;
		while (i < hfx - 1.0)
		{
			sdlh_putpixel(sdlh->surface, ox + i, top, color);
			sdlh_putpixel(sdlh->surface, ox - i, top, color);
			sdlh_putpixel(sdlh->surface, ox + i, bot, color);
			sdlh_putpixel(sdlh->surface, ox - i, bot, color);
			i++;
		}
		i = 0;
		while (i < hfy - 1.0)
		{
			sdlh_putpixel(sdlh->surface, right, oy + i, color);
			sdlh_putpixel(sdlh->surface, right, oy - i, color);
			sdlh_putpixel(sdlh->surface, left, oy + i, color);
			sdlh_putpixel(sdlh->surface, left, oy - i, color);
			i++;
		}
	}
	else
	{
		i = left;
		while (i < right)
		{
			j = top;
			while (j < bot)
			{
				sdlh_mixpixel(sdlh, i, j, color, 0.5);
				j++;
			}
			i++;
		}
	}*/
	double left, right, top, bottom;

	left = rect->origin.x - rect->halfsize.x;
	bottom = rect->origin.y - rect->halfsize.y;
	right = rect->origin.x + rect->halfsize.x;
	top = rect->origin.y + rect->halfsize.y;
	plot_worldline(sdlh->surface, fpoint_create(left, bottom), 0xFFFFFF, fpoint_create(right, bottom), 0xFFFFFF, *campos, zoom, *winfhalfsize);
	plot_worldline(sdlh->surface, fpoint_create(right, bottom), 0xFFFFFF, fpoint_create(right, top), 0xFFFFFF, *campos, zoom, *winfhalfsize);
	plot_worldline(sdlh->surface, fpoint_create(right, top), 0xFFFFFF, fpoint_create(left, top), 0xFFFFFF, *campos, zoom, *winfhalfsize);
	plot_worldline(sdlh->surface, fpoint_create(left, top), 0xFFFFFF, fpoint_create(left, bottom), 0xFFFFFF, *campos, zoom, *winfhalfsize);
}

void	drawtree(t_sdlh* sdlh, const t_qtree* tree, t_fpoint* campos, t_ipoint* winoff, double zoom, bool drawgrid)
{
	t_frect		screenrect;

	screenrect.origin = *campos;
	screenrect.halfsize.x = winoff->x / zoom;
	screenrect.halfsize.y = winoff->y / zoom;
	if (!frect_intersect(&tree->bounds, &screenrect))
		return ;
	if (drawgrid)
		drawfrect(sdlh, &tree->bounds, campos, winoff, zoom);
	if (tree->northwest != NULL)
	{
		drawtree(sdlh, tree->northwest, campos, winoff, zoom, drawgrid);
		drawtree(sdlh, tree->northeast, campos, winoff, zoom, drawgrid);
		drawtree(sdlh, tree->southwest, campos, winoff, zoom, drawgrid);
		drawtree(sdlh, tree->southeast, campos, winoff, zoom, drawgrid);
	}
}
