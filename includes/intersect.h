#ifndef INTERSECT_H
#define INTERSECT_H

#include <stdbool.h>

inline double		vec2d_len(double x, double y);
inline double		vec2d_dot(double ax, double ay, double bx, double by);
bool				linecirleintersect(double seg_ax, double seg_ay, double seg_bx, double seg_by, double cir_x, double cir_y, double cir_sz);
bool				circleintersect(double ax, double ay, double as, double bx, double by, double bs, double* newx, double* newy);

#endif
