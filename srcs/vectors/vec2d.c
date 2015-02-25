#include "vectors/vec2d.h"

#include <stdlib.h>
#include <math.h>

t_vec2d		vec2d_create(double x, double y)
{
	t_vec2d		vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

t_vec2d*	vec2d_alloc(double x, double y)
{
	t_vec2d*	vec;

	vec = (t_vec2d*)malloc(sizeof(t_vec2d));
	if (vec != NULL)
	{
		vec->x = x;
		vec->y = y;
	}
	return (vec);
}

t_vec2d		vec2d_add(t_vec2d a, t_vec2d b)
{
	a.x += b.x;
	a.y += b.y;
	return (a);
}

t_vec2d		vec2d_negate(t_vec2d vec)
{
	vec.x = -vec.x;
	vec.y = -vec.y;
	return (vec);
}

t_vec2d		vec2d_sub(t_vec2d a, t_vec2d b)
{
	a.x -= b.x;
	a.y -= b.y;
	return (a);
}

t_vec2d		vec2d_mult(t_vec2d a, t_vec2d b)
{
	a.x *= b.x;
	a.y *= b.y;
	return (a);
}

t_vec2d		vec2d_multsca(t_vec2d vec, double sca)
{
	vec.x *= sca;
	vec.y *= sca;
	return (vec);
}

t_vec2d		vec2d_addsca(t_vec2d vec, double sca)
{
	vec.x += sca;
	vec.y += sca;
	return (vec);
}

double		vec2d_lenght(t_vec2d vec)
{
	return sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

double		vec2d_lenghtsq(t_vec2d vec)
{
	return ((vec.x * vec.x) + (vec.y * vec.y));
}

t_vec2d		vec2d_divsca(t_vec2d vec, double sca)
{
	vec.x /= sca;
	vec.y /= sca;
	return (vec);
}

t_vec2d		vec2d_normalize(t_vec2d vec)
{
	return (vec2d_divsca(vec, vec2d_lenght(vec)));
}

