#include <iostream>
#include <cassert>
#include "Test.h"
using namespace std;
struct point_position rectangle_bottom_left_t, rectangle_top_right_t, segment_begin_t, segment_end_t, point_intersection1_t, point_intersection2_t; 
int expected_x_1 = 0, expected_y_1 = 0, expected_x_2 = 0, expected_y_2 = 0, expected_quantity = 0, quantity_points = 0;
double k_r = 0, b_r = 0, k_s = 0, b_s = 0;

void update_dates(void) {
	quantity_points = 0;
	k_r = 0, b_r = 0, k_s = 0, b_s = 0;
	point_intersection1_t.x = 0;
	point_intersection1_t.y = 0;
	point_intersection2_t.x = 0;
	point_intersection2_t.y = 0;
}
	bool Test1(void) {
		update_dates();
		rectangle_bottom_left_t.x = 0;
		rectangle_bottom_left_t.y = 0;
		rectangle_top_right_t.x = 6;
		rectangle_top_right_t.y = 6;
		segment_begin_t.x = 5;
		segment_begin_t.y = 5;
		segment_end_t.x = 10;
		segment_end_t.y = 10;
		expected_x_1 = 6;
		expected_y_1 = 6;
		expected_x_2 = 0;
		expected_y_2 = 0;
		check_function(rectangle_bottom_left_t, rectangle_top_right_t, segment_begin_t, segment_end_t, 
			0, point_intersection1_t, point_intersection2_t, quantity_points);
		if (((point_intersection1_t.x == expected_x_1) && (point_intersection1_t.y == expected_y_1)) &&
			((point_intersection2_t.x == expected_x_2) && (point_intersection2_t.y == expected_y_2)))  return true;
		else{
			cout << "Тест 1 не пройден." << endl;
			data_output(rectangle_bottom_left_t, rectangle_top_right_t, 0, segment_begin_t, segment_end_t);
			cout << "Полученная 1 точка пересечения по x: " << point_intersection1_t.x << " по y: " << point_intersection1_t.y << endl; 
			cout << "Ожидаемая  1 точка пересечения по x: " << expected_x_1 << " по y: " << expected_y_1 << endl;
			cout << "Полученная 2 точка пересечения по x: " << point_intersection2_t.x << " по y: " << point_intersection2_t.y << endl;
			cout << "Ожидаемая  2 точка пересечения по x: " << expected_x_2 << " по y: " << expected_y_2 << endl;
			cout << endl;
			return false;
		}
	}

	bool Test2(void) {
		update_dates();
		rectangle_bottom_left_t.x = 1;
		rectangle_bottom_left_t.y = 1;
		rectangle_top_right_t.x = 8;
		rectangle_top_right_t.y = 8;
		segment_begin_t.x = 0;
		segment_begin_t.y = 1;
		segment_end_t.x = 9;
		segment_end_t.y = 1;
		expected_quantity = INFINITY_INTERSECTIONS;
		check_function(rectangle_bottom_left_t, rectangle_top_right_t, segment_begin_t, segment_end_t, 0,
			point_intersection1_t, point_intersection2_t, quantity_points);
		if (quantity_points == expected_quantity) return true;
		else {
			cout << "Тест 2 не пройден." << endl;
			data_output(rectangle_bottom_left_t, rectangle_top_right_t, 0, segment_begin_t, segment_end_t);
			cout << "Полученное количество  точек пересечений: " << quantity_points << endl;
			cout << "Ожидаемое  количество  точек пересечений: " << expected_quantity << endl;
			cout << endl;
			return false;
		}
	}

	bool Test3(void) {
		update_dates();
		rectangle_bottom_left_t.x = 1;
		rectangle_bottom_left_t.y = 1;
		rectangle_top_right_t.x = 8;
		rectangle_top_right_t.y = 8;
		segment_begin_t.x = 0;
		segment_begin_t.y = 9;
		segment_end_t.x = 9;
		segment_end_t.y = 9;
		expected_quantity = 0;
		check_function(rectangle_bottom_left_t, rectangle_top_right_t, segment_begin_t, segment_end_t, 0,
			point_intersection1_t, point_intersection2_t, quantity_points);
		if (quantity_points == expected_quantity) return true;
		else {
			cout << "Тест 3 не пройден." << endl;
			data_output(rectangle_bottom_left_t, rectangle_top_right_t, 0, segment_begin_t, segment_end_t);
			cout << "Полученное количество  точек пересечений: " << quantity_points << endl;
			cout << "Ожидаемое  количество  точек пересечений: " << expected_quantity << endl;
			cout << endl;
			return false;
		}
	}

	bool Test4(void) {
		update_dates();
		rectangle_bottom_left_t.x = 0;
		rectangle_bottom_left_t.y = 0;
		rectangle_top_right_t.x = 6;
		rectangle_top_right_t.y = 6;
		segment_begin_t.x = -4;
		segment_begin_t.y = -4;
		segment_end_t.x = 10;
		segment_end_t.y = 10;
		expected_x_1 = 0;
		expected_y_1 = 0;
		expected_x_2 = 6;
		expected_y_2 = 6;
		check_function(rectangle_bottom_left_t, rectangle_top_right_t, segment_begin_t, segment_end_t,
			0, point_intersection1_t, point_intersection2_t, quantity_points);
		if (((point_intersection1_t.x == expected_x_1) && (point_intersection1_t.y == expected_y_1)) &&
			((point_intersection2_t.x == expected_x_2) && (point_intersection2_t.y == expected_y_2))) return true;
		else {
			cout << "Тест 4 не пройден." << endl;
			data_output(rectangle_bottom_left_t, rectangle_top_right_t, 0, segment_begin_t, segment_end_t);
			cout << "Полученная 1 точка пересечения по x: " << point_intersection1_t.x << " по y: " << point_intersection1_t.y << endl;
			cout << "Ожидаемая  1 точка пересечения по x: " << expected_x_1 << " по y: " << expected_y_1 << endl;
			cout << "Полученная 2 точка пересечения по x: " << point_intersection2_t.x << " по y: " << point_intersection2_t.y << endl;
			cout << "Ожидаемая  2 точка пересечения по x: " << expected_x_2 << " по y: " << expected_y_2 << endl;
			cout << endl;
			return false;
		}
	}

	bool Test5(void) {
		update_dates();
		rectangle_bottom_left_t.x = 2;
		rectangle_bottom_left_t.y = 1;
		rectangle_top_right_t.x = 6;
		rectangle_top_right_t.y = 5;
		segment_begin_t.x = 0;
		segment_begin_t.y = 0;
		segment_end_t.x = 10;
		segment_end_t.y = 10;
		expected_x_1 = 2;
		expected_y_1 = 2;
		expected_x_2 = 5;
		expected_y_2 = 5;
		check_function(rectangle_bottom_left_t, rectangle_top_right_t, segment_begin_t, segment_end_t,
			0, point_intersection1_t, point_intersection2_t, quantity_points);
		if (((point_intersection1_t.x == expected_x_1) && (point_intersection1_t.y == expected_y_1)) &&
			((point_intersection2_t.x == expected_x_2) && (point_intersection2_t.y == expected_y_2))) return true;
		else {
			cout << "Тест 5 не пройден." << endl;
			data_output(rectangle_bottom_left_t, rectangle_top_right_t, 0, segment_begin_t, segment_end_t);
			cout << "Полученная 1 точка пересечения по x: " << point_intersection1_t.x << " по y: " << point_intersection1_t.y << endl;
			cout << "Ожидаемая  1 точка пересечения по x: " << expected_x_1 << " по y: " << expected_y_1 << endl;
			cout << "Полученная 2 точка пересечения по x: " << point_intersection2_t.x << " по y: " << point_intersection2_t.y << endl;
			cout << "Ожидаемая  2 точка пересечения по x: " << expected_x_2 << " по y: " << expected_y_2 << endl;
			cout << endl;
			return false;
		}
		update_dates();
	}

	bool Test6(void) {
		update_dates();
		rectangle_bottom_left_t.x = 0;
		rectangle_bottom_left_t.y = 0;
		rectangle_top_right_t.x = 7;
		rectangle_top_right_t.y = 4;
		segment_begin_t.x = 3;
		segment_begin_t.y = -1;
		segment_end_t.x = 9;
		segment_end_t.y = 5;
		expected_x_1 = 4;
		expected_y_1 = 0;
		expected_x_2 = 7;
		expected_y_2 = 3;
		check_function(rectangle_bottom_left_t, rectangle_top_right_t, segment_begin_t, segment_end_t,
			0, point_intersection1_t, point_intersection2_t, quantity_points);
		if (((point_intersection1_t.x == expected_x_1) && (point_intersection1_t.y == expected_y_1)) &&
			((point_intersection2_t.x == expected_x_2) && (point_intersection2_t.y == expected_y_2)))  return true;
		else {
			cout << "Тест 6 не пройден." << endl;
			data_output(rectangle_bottom_left_t, rectangle_top_right_t, 0, segment_begin_t, segment_end_t);
			cout << "Полученная 1 точка пересечения по x: " << point_intersection1_t.x << " по y: " << point_intersection1_t.y << endl;
			cout << "Ожидаемая  1 точка пересечения по x: " << expected_x_1 << " по y: " << expected_y_1 << endl;
			cout << "Полученная 2 точка пересечения по x: " << point_intersection2_t.x << " по y: " << point_intersection2_t.y << endl;
			cout << "Ожидаемая  2 точка пересечения по x: " << expected_x_2 << " по y: " << expected_y_2 << endl;
			cout << endl;
			return false;
		}
	}

	bool Test7(void) {
		update_dates();
		rectangle_bottom_left_t.x = 0;
		rectangle_bottom_left_t.y = 0;
		rectangle_top_right_t.x = 10;
		rectangle_top_right_t.y = 2;
		segment_begin_t.x = -2;
		segment_begin_t.y = 0;
		segment_end_t.x = 7;
		segment_end_t.y = -5;
		expected_x_1 = 0;
		expected_y_1 = 0;
		expected_x_2 = 0;
		expected_y_2 = 0;
		check_function(rectangle_bottom_left_t, rectangle_top_right_t, segment_begin_t, segment_end_t,
			0, point_intersection1_t, point_intersection2_t, quantity_points);
		if (((point_intersection1_t.x == expected_x_1) && (point_intersection1_t.y == expected_y_1)) &&
			((point_intersection2_t.x == expected_x_2) && (point_intersection2_t.y == expected_y_2)))  return true;
		else {
			cout << "Тест 7 не пройден." << endl;
			data_output(rectangle_bottom_left_t, rectangle_top_right_t, 0, segment_begin_t, segment_end_t);
			cout << "Полученная 1 точка пересечения по x: " << point_intersection1_t.x << " по y: " << point_intersection1_t.y << endl;
			cout << "Ожидаемая  1 точка пересечения по x: " << expected_x_1 << " по y: " << expected_y_1 << endl;
			cout << "Полученная 2 точка пересечения по x: " << point_intersection2_t.x << " по y: " << point_intersection2_t.y << endl;
			cout << "Ожидаемая  2 точка пересечения по x: " << expected_x_2 << " по y: " << expected_y_2 << endl;
			cout << endl;
			return false;
		}
	}


void run_tests(void) {
	if (Test1() && Test2() && Test3() && Test4() && Test5() && Test6() && Test7()) cout <<"Все тесты пройдены!" << endl;
}
