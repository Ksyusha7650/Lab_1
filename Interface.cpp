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
		cout << "Введите число." << endl;
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
		cout << "Введите число." << endl;
		cin >> input;
	}
	while (getchar() != '\n');
	return input;
}

double point_input() {
	double input = get_double();
	while (((INT64_MAX < input) || (input < INT64_MIN))) {
		cout << "Значение координаты не соответствует типу double." << endl
			<< "Введите число из данного диапазона: " << INT64_MIN << " / " << INT64_MAX << endl;
		input = get_double();
	}
	return input;
}

void input_segment(point_position& point, point_position& point2) {
	int check = 0;
	cout << "Введите координаты начала отрезка." << endl;
	cout << "Координата по х: ";
	point.x = point_input();
	cout << "Координата по у: ";
	point.y = point_input();
	cout << "Введите координаты конца отрезка." << endl;
	cout << "Координата по х: ";
	point2.x = point_input();
	cout << "Координата по у: ";
	point2.y = point_input();
	while ((point.x == point2.x) && (point.y == point2.y)) {
		cout << "Введите координаты отличные от начала отрезка." << endl;
		cout << "Координата по х: ";
		point2.x = point_input();
		cout << "Координата по у: ";
		point2.y = point_input();
	}
}

void input_rectangle(point_position& point, point_position& point2, double& angle) {
	int check = 0;
	cout << "Введите координаты левой нижней точки прямоугольника." << endl;
	cout << "Координата по х: ";
	point.x = point_input();
	cout << "Координата по у: ";
	point.y = point_input();
	cout << "Введите координаты правой верхней точки прямоугольника." << endl;
	cout << "Координата по х: ";
	point2.x = point_input();
	while ((point.x == point2.x) || (point.x > point2.x)) {
		if (point.x == point2.x) {
			cout << "Введите координату по х отличную от предыдущей." << endl;
			point2.x = point_input();
		}
		if (point.x > point2.x) {
			cout << "Введите координату по х больше предыдущей. Это правая координата." << endl;
			point2.x = point_input();
		}
	}
	check = 0;
	cout << "Координата по у: ";
	point2.y = point_input();
	while ((point.y == point2.y) || (point.y > point2.y)) {
		if (point.y == point2.y) {
			cout << "Введите координату по y отличную от предыдущей." << endl;
			point2.y = point_input();
		}
		if (point.y > point2.y) {
			cout << "Введите координату по y больше предыдущей. Это верхняя координата." << endl;
			point2.y = point_input();
		}
		else check = 1;
	}
	cout << "Введите угол наклона в радианах: " << endl;
	angle = get_double();
}

void generate_recatngle(point_position& point, point_position& point2, double& angle) {
	const int RANDOM_MIN = -100, RANDOM_MAX = 100 - RANDOM_MIN + 1, RANDOM_MIN_ANGLE = 0, RANDOM_MAX_ANGLE = 6;
	point.x = RANDOM_MIN + rand() / double(RANDOM_MAX);
	point.y = RANDOM_MIN + rand() / (double)RANDOM_MAX;
	point2.x = (point.x + 1) + rand() / (double)RANDOM_MAX;
	point2.y = (point.y + 1) + rand() / (double)RANDOM_MAX;
	angle = rand() % RANDOM_MAX_ANGLE + RANDOM_MIN_ANGLE;
	cout << "Kоординаты левой нижней точки прямоугольника по x: " << point.x << " по y: " << point.y << endl;
	cout << "Kоординаты правой верхней точки прямоугольника по x: " << point2.x << " по y: " << point2.y << endl;
	cout << "Угол наклона: " << angle << endl;
}

void generate_segment(point_position& point, point_position& point2) {
	const int RANDOM_MIN = -100, RANDOM_MAX = 100 - RANDOM_MIN + 1;
	point.x = RANDOM_MIN + rand() / double(RANDOM_MAX);
	point.y = RANDOM_MIN + rand() / (double)RANDOM_MAX;
	point2.x = (point.x + 1) + rand() / (double)RANDOM_MAX;
	point2.y = (point.y + 1) + rand() / (double)RANDOM_MAX;
	cout << "Kоординаты начала отрезка по x: " << point.x << " по y: " << point.y << endl;
	cout << "Kоординаты конца отрезка по x: " << point2.x << " по y: " << point2.y << endl;
}

