#ifndef GUI_H
# define GUI_H

#include "misc/array.h"
#include "graphics/sprite.h"

typedef struct	s_guibutton
{
	void		(*callback)(void*);
	void*		data;
	t_sprite*	sprite;
}				t_guibutton;

typedef struct	s_guibox
{
	t_array*		buttons;
	unsigned int	selected;
}				t_guibox;

typedef struct	s_gui
{
	t_array*	boxes;
}				t_gui;

t_gui*			gui_create();
t_guibutton*	gui_addbutton(t_guibox* box, void (*callback)(void*), void* data, t_sprite* sprite);
t_guibox*		gui_addbox(t_gui* gui);

#endif
