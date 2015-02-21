#ifndef FPOINT_H
# define FPOINT_H

typedef struct		s_fpoint
{
	double x;
	double y;
}					t_fpoint;

typedef struct		s_ipoint
{
	int x;
	int y;
}					t_ipoint;

t_ipoint		coord_worldtowindow(t_fpoint coord, t_fpoint campos, double zoom, t_ipoint winhalfsize);
t_fpoint		fpoint_create(double x, double y);
t_fpoint*		fpoint_alloc(double x, double y);

#endif
