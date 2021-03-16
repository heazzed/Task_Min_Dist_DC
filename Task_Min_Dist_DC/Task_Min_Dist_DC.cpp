#include "Point.h"
#include <iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "rus");
	int count;
	cout <<"Введите количество точек:";
	cin >> count;
	Point* points = new Point[count];
	for (int i = 0; i < count; i++) {
		double x, y;
		cin >> x >> y;
		points[i] = Point(x, y);
	}
	cout << "\n" << "Minimal distance is: " << Point::min_dist(points, count) << endl;
	delete[] points;
	system("pause");
	return 0;
}