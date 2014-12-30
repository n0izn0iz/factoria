#include "drawgrid.h"
#include "sdlhandler.h"

void		drawgrid(t_sdlh* sdlh, double offsetx, double offsety)
{
	int i;
	t_point apt, bpt;

	apt.color = 0x22F7CA;
	bpt.color = 0x22FC7A;
	apt.y = 0;
	bpt.y = -WIN_HEIGHT;
	i = 0;
	while (i < WIN_WIDTH / GRID_SIZE)
	{
		apt.x = i * GRID_SIZE - offsetx;
		bpt.x = i * GRID_SIZE - offsetx;
		plot_line(apt, bpt, sdlh);
		i++;
	}
	apt.x = 0;
	bpt.x = WIN_WIDTH;
	i = 0;
	while (i < WIN_HEIGHT / GRID_SIZE)
	{
		apt.y = -i * GRID_SIZE - offsety;
		bpt.y = -i * GRID_SIZE - offsety;
		plot_line(apt, bpt, sdlh);
		i++;
	}
}
