#include "events/events.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

t_events*			events_alloc(t_resnode* bindings)
{
	t_events* events;

	events = (t_events*)malloc(sizeof(t_events));
	if (events != NULL)
	{
		events->quitflag = false;
		events->mov_x = 0;
		events->mov_y = 0;
		events->bindings = bindings;
		events->callbacks = array_create(10);
	}
	return (events);
}

t_eventcallback*	events_callbackalloc(char* name, void* data, t_callbackfunc func)
{
	t_eventcallback*	callback;

	callback = (t_eventcallback*)malloc(sizeof(t_eventcallback));
	if (callback != NULL)
	{
		callback->name = strdup(name);
		callback->data = data;
		callback->func = func;
		callback->sym = SDLK_UNKNOWN;
	}
	return (callback);
}

void				events_registercallback(t_events* events, t_eventcallback* callback)
{
	t_resnode*		binding;
	t_datapoint*	datapoint;
	char			key[2];

	binding = resnode_getchildbyname(events->bindings, callback->name);
	if (binding != NULL)
	{
		datapoint = resnode_getdatabyname(binding, "key");
		if (datapoint != NULL)
		{
			if (datapoint->type == DPTYPE_CHAR)
			{
				key[0] = datapoint->data.c;
				key[1] = '\0';
				callback->sym = SDL_GetKeyFromName(key);
				array_append(events->callbacks, callback);
				return ;
			}
			else if (datapoint->type == DPTYPE_STR)
			{
				callback->sym = SDL_GetKeyFromName(datapoint->data.str);
				array_append(events->callbacks, callback);
				return ;
			}
		}
	}
	fprintf(stderr, "No valid binding found for event \"%s\".\n", callback->name);
}

void				events_registercallbackarray(t_events* events, t_array* array)
{
	unsigned int i;

	i = 0;
	while (i < array->size)
	{
		events_registercallback(events, array_get(array, i));
		i++;
	}
}

void				events_update(t_events* events)
{
	unsigned int		i;
	t_array*			callbacks;
	t_eventcallback*	callback;
	SDL_Event			e;
	const Uint8*		kstate;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
			events->quitflag = true;
		else if (e.type == SDL_KEYDOWN)
		{
			callbacks = events->callbacks;
			i = 0;
			while (i < callbacks->size)
			{
				callback = array_get(callbacks, i);
				if (callback->sym == e.key.keysym.sym)
					callback->func(callback->data);
				i++;
			}
		}
	}
	kstate = SDL_GetKeyboardState(NULL);
	events->mov_x = 0;
	events->mov_y = 0;
	if (kstate[SDL_GetScancodeFromKey(SDLK_d)])
		events->mov_x += 1;
	if (kstate[SDL_GetScancodeFromKey(SDLK_q)])
		events->mov_x -= 1;
	if (kstate[SDL_GetScancodeFromKey(SDLK_z)])
		events->mov_y += 1;
	if (kstate[SDL_GetScancodeFromKey(SDLK_s)])
		events->mov_y -= 1;
}
