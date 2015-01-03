#ifndef EVENTS_H
# define EVENTS_H

#include <stdbool.h>

typedef struct		s_evnh
{
	bool			quitflag;
	bool			turretflag;
	bool			healflag;
	bool			spawnmobflag;
	bool			drawgrid;
	bool			batteryflag;
	bool			solarpanelflag;
	int				mov_x;
	int				mov_y;
	int				scale;
}					t_evnh;


t_evnh*		events_create();
void		events_update(t_evnh* env);

#endif
