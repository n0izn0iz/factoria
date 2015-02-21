#ifndef EVENTS_H
# define EVENTS_H

# include <SDL2/SDL.h>
# include <stdbool.h>
# include "resparser/restree.h"
# include "misc/array.h"

typedef void (*t_callbackfunc)(void*);

typedef struct	s_eventcallback
{
	char*			name;
	void*			data;
	t_callbackfunc	func;
	SDL_Keycode		sym;
}				t_eventcallback;

typedef struct	s_events
{
	bool		quitflag;
	int			mov_x;
	int			mov_y;
	t_resnode*	bindings;
	t_array*	callbacks;
}				t_events;

t_events*			events_alloc(t_resnode* bindings);
t_eventcallback*	events_callbackalloc(char* name, void* data, t_callbackfunc func);
void				events_registercallback(t_events* events, t_eventcallback* callback);
void				events_registercallbackarray(t_events* events, t_array* array);
void				events_update(t_events* events);

#endif
