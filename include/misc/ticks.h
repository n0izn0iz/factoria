#ifndef TICKS_H
# define TICKS_H

typedef struct		s_ticker
{
	unsigned int	count;
	double			freq;
	double			period; // inmillisec
	double			last;
	double			next;
	double			delta;
	double			avgdelta;
	double			avgtps;
}					t_ticker;

t_ticker		ticker_create(double freq, double period);
t_ticker*		ticker_alloc(double freq, double period);

void			ticker_update(t_ticker* ticker);

#endif
