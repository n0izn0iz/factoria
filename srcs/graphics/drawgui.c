#include "graphics/graphics.h"
#include "misc/sdlhandler.h"

#define BUTTON_SIZE 50

static void		gfx_drawguibutton(SDL_Surface* surface, t_guibutton* button, int x, int y, uint32_t rectcolor)
{
	int i;

	gfx_mixsprite(surface, button->sprite, x, y, 1);
	i = 0;
	while (i < BUTTON_SIZE)
	{
		sdlh_putpixel(surface, x - (BUTTON_SIZE / 2) + i, -y - (BUTTON_SIZE / 2), rectcolor);
		sdlh_putpixel(surface, x + i - (BUTTON_SIZE / 2), -y + (BUTTON_SIZE / 2), rectcolor);
		sdlh_putpixel(surface, x- (BUTTON_SIZE / 2), -y + i - (BUTTON_SIZE / 2), rectcolor);
		sdlh_putpixel(surface, x + (BUTTON_SIZE / 2), -y + i - (BUTTON_SIZE / 2), rectcolor);
		i++;
	}
}

static void		gfx_drawguibox(SDL_Surface* surface, t_guibox* box, int x, int y)
{
	unsigned int i;
	int size;

	size = box->buttons->size * BUTTON_SIZE;
	i = 0;
	while (i < box->buttons->size)
	{
		if (i == box->selected)
			gfx_drawguibutton(surface, array_get(box->buttons, i), x - (size / 2) + (i * BUTTON_SIZE), y + (BUTTON_SIZE / 2), 0xAAAAAA);
		else
			gfx_drawguibutton(surface, array_get(box->buttons, i), x - (size / 2) + (i * BUTTON_SIZE), y + (BUTTON_SIZE / 2), 0x555555);
		i++;
	}
}

void			gfx_drawgui(SDL_Surface* surface, t_gui* gui)
{
	t_guibox* box;

	if (gui->boxes->size > 0)
	{
		box = array_get(gui->boxes, 0);
		box->selected = 0;
		gfx_drawguibox(surface, box, surface->w / 2, -surface->h + 1);
	}
}