void data_output(point_position rectangle_bottom_left, point_position rectangle_top_right, double angle,
	point_position segment_begin, point_position segment_end) {
	cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _" << endl;
	cout << "Исходные данные:" << endl;
	cout << "Kоординаты левой нижней точки прямоугольника по x: " << rectangle_bottom_left.x << " по y: " << rectangle_bottom_left.y << endl;
	cout << "Kоординаты правой верхней точки прямоугольника по x: " << rectangle_top_right.x << " по y: " << rectangle_top_right.y << endl;
	cout << "Угол наклона: " << angle << endl;
	cout << "Kоординаты начала отрезка по x: " << segment_begin.x << " по y: " << segment_begin.y << endl;
	cout << "Kоординаты конца отрезка по x: " << segment_end.x << " по y: " << segment_end.y << endl;
	cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _" << endl;
}

bool show_or_try(void) {
	cout << "Для того, чтобы показать тесты нажмите 1." << endl;
	cout << "Для того, чтобы запустить программу нажмите 2." << endl;
	int mode = 0;
	while (!((mode == TEST) || (mode == TRY))) {
		mode = get_int();
		switch (mode) {
		case TEST: return true;
			break;
		case TRY: return false;
			break;
		default: cout << "Введите либо 1, либо 2." << endl;
		}
	}
}

void create_file(int mode, point_position& rectangle_bottom_left, point_position& rectangle_top_right, point_position& segment_begin, point_position& segment_end,
	point_position point_intersection1, point_position point_intersection2, double& angle, int quantity_points) {
	if (mode == READ) {
	here: cout << "Введите путь файла, из которого берутся данные." << endl
		<< "Образец: C:\\\\Папка1(если необходимо)\\\\Папка2(если необходимо)\\\\...\\\\Название файла.txt " << endl
		<< "Либо введите просто название файла, если он в папке этого проекта."
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
				  cout << "Некорректные данные." << endl;
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
	path:cout << "Введите путь файла, в который запишутся данные." << endl << "Образец: C:\\\\Папка1(если необходимо)\\\\"
		"Папка2(если необходимо)\\\\...\\\\Название файла.txt " << endl << "Либо введите просто название файла, тогда он будет в папке этого проекта."
		<< endl;
		 string name = "";
		 cin >> name;
		 if (ifstream(name)) {
			 bool rewrite = true;
			 cout << "Файл уже существует." << endl;
			 cout << "Введите 0 для того, чтобы перезаписать существующий файл." << endl;
			 cout << "Введите 1 для того, чтобы повторить ввод." << endl;
		 repeat: rewrite = get_int();
			 switch (rewrite) {
			 case 0: cout << "Вы выбрали опцию перезаписать файл." << endl;
				 break;
			 case 1: cout << "Вы выбрали опцию повторить ввод." << endl;
				 goto path;
				 break;
			 default:
				 cout << "Введите 1, либо 2";
				 goto repeat;
			 }
		 }
		 ofstream result_file(name, ofstream::app);

		 error_code ec;
		 if (!is_regular_file(name, ec)) {
			 cout << "Адрес содержит недопустимые значения. Повторите ввод." << endl;
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
				 << "Результат программы: " << endl;
			 switch (quantity_points) {
			 case INFINITY_INTERSECTIONS:
				 result_file << "Бесконечное множество пересечений" << endl;
				 break;
			 case 0:
				 result_file << "Нет пересечений" << endl;
				 break;
			 case 1:
				 result_file << "Первая точка пересечения по x: " << point_intersection1.x << " по y: " << point_intersection1.y << endl;
				 result_file << "Второй точки пересечения нет" << endl;
				 break;
			 case 2:
				 result_file << "Первая точка пересечения по x: " << point_intersection1.x << " по y: " << point_intersection1.y << endl;
				 result_file << "Вторая точка пересечения по x: " << point_intersection2.x << " по y: " << point_intersection2.y << endl;
				 break;
			 }

			 break;
		 }
		 result_file.close();

	}
}

void greetings() {
	cout << "Программу выполнила Рухлова Ксения Алексеевна." << endl << "Группа: 404." << endl << "Вариант: 22." << endl <<
		"Задача номер 9:" << endl <<
		"Для заданного прямоугольника и отрезка на плоскости определить, пересекаются ли они." << endl << "Найти координаты точек пересечения."
		<< endl;
}

