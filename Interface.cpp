#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <filesystem>
#include "Interface.h"
#define INFINITY_INTERSECTIONS 1000
#define NO_INTERSECTIONS 0
#define ONE_POINT 1
#define TWO_POINTS 2
using namespace std;
using namespace filesystem;



double get_double() {
	double input = 0;
	cin >> input;
	while (cin.fail()) {
		while ((getchar() != '\n'));
		cin.clear();
		cout << "������� �����." << endl;
		cin >> input;
	}
	while (getchar() != '\n');
	return input;
}

int get_int() {
	int input = 0;
	cin >> input;
	while (cin.fail()) {
		while (getchar() != '\n');
		cin.clear();
		cout << "������� �����." << endl;
		cin >> input;
	}
	while (getchar() != '\n');
	return input;
}

double point_input() {
	double input = get_double();
	while (((INT64_MAX < input) || (input < INT64_MIN))) {
		cout << "�������� ���������� �� ������������� ���� double." << endl
			<< "������� ����� �� ������� ���������: " << INT64_MIN << " / " << INT64_MAX << endl;
		input = get_double();
	}
	return input;
}

void input_segment(point_position& point, point_position& point2) {
	int check = 0;
	cout << "������� ���������� ������ �������." << endl;
	cout << "���������� �� �: ";
	point.x = point_input();
	cout << "���������� �� �: ";
	point.y = point_input();
	cout << "������� ���������� ����� �������." << endl;
	cout << "���������� �� �: ";
	point2.x = point_input();
	cout << "���������� �� �: ";
	point2.y = point_input();
	while ((point.x == point2.x) && (point.y == point2.y)) {
		cout << "������� ���������� �������� �� ������ �������." << endl;
		cout << "���������� �� �: ";
		point2.x = point_input();
		cout << "���������� �� �: ";
		point2.y = point_input();
	}
}

void input_rectangle(point_position& point, point_position& point2, double& angle) {
	int check = 0;
	cout << "������� ���������� ����� ������ ����� ��������������." << endl;
	cout << "���������� �� �: ";
	point.x = point_input();
	cout << "���������� �� �: ";
	point.y = point_input();
	cout << "������� ���������� ������ ������� ����� ��������������." << endl;
	cout << "���������� �� �: ";
	point2.x = point_input();
	while ((point.x == point2.x) || (point.x > point2.x)) {
		if (point.x == point2.x) {
			cout << "������� ���������� �� � �������� �� ����������." << endl;
			point2.x = point_input();
		}
		if (point.x > point2.x) {
			cout << "������� ���������� �� � ������ ����������. ��� ������ ����������." << endl;
			point2.x = point_input();
		}
	}
	check = 0;
	cout << "���������� �� �: ";
	point2.y = point_input();
	while ((point.y == point2.y) || (point.y > point2.y)) {
		if (point.y == point2.y) {
			cout << "������� ���������� �� y �������� �� ����������." << endl;
			point2.y = point_input();
		}
		if (point.y > point2.y) {
			cout << "������� ���������� �� y ������ ����������. ��� ������� ����������." << endl;
			point2.y = point_input();
		}
		else check = 1;
	}
	cout << "������� ���� ������� � ��������: " << endl;
	angle = get_double();
}

void generate_recatngle(point_position& point, point_position& point2, double& angle) {
	const int RANDOM_MIN = -100, RANDOM_MAX = 100 - RANDOM_MIN + 1, RANDOM_MIN_ANGLE = 0, RANDOM_MAX_ANGLE = 6;
	point.x = RANDOM_MIN + rand() / double(RANDOM_MAX);
	point.y = RANDOM_MIN + rand() / (double)RANDOM_MAX;
	point2.x = (point.x + 1) + rand() / (double)RANDOM_MAX;
	point2.y = (point.y + 1) + rand() / (double)RANDOM_MAX;
	angle = rand() % RANDOM_MAX_ANGLE + RANDOM_MIN_ANGLE;
	cout << "K��������� ����� ������ ����� �������������� �� x: " << point.x << " �� y: " << point.y << endl;
	cout << "K��������� ������ ������� ����� �������������� �� x: " << point2.x << " �� y: " << point2.y << endl;
	cout << "���� �������: " << angle << endl;
}

void generate_segment(point_position& point, point_position& point2) {
	const int RANDOM_MIN = -100, RANDOM_MAX = 100 - RANDOM_MIN + 1;
	point.x = RANDOM_MIN + rand() / double(RANDOM_MAX);
	point.y = RANDOM_MIN + rand() / (double)RANDOM_MAX;
	point2.x = (point.x + 1) + rand() / (double)RANDOM_MAX;
	point2.y = (point.y + 1) + rand() / (double)RANDOM_MAX;
	cout << "K��������� ������ ������� �� x: " << point.x << " �� y: " << point.y << endl;
	cout << "K��������� ����� ������� �� x: " << point2.x << " �� y: " << point2.y << endl;
}

