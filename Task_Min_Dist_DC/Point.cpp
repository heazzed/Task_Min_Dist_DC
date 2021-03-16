#include "Point.h"

	Point::Point(double x, double y) {
		this->x = x;
		this->y = y;
	}
	Point::Point(double value) {
		this->x = value;
		this->y = value;
	}
	Point::Point() {
		this->x = 0;
		this->y = 0;
	}

	void Point::setX(double x) {
		this->x = x;
	}
	double Point::getX() {
		return x;
	}
	void Point::setY(double y) {
		this->y = y;
	}
	double Point::getY() {
		return y;
	}

	string Point::get_point_as_string() const {
		string result = "(";
		result += std::to_string(this->x) + ", " + std::to_string(this->y) + ")";
		return result;
	}

	double Point::distance_to_point(Point p2) {
		return sqrt(((this->x - p2.x) * (this->x - p2.x)) + ((this->y - p2.y) * (this->y - p2.y)));
	}

	bool Point::operator<(Point p) {
		return this->x < p.x;
	}
	bool Point::operator<=(Point p) {
		return !(this->x > p.x);
	}
	bool Point::operator==(Point p) {
		return this->x == p.x;
	}
	bool Point::operator!=(Point p) {
		return !(this->x == p.x);
	}
	bool Point::operator>=(Point p) {
		return !(this->x < p.x);
	}
	bool Point::operator>(Point p) {
		return !(this->x <= p.x);
	}

	double Point::distance_between_points(Point p1, Point p2) {
		return sqrt(((p1.x - p2.x) * (p1.x - p2.x)) + ((p1.y - p2.y)) * (p1.y - p2.y));
	}

	double Point::min_val(double x, double y) {
		return (x < y) ? x : y;
	}

	void Point::sort_by_X(Point* points, int count) {
		for (int i = 0; i < count; i++)
		{
			for (int j = i + 1; j < count; j++)
			{
				if (points[i] > points[j])
				{
					Point pnt = points[j];
					points[j] = points[i];
					points[i] = pnt;
				}
			}
		}
	}

	double Point::find_min_dist_in_half(Point* points, int count, int start=0)
	{
		double min = DBL_MAX;
		for (int i = start; i < count; i++)
			if ((distance_between_points(points[i], points[i + 1])) < min)
				min = distance_between_points(points[i], points[i + 1]);
		return min;
	}

	double Point::min_dist(Point* points, int count) {
		sort_by_X(points, count);
		Point* strip = new Point[count];
		int mid = count / 2;
		double left_min = find_min_dist_in_half(points, mid);
		double right_min = find_min_dist_in_half(points, count, mid);
		double min = min_val(left_min, right_min);
		int j = 0;
		for (int i = 0; i < count; i++)
			if (abs(points[i].x - points[mid].x) < min)
				strip[j] = points[i], j++;
		for (int i = 0; i < j; i++)
			for (int k = i + 1; k < j && (strip[k].y - strip[i].y) < min; k++)
				if (distance_between_points(strip[i], strip[k]) < min)
					min = distance_between_points(strip[i], strip[k]);
		return min;
	}