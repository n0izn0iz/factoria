#include "graphics/gui.h"
#include <stdlib.h>
#include "misc/array.h"

t_gui*					gui_create(void)
{
	t_gui*		gui;

	gui = (t_gui*)malloc(sizeof(t_gui));
	gui->boxes = array_create(10);
	return (gui);
}

static t_guibox*		gui_createbox(void)
{
	t_guibox*	box;

	box = (t_guibox*)malloc(sizeof(t_guibox));
	box->buttons = array_create(10);
	box->selected = 0;
	return (box);
}

static t_guibutton*		gui_createbutton(void (*callback)(void*), void* data, t_sprite* sprite)
{
	t_guibutton*	button;

	button = (t_guibutton*)malloc(sizeof(t_guibutton));
	button->callback = callback;
	button->data = data;
	button->sprite = sprite;
	return (button);
}

t_guibox*		gui_addbox(t_gui* gui)
{
	t_guibox*	box;

	box = gui_createbox();
	array_append(gui->boxes, box);
	return (box);
}

t_guibutton*	gui_addbutton(t_guibox* box, void (*callback)(void*), void* data, t_sprite* sprite)
{
	t_guibutton*	button;

	button = gui_createbutton(callback, data, sprite);
	array_append(box->buttons, button);
	return (button);
}
