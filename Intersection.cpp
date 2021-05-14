#include "Intersection.h"
#include <iostream>
#include <math.h>

using namespace std;


int equation_line(point_position segment_begin, point_position segment_end, double& k, double& b) {
	if (segment_begin.x == segment_end.x) {
		k = 0;
		b = segment_begin.x;
		return 1;
	}
	else
	{
		k = (-segment_begin.y + segment_end.y) / (segment_end.x - segment_begin.x);
		b = segment_begin.y - k * segment_begin.x;
		return 0;
	}
}

void equation_rectangle(point_position point, double angle,
	double& k_rectangle, double& b_rectangle) {
	k_rectangle = round(tan(angle));
	b_rectangle = point.y - k_rectangle * point.x; //b_rectangle
}

bool check_y(point_position rectangle_bottom_left, point_position rectangle_top_right, point_position segment_begin, point_position segment_end,
	double k_rectangle, double b_rectangle, double k_segment, double b_segment, point_position& point_intersection, point_position& point_intersection2,
	int quantity_points, double kind_line) {
	double x;
	if ((kind_line == 0) && (k_rectangle == k_segment)) {
		if (b_rectangle == b_segment) {
			point_intersection.x = point_intersection.y = INFINITY_INTERSECTIONS;
			return true;
		}
		else return false;
	}
	else {
		if (kind_line == 0)
			x = (b_segment - b_rectangle) / (k_rectangle - k_segment);
		else x = b_segment;
		if (x == -0) x = 0;
		if (segment_begin.x > segment_end.x)
			swap(segment_begin.x, segment_end.x);
		if (((rectangle_bottom_left.x <= x) && (x <= rectangle_top_right.x)) && ((segment_begin.x <= x) && (x <= segment_end.x))) {
			double y = k_segment * x + b_segment;
			if (((rectangle_bottom_left.y <= y) && (y <= rectangle_top_right.y)) && ((segment_begin.y <= y) && (y <= segment_end.y))) {
				if (quantity_points == 0) {
					point_intersection.x = x;
					point_intersection.y = k_rectangle * x + b_rectangle;
				}
				else {
					point_intersection2.x = x;
					point_intersection2.y = k_rectangle * x + b_rectangle;
				}
				return true;
			}
			else return false;
		}
		else return false;
	}
}

bool check_x(point_position rectangle_bottom_left, point_position rectangle_top_right, point_position segment_begin, point_position segment_end,
	double k_rectangle, double b_rectangle, double k_segment, double b_segment, point_position& point_intersection,
	point_position& point_intersection2, int quantity_points, point_position point) {
	double x = point.x;
	if (segment_begin.x > segment_end.x)
		swap(segment_begin.x, segment_end.x);
	if ((segment_begin.x <= x) && (x <= segment_end.x)) {
		double y = k_segment * x + b_segment;
		if (((rectangle_bottom_left.y <= y) && (y <= rectangle_top_right.y)) && ((segment_begin.y <= y) && (y <= segment_end.y))) {
			if (quantity_points == 0) {
				point_intersection.x = x;
				point_intersection.y = y;
				return true;
			}
			else if ((point_intersection.x != x) || (point_intersection.y != y)){
				point_intersection2.x = x;
				point_intersection2.y = y;
				return true;
			}
			else return false;
		}
		else return false;
	}
	else return false;
	if ((segment_begin.x == x) && (x == segment_end.x)) {
		if (quantity_points == 0) {
			point_intersection.x = INFINITY_INTERSECTIONS;
			point_intersection.y = INFINITY_INTERSECTIONS;
		}
		else {
			point_intersection2.x = INFINITY_INTERSECTIONS;
			point_intersection2.y = INFINITY_INTERSECTIONS;
		}
	}
	else return false;
}
void change_begin_end(point_position& segment_begin, point_position& segment_end) {
	if (segment_begin.y > segment_end.y) {
		swap(segment_begin.x, segment_end.x);
		swap(segment_begin.y, segment_end.y);
	}
}

bool check_function(point_position rectangle_bottom_left, point_position rectangle_top_right, point_position segment_begin, point_position segment_end,
	double angle, point_position& point_intersection1, point_position& point_intersection2, int& quantity_points) {
	double k_segment = 0, b_segment = 0, check_equation = 0, k_rectangle = 0, b_rectangle = 0;
	change_begin_end(segment_begin, segment_end);
	check_equation = equation_line(segment_begin, segment_end, k_segment, b_segment);
	point_intersection1.x = NO_INTERSECTIONS; point_intersection2.x = NO_INTERSECTIONS;
	if (((check_equation) && ((segment_begin.x == rectangle_bottom_left.x) || (segment_begin.x == rectangle_top_right.x)))
		|| ((segment_end.y == segment_begin.y) && ((segment_begin.y == rectangle_bottom_left.y)
			|| (segment_end.y == rectangle_top_right.y))))
		quantity_points = INFINITY_INTERSECTIONS;
	else {
		equation_rectangle(rectangle_bottom_left, angle, k_rectangle, b_rectangle);
		double PI = asin(1.0) * 2;
		if ((check_y(rectangle_bottom_left, rectangle_top_right, segment_begin, segment_end,
			k_rectangle, b_rectangle, k_segment, b_segment, point_intersection1, point_intersection2, quantity_points, check_equation))) {
			quantity_points++;
		}
		if ((angle == 0)) {
			if (check_x(rectangle_bottom_left, rectangle_top_right, segment_begin, segment_end,
				k_rectangle, b_rectangle, k_segment, b_segment, point_intersection1, point_intersection2, quantity_points, rectangle_bottom_left))
				quantity_points++;
		}
		else {
			equation_rectangle(rectangle_bottom_left, angle + PI / 2, k_rectangle, b_rectangle);
			if (check_y(rectangle_bottom_left, rectangle_top_right, segment_begin, segment_end,
				k_rectangle, b_rectangle, k_segment, b_segment, point_intersection1, point_intersection2, quantity_points, check_equation))
				quantity_points++;
		}
		if (quantity_points != ALL_POINTS) {

			equation_rectangle(rectangle_top_right, angle, k_rectangle, b_rectangle);
			if ((check_y(rectangle_bottom_left, rectangle_top_right, segment_begin, segment_end,
				k_rectangle, b_rectangle, k_segment, b_segment, point_intersection1, point_intersection2, quantity_points, check_equation)))
				quantity_points++;
			if ((angle == 0) && (quantity_points != ALL_POINTS)) {
				if (check_x(rectangle_bottom_left, rectangle_top_right, segment_begin, segment_end,
					k_rectangle, b_rectangle, k_segment, b_segment, point_intersection1, point_intersection2, quantity_points, rectangle_top_right))
					if (point_intersection1.x == point_intersection1.y == INFINITY_INTERSECTIONS)
						quantity_points = INFINITY_INTERSECTIONS;
					else
						quantity_points++;
			}
			else if (quantity_points != ALL_POINTS) {

				equation_rectangle(rectangle_top_right, angle + PI / 2, k_rectangle, b_rectangle);
				if (check_y(rectangle_bottom_left, rectangle_top_right, segment_begin, segment_end,
					k_rectangle, b_rectangle, k_segment, b_segment, point_intersection1, point_intersection2, quantity_points, check_equation)) {
					if (point_intersection1.x == point_intersection1.y == INFINITY_INTERSECTIONS)
						quantity_points = INFINITY_INTERSECTIONS;
					else
						quantity_points++;
				}

			}
		}

	}
	if (quantity_points == 0) return false;
	else return true;
}