void data_output(point_position rectangle_bottom_left, point_position rectangle_top_right, double angle,
	point_position segment_begin, point_position segment_end) {
	cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _" << endl;
	cout << "�������� ������:" << endl;
	cout << "K��������� ����� ������ ����� �������������� �� x: " << rectangle_bottom_left.x << " �� y: " << rectangle_bottom_left.y << endl;
	cout << "K��������� ������ ������� ����� �������������� �� x: " << rectangle_top_right.x << " �� y: " << rectangle_top_right.y << endl;
	cout << "���� �������: " << angle << endl;
	cout << "K��������� ������ ������� �� x: " << segment_begin.x << " �� y: " << segment_begin.y << endl;
	cout << "K��������� ����� ������� �� x: " << segment_end.x << " �� y: " << segment_end.y << endl;
	cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _" << endl;
}

bool show_or_try(void) {
	cout << "��� ����, ����� �������� ����� ������� 1." << endl;
	cout << "��� ����, ����� ��������� ��������� ������� 2." << endl;
	int mode = 0;
	while (!((mode == TEST) || (mode == TRY))) {
		mode = get_int();
		switch (mode) {
		case TEST: return true;
			break;
		case TRY: return false;
			break;
		default: cout << "������� ���� 1, ���� 2." << endl;
		}
	}
}

void create_file(int mode, point_position& rectangle_bottom_left, point_position& rectangle_top_right, point_position& segment_begin, point_position& segment_end,
	point_position point_intersection1, point_position point_intersection2, double& angle, int quantity_points) {
	if (mode == READ) {
	here: cout << "������� ���� �����, �� �������� ������� ������." << endl
		<< "�������: C:\\\\�����1(���� ����������)\\\\�����2(���� ����������)\\\\...\\\\�������� �����.txt " << endl
		<< "���� ������� ������ �������� �����, ���� �� � ����� ����� �������."
		<< endl;
		  const int SIZE_NAME = 256;
		  string name = "";
		  cin >> name;
		  fstream output_file(name);
		  const int AMOUNT_DATA = 9;
		  double input_data[AMOUNT_DATA];
		  int i = 0;
		  for (; i < AMOUNT_DATA; i++) {
			  if (!(output_file >> input_data[i])) {
				  cout << "������������ ������." << endl;
				  output_file.close();
				  goto here;
				  break;
			  }
		  }

		  for (; i < AMOUNT_DATA; i++) {
			  output_file >> input_data[i];
		  }
		  rectangle_bottom_left.x = input_data[0];
		  rectangle_bottom_left.y = input_data[1];
		  rectangle_top_right.x = input_data[2];
		  rectangle_top_right.y = input_data[3];
		  angle = input_data[4];
		  segment_begin.x = input_data[5];
		  segment_begin.y = input_data[6];
		  segment_end.x = input_data[7];
		  segment_end.y = input_data[8];
		  data_output(rectangle_bottom_left, rectangle_top_right, angle, segment_begin, segment_end);
		  output_file.close();
	}
	else {
	path:cout << "������� ���� �����, � ������� ��������� ������." << endl << "�������: C:\\\\�����1(���� ����������)\\\\"
		"�����2(���� ����������)\\\\...\\\\�������� �����.txt " << endl << "���� ������� ������ �������� �����, ����� �� ����� � ����� ����� �������."
		<< endl;
		 string name = "";
		 cin >> name;
		 if (ifstream(name)) {
			 bool rewrite = true;
			 cout << "���� ��� ����������." << endl;
			 cout << "������� 0 ��� ����, ����� ������������ ������������ ����." << endl;
			 cout << "������� 1 ��� ����, ����� ��������� ����." << endl;
		 repeat: rewrite = get_int();
			 switch (rewrite) {
			 case 0: cout << "�� ������� ����� ������������ ����." << endl;
				 break;
			 case 1: cout << "�� ������� ����� ��������� ����." << endl;
				 goto path;
				 break;
			 default:
				 cout << "������� 1, ���� 2";
				 goto repeat;
			 }
		 }
		 ofstream result_file(name, ofstream::app);

		 error_code ec;
		 if (!is_regular_file(name, ec)) {
			 cout << "����� �������� ������������ ��������. ��������� ����." << endl;
			 ec.clear();
			 goto path;
		 }

		 result_file.clear();
		 switch (mode) {
		 case DATA:
			 result_file << rectangle_bottom_left.x << " " << rectangle_bottom_left.y << " " << rectangle_top_right.x << " " << rectangle_top_right.y << " "
				 << angle << " " << segment_begin.x << " " << segment_begin.y << " " << segment_end.x << " " << segment_end.y;
			 break;
		 case RESULT:
			 result_file
				 << "��������� ���������: " << endl;
			 switch (quantity_points) {
			 case INFINITY_INTERSECTIONS:
				 result_file << "����������� ��������� �����������" << endl;
				 break;
			 case 0:
				 result_file << "��� �����������" << endl;
				 break;
			 case 1:
				 result_file << "������ ����� ����������� �� x: " << point_intersection1.x << " �� y: " << point_intersection1.y << endl;
				 result_file << "������ ����� ����������� ���" << endl;
				 break;
			 case 2:
				 result_file << "������ ����� ����������� �� x: " << point_intersection1.x << " �� y: " << point_intersection1.y << endl;
				 result_file << "������ ����� ����������� �� x: " << point_intersection2.x << " �� y: " << point_intersection2.y << endl;
				 break;
			 }

			 break;
		 }
		 result_file.close();

	}
}

