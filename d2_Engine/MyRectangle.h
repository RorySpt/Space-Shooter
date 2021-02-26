#pragma once

#include"MyPolygon.h"
#include"myVector.h"
namespace MgGeometryType2D
{
	//矩形
	class gtRECT;
}
//
//class MgGeometryType2D::gtRECT :public Polygon
//{
//public:
//	gtRECT() {};
//	//使用内置矩形产生一个任意位置矩形，angle为以第一个点为原点的旋转角度
//	gtRECT(const RECT& rect, double angle)
//		:Polygon(4,
//			POINT_DB({ (double)rect.left,(double)rect.top }),
//			POINT_DB({ (double)rect.right,(double)rect.top }) + (TC::Vector2D((double)rect.right - rect.left, 0).Rotate(angle)),
//			POINT_DB({ (double)rect.right,(double)rect.bottom }) + (TC::Vector2D((double)rect.right - rect.left, (double)rect.bottom - rect.top).Rotate(angle)),
//			POINT_DB({ (double)rect.left,(double)rect.bottom }) + (TC::Vector2D(0, (double)rect.bottom - rect.top).Rotate(angle))
//		) {};
//	gtRECT(const RECT& rect)
//		:Polygon(4,
//			POINT_DB({ (double)rect.left,(double)rect.top }),
//			POINT_DB({ (double)rect.right,(double)rect.top }) ,
//			POINT_DB({ (double)rect.right,(double)rect.bottom }) ,
//			POINT_DB({ (double)rect.left,(double)rect.bottom })
//		) {};
//	gtRECT(const gtRECT& grect)
//	{
//		(*this).MultiPOINT = grect.MultiPOINT;
//	}
//	double left() const { return (*this)[0].x; };
//	double top() const { return (*this)[0].y; };
//	double right() const { return (*this)[2].x; };
//	double bottom() const { return (*this)[2].y; };
//};
//
