#ifndef interface_H
#define interface_H
#include "Main.h"
struct point_position;
enum Actions {
	END, CONTINUE,
	MANUAL = 1, GENERATE, FILE_INPUT,
	YES = 1, NO,
	DATA, RESULT, READ,
	TEST = 1, TRY
};
bool show_or_try(); 
void input_types(point_position& rectangle_bottom_left, point_position& rectangle_top_right, point_position& segment_begin,
	point_position& segment_end, double& angle,
	int& mode);
void create_file(int mode, point_position & rectangle_bottom_left, point_position & rectangle_top_right,
	point_position & segment_begin, point_position & segment_end, point_position point_intersection1,
	point_position point_intersection2, double& angle, int quantity_points);
void greetings();
void data_output(point_position rectangle_bottom_left, point_position rectangle_top_right, double angle,
	point_position segment_begin, point_position segment_end);
bool end_program();
void saving_results(point_position& rectangle_bottom_left, point_position& rectangle_top_right, 
	point_position& segment_begin, point_position& segment_end,
	point_position point_intersection1, point_position point_intersection2);
void save_data(point_position& rectangle_bottom_left, point_position& rectangle_top_right,
	point_position& segment_begin, point_position& segment_end, double& angle);
void output_results(point_position point_intersection1, point_position point_intersection2, int quantity_points);
#endif

