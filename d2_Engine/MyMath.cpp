#include "MyMath.h"
namespace TC
{
	Vector2D::Vector2D(const double x_, const double y_) :x(x_), y(y_) {}
	//Vector2D::Vector2D(double length, double angle)
	//{
	//	x = length * cos(angle);
	//	y = length * sin(angle);
	//}

	Vector2D::Vector2D(POINT_DB begin, POINT_DB end)
	{
		x = (double)end.x - begin.x;
		y = (double)end.y - begin.y;
	}
	Vector2D::Vector2D(const double length, const Vector2D& v)
	{
		x = v.x;
		y = v.y;
		Clamp(length);
	}

	Vector2D::Vector2D(const Vector2D& v, double angle)
	{
		double length = v.Length();
		x = length * cos(angle);
		y = length * sin(angle);
	}

}
