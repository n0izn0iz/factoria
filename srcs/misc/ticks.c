#include "misc/ticks.h"

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <misc/xp_sleep.h>

t_ticker		ticker_create(double freq, double period)
{
	t_ticker	ticker;

	ticker.count = 0;
	if (freq == 0.0)
	{
		ticker.freq = 1000.0 / period;
		ticker.period = period;
	}
	else
	{
		ticker.freq = freq;
		ticker.period = 1000.0 / freq;
	}
	ticker.last = SDL_GetTicks();
	ticker.next = ticker.last + ticker.period;
	ticker.delta = ticker.period;
	ticker.avgdelta = ticker.period;
	ticker.avgtps = 1000.0 / ticker.delta;
	return (ticker);
}
t_ticker*		ticker_alloc(double freq, double period)
{
	t_ticker*	ticker;

	ticker = (t_ticker*)malloc(sizeof(t_ticker));
	if (ticker != NULL)
		*ticker = ticker_create(freq, period);
	return (ticker);
}

void			ticker_update(t_ticker* ticker)
{
	double now;

	ticker->count += 1;
	now = SDL_GetTicks();
	ticker->delta = now - ticker->last;
	ticker->avgdelta = (ticker->avgdelta + ticker->delta) / 2.0;
	ticker->avgtps = (ticker->avgtps + (1000.0 / ticker->avgdelta)) / 2.0;
	ticker->last = now;
	while (SDL_GetTicks() < ticker->next)
		Sleep(0);
	ticker->next += ticker->period;
}
