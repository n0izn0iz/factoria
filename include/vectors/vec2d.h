#ifndef VEC2D_H
# define VEC2D_H

typedef struct	s_vec2d
{
	double x;
	double y;
}				t_vec2d;

t_vec2d		vec2d_create(double x, double y);
t_vec2d*	vec2d_alloc(double x, double y);
t_vec2d		vec2d_add(t_vec2d a, t_vec2d b);
t_vec2d		vec2d_negate(t_vec2d vec);
t_vec2d		vec2d_sub(t_vec2d a, t_vec2d b);
t_vec2d		vec2d_mult(t_vec2d a, t_vec2d b);
t_vec2d		vec2d_multsca(t_vec2d vec, double sca);
t_vec2d		vec2d_addsca(t_vec2d vec, double sca);
t_vec2d		vec2d_divsca(t_vec2d vec, double sca);
double		vec2d_lenght(t_vec2d vec);
double		vec2d_lenghtsq(t_vec2d vec);
t_vec2d		vec2d_normalize(t_vec2d vec);

#endif
