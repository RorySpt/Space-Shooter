#pragma once

#include"MyPolygon.h"
#include"myVector.h"
namespace MgGeometryType2D
{
	//����
	class gtRECT;
}
//
//class MgGeometryType2D::gtRECT :public Polygon
//{
//public:
//	gtRECT() {};
//	//ʹ�����þ��β���һ������λ�þ��Σ�angleΪ�Ե�һ����Ϊԭ�����ת�Ƕ�
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