void greetings() {
	cout << "��������� ��������� ������� ������ ����������." << endl << "������: 404." << endl << "�������: 22." << endl <<
		"������ ����� 9:" << endl <<
		"��� ��������� �������������� � ������� �� ��������� ����������, ������������ �� ���." << endl << "����� ���������� ����� �����������."
		<< endl;
}

void input_types(point_position& rectangle_bottom_left, point_position& rectangle_top_right, point_position& segment_begin, point_position& segment_end, double& angle,
	int& mode) {
	cout << "�������� ���� ��������� �������������� � �������:" << endl << "������� 1 ��� ����� �������." << endl
		<< "������� 2 ��� ��������� ��������� ���������." << endl << "������� 3 ��� ������������� �������� ������ �� �����." << endl;
again: int menu_type = get_int();
	mode = menu_type;
	switch (menu_type) {
	case MANUAL:
		cout << "�� ������� ����� ����� �������." << endl;
		input_rectangle(rectangle_bottom_left, rectangle_top_right, angle);
		input_segment(segment_begin, segment_end);
		cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _" << endl;
		break;
	case GENERATE:
		cout << "�� ������� ����� ���������." << endl;
		generate_recatngle(rectangle_bottom_left, rectangle_top_right, angle);
		generate_segment(segment_begin, segment_end);
		cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _" << endl;
		break;
	case FILE_INPUT:
		cout << "�� ������� ����� ����� ������ �� �����." << endl;
		create_file(READ, rectangle_bottom_left, rectangle_top_right, segment_begin, segment_end, segment_end, segment_end, angle, 0);
		break;
	default:
		cout << "������� ���� 1, ���� 2, ���� 3." << endl;
		goto again;
	}
}

bool end_program() {
	cout << "��������� ���������? " << endl << "������� 0 ��� ����������." << endl << "������� 1 ��� �������." << endl;
	while (true) {
		int end = get_int();
		switch (end) {
		case END:
			cout << "��������� �����������..." << endl;
			return true;
			break;
		case CONTINUE:
			cout << "�� ������� ��������� ���������: " << endl;
			return false;
			break;
		default:
			cout << "������� ���� 0, ���� 1." << endl;
		}
	}
	
}


void output_results(point_position point_intersection1, point_position point_intersection2, int quantity_points) {
	cout << "���������� ���������: " << endl;
	switch (quantity_points) {
	case INFINITY_INTERSECTIONS:
		cout << "����������� ��������� �����������" << endl;
		break;
	case NO_INTERSECTIONS:
		cout << "��� �����������" << endl;
		break;
	case ONE_POINT:
		cout << "������ ����� ����������� �� x: " << point_intersection1.x << " �� y: " << point_intersection1.y << endl;
		cout << "������ ����� ����������� ���" << endl;
		break;
	case TWO_POINTS:
		cout << "������ ����� ����������� �� x: " << point_intersection1.x << " �� y: " << point_intersection1.y << endl;
		cout << "������ ����� ����������� �� x: " << point_intersection2.x << " �� y: " << point_intersection2.y << endl;
		break;
	}
	cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _" << endl;

}

void saving_results(point_position& rectangle_bottom_left, point_position& rectangle_top_right, point_position& segment_begin, point_position& segment_end,
	point_position point_intersection1, point_position point_intersection2) {
	cout << "����a���� ���������� � ��������� �����?" << endl << "������� 1 ��� ����������." << endl << "������� 2, ����� ���������� ����������." << endl;
	double angle = 0;
	while (true) {
		int save = get_int();
		if (save == YES) {
			create_file(RESULT, rectangle_bottom_left, rectangle_top_right, segment_begin, segment_end,
				point_intersection1, point_intersection2, angle, 0);
			break;
		}
		if (save == NO) {
			cout << "�� ������� ���������� ����������." << endl;
			break;
		}
		else 
		cout << "������� ���� 1, ���� 2." << endl;
	}

}

void save_data(point_position& rectangle_bottom_left, point_position& rectangle_top_right, point_position& segment_begin, point_position& segment_end, double& angle)
{
	cout << "�� ������ ��������� ������? ������� 1 - ��� ����������, 2 - ��� �������� ����������." << endl;
	while (true) {
		int save = get_int();
		if (save == YES) {
			create_file(DATA, rectangle_bottom_left, rectangle_top_right, segment_begin, segment_end, segment_end, segment_end, angle, 0);
			cout << "������ ���������." << endl;
			break;
		}
		if (save == NO) {
			cout << "�� ������� ���������� ����������." << endl;
			break;
		}
		else
			cout << "������� ���� 1, ���� 2." << endl;
		}
}
