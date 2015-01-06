#include <math.h>
#include <stdbool.h>

double		vec2d_len(double x, double y)
{
	return (sqrt((x * x) + (y * y)));
}

double		vec2d_dot(double ax, double ay, double bx, double by)
{
	return (ax * bx) + (ay * by);
}

bool				linecirleintersect(double seg_ax, double seg_ay, double seg_bx, double seg_by, double cir_x, double cir_y, double cir_sz)
{
	double seg_vx, seg_vy, pt_vx, pt_vy, seg_vlen, seg_vux, seg_vuy, proj_vx, proj_vy, proj_vlen;
	double clos_x, clos_y, dist_x, dist_y;

	seg_vx = seg_bx - seg_ax;
	seg_vy = seg_by - seg_ay;
	pt_vx = cir_x - seg_ax;
	pt_vy = cir_y - seg_ay;
	seg_vlen = vec2d_len(seg_vx, seg_vy);
	seg_vux = seg_vx / seg_vlen;
	seg_vuy = seg_vy / seg_vlen;
	proj_vlen = vec2d_dot(pt_vx, pt_vy, seg_vux, seg_vuy);
	if (proj_vlen < 0)
	{
		clos_x = seg_ax;
		clos_y = seg_ay;
	}
	else if (proj_vlen > seg_vlen)
	{
		clos_x = seg_bx;
		clos_y = seg_by;
	}
	else
	{
		proj_vx = proj_vlen * seg_vux;
		proj_vy = proj_vlen * seg_vuy;
		clos_x = seg_ax + proj_vx;
		clos_y = seg_ay + proj_vy;
	}
	dist_x = cir_x - clos_x;
	dist_y = cir_y - clos_y;
	if (vec2d_len(dist_x, dist_y) < cir_sz)
		return (true);
	else
		return (false);
}

bool				circleintersect(double ax, double ay, double as, double bx, double by, double bs, double* newx, double* newy)
{
	double lenght;
	double newlenght;
	double distance;
	double unitx, unity;
	double vx, vy;

	vx = bx - ax;
	vy = by - ay;
	lenght = vec2d_len(vx, vy);
	distance = as + bs / 2;
	if (lenght <= distance)
	{
		unitx = vx / lenght;
		unity = vy / lenght;
		newlenght = lenght - distance;
		*newx = ax + (unitx * newlenght);
		*newy = ay + (unity * newlenght);
		return (true);
	}
	else
		return (false);
}
