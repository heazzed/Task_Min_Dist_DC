#pragma once
#include <string>
#include <cmath>
using std::string;

class Point
{
private:
	double x, y;
public:
	Point(double x, double y);
	Point(double value);
	Point();
	void setX(double x);
	double getX();
	void setY(double y);
	double getY();
	string get_point_as_string() const;
	double distance_to_point(Point p2);
	bool operator<(Point p);
	bool operator<=(Point p);
	bool operator==(Point p);
	bool operator!=(Point p);
	bool operator>=(Point p);
	bool operator>(Point p);
	static double distance_between_points(Point p1, Point p2);
	static double min_val(double x, double y);
	static void sort_by_X(Point* points, int count);
	static double find_min_dist_in_half(Point* points, int count, int start);
	static double min_dist(Point* points, int count);
};

