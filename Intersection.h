#ifndef intersection_H
#define intersection_H
#include "Main.h"
#define INFINITY_INTERSECTIONS 1000
#define NO_INTERSECTIONS 0
#define ALL_POINTS 2
main_H struct point_position;
void equation_rectangle(point_position point, double angle, double& k_rectangle, double& b_rectangle);
int equation_line(point_position segment_begin, point_position segment_end, double& k, double& b);
bool check_function(point_position point1, point_position point2, point_position point3, point_position point4, double angle,
	point_position& point_intersection1, point_position& point_intersection2, int& quantity_points);
#endif