void input_types(point_position& rectangle_bottom_left, point_position& rectangle_top_right, point_position& segment_begin, point_position& segment_end, double& angle,
	int& mode) {
	cout << "Выберите ввод координат прямоугольника и отрезка:" << endl << "Введите 1 для ввода вручную." << endl
		<< "Введите 2 для генерации случайных координат." << endl << "Введите 3 для использования исходных данных из файла." << endl;
again: int menu_type = get_int();
	mode = menu_type;
	switch (menu_type) {
	case MANUAL:
		cout << "Вы выбрали режим ввода вручную." << endl;
		input_rectangle(rectangle_bottom_left, rectangle_top_right, angle);
		input_segment(segment_begin, segment_end);
		cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _" << endl;
		break;
	case GENERATE:
		cout << "Вы выбрали режим генерации." << endl;
		generate_recatngle(rectangle_bottom_left, rectangle_top_right, angle);
		generate_segment(segment_begin, segment_end);
		cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _" << endl;
		break;
	case FILE_INPUT:
		cout << "Вы выбрали режим ввода данных из файла." << endl;
		create_file(READ, rectangle_bottom_left, rectangle_top_right, segment_begin, segment_end, segment_end, segment_end, angle, 0);
		break;
	default:
		cout << "Введите либо 1, либо 2, либо 3." << endl;
		goto again;
	}
}

bool end_program() {
	cout << "Повторить программу? " << endl << "Введите 0 для завершения." << endl << "Введите 1 для повтора." << endl;
	while (true) {
		int end = get_int();
		switch (end) {
		case END:
			cout << "Программа завершается..." << endl;
			return true;
			break;
		case CONTINUE:
			cout << "Вы выбрали повторить программу: " << endl;
			return false;
			break;
		default:
			cout << "Введите либо 0, либо 1." << endl;
		}
	}
	
}


void output_results(point_position point_intersection1, point_position point_intersection2, int quantity_points) {
	cout << "Результаты программы: " << endl;
	switch (quantity_points) {
	case INFINITY_INTERSECTIONS:
		cout << "Бесконечное множество пересечений" << endl;
		break;
	case NO_INTERSECTIONS:
		cout << "Нет пересечений" << endl;
		break;
	case ONE_POINT:
		cout << "Первая точка пересечения по x: " << point_intersection1.x << " по y: " << point_intersection1.y << endl;
		cout << "Второй точки пересечения нет" << endl;
		break;
	case TWO_POINTS:
		cout << "Первая точка пересечения по x: " << point_intersection1.x << " по y: " << point_intersection1.y << endl;
		cout << "Вторая точка пересечения по x: " << point_intersection2.x << " по y: " << point_intersection2.y << endl;
		break;
	}
	cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _" << endl;

}

void saving_results(point_position& rectangle_bottom_left, point_position& rectangle_top_right, point_position& segment_begin, point_position& segment_end,
	point_position point_intersection1, point_position point_intersection2) {
	cout << "Сохрaнить результаты в отдельном файле?" << endl << "Введите 1 для сохранения." << endl << "Введите 2, чтобы пропустить сохранение." << endl;
	double angle = 0;
	while (true) {
		int save = get_int();
		if (save == YES) {
			create_file(RESULT, rectangle_bottom_left, rectangle_top_right, segment_begin, segment_end,
				point_intersection1, point_intersection2, angle, 0);
			break;
		}
		if (save == NO) {
			cout << "Вы выбрали пропустить сохранение." << endl;
			break;
		}
		else 
		cout << "Введите либо 1, либо 2." << endl;
	}

}

void save_data(point_position& rectangle_bottom_left, point_position& rectangle_top_right, point_position& segment_begin, point_position& segment_end, double& angle)
{
	cout << "Вы хотите сохранить данные? Введите 1 - для сохранения, 2 - для пропуска сохранения." << endl;
	while (true) {
		int save = get_int();
		if (save == YES) {
			create_file(DATA, rectangle_bottom_left, rectangle_top_right, segment_begin, segment_end, segment_end, segment_end, angle, 0);
			cout << "Данные сохранены." << endl;
			break;
		}
		if (save == NO) {
			cout << "Вы выбрали пропустить сохранение." << endl;
			break;
		}
		else
			cout << "Введите либо 1, либо 2." << endl;
		}
}
