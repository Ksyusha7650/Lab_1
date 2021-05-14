#include <iostream>
#include <ctime>
#include "Main.h"
struct point_position rectangle_bottom_left, rectangle_top_right, segment_begin, segment_end, point_intersection1, point_intersection2;
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	greetings();
	bool end = false;
	double angle = 0;
	int  quantity_points = 0, mode = 0;
	srand((unsigned)time(NULL));
	do {
		if (show_or_try()) run_tests();
		else {
			input_types(rectangle_bottom_left, rectangle_top_right, segment_begin, segment_end, angle, mode);
			if (mode != Actions::FILE_INPUT)
				save_data(
					rectangle_bottom_left, rectangle_top_right,
					segment_begin, segment_end, angle);
			check_function(rectangle_bottom_left, rectangle_top_right,
				segment_begin, segment_end, angle,
				point_intersection1, point_intersection2, quantity_points);
			output_results(point_intersection1,
				point_intersection2, quantity_points);
			saving_results(rectangle_bottom_left, rectangle_top_right,
				segment_begin, segment_end,
				point_intersection1,
				point_intersection2);
		}
			end = end_program();
	} while (end != true);
}

