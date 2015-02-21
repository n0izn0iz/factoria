#include "misc/point.h"

t_ipoint		coord_worldtowindow(t_fpoint coord, t_fpoint campos, double zoom, t_ipoint winhalfsize)
{
	t_ipoint result;

	// subtract the camera position
	coord.x -= campos.x;
	coord.y -= campos.y;
	// multiply by the zoom factor
	result.x = coord.x * zoom;
	result.y = coord.y * zoom;
	// invert the y coordinate
	result.y = -result.y;
	// add half the window size
	result.x += winhalfsize.x;
	result.y += winhalfsize.y;
	// return the result
	return (result);
}
