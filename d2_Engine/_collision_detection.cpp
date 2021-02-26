#include "_collision_detection.h"
#include<iostream>

//using namespace TC;
//两圆
namespace TC {
	using MgGeometryType2D::Cycle;
	using MgGeometryType2D::Polygon;
	bool TC::IsHit(Cycle cyc1, Cycle cyc2)
	{
		double dist_x = double(cyc1.position.x) - cyc2.position.x;
		double dist_y = double(cyc1.position.y) - cyc2.position.y;
		if ((dist_x * dist_x + dist_y * dist_y) < cyc1.radius + cyc2.radius)return true;
		else return false;
	}
	//两个规则矩形
	bool TC::IsHit(RECT rect1, RECT rect2)
	{
		if (rect1.left > rect2.right || rect1.right<rect2.left || rect1.top>rect2.bottom || rect1.bottom < rect2.top)return false;
		else return true;
	}
	/*bool IsHit(const MgGeometryType2D::gtRECT& rect1, const  MgGeometryType2D::gtRECT& rect2)
	{

		if(rect1[0].x>rect2[2].x|| rect1[0].y > rect2[2].y|| rect1[2].x < rect2[0].x || rect1[2].y < rect2[0].y)return false;
		else return true;
	}*/
	void CalAABB(b2AABB& Dst,const b2AABB& Src, const Transform& xf) {
		Vec2D Vertex[4] = {
		Src.lowerBound,
		{Src.lowerBound.x,Src.upperBound.y},
		Src.upperBound,
		{Src.upperBound.x,Src.lowerBound.y}
		};
		Transform tf(xf);
		tf.q.s = -tf.q.s;
		Vec2D lower = Mul(tf, Vertex[0]);
		Vec2D upper = lower;
		for (int i = 1; i < 4; ++i) {
			Vec2D v = Mul(tf, Vertex[i]);
			lower = Min(lower, v);
			upper = Max(upper, v);
		}
		Vec2D r(polygonRadius, polygonRadius);
		Dst.lowerBound = lower - r;
		Dst.upperBound = upper + r;
	}

	bool IsHit(const b2AABB &_a, const Transform&tf1, const b2AABB &_b, const  Transform& tf2) {

		b2AABB a , b ;
		CalAABB(a, _a, tf1);
		CalAABB(b, _b, tf2);
		return IsHit(a, b);
	}

	bool IsHit(const b2AABB& a, const b2AABB& b) {
		bool result = false;
		result = result || a.upperBound.x < b.lowerBound.x;
		result = result || a.upperBound.y < b.lowerBound.y;
		result = result || a.lowerBound.x > b.upperBound.x;
		result = result || a.lowerBound.y > b.upperBound.y;
		return !result;
	}
	bool TC::IsHit(MgGeometryType2D::Polygon pol1, MgGeometryType2D::Polygon pol2)
	{
		//选择一个点作为坐标原点
		Vec2D origin = pol1[0];
		for (size_t i(0); i < pol1.Extent(); ++i)
		{
			//选择一条边的垂线作为坐标轴
			Vector2D Axes(pol1.getSide(i + 1));
			Axes.Rotate(Vector2D(0, 1).Angle());
			//分别设置两个多边形的投影边界
			double pol1_max(- DBL_MAX);
			double pol1_min(DBL_MAX);
			double pol2_max(- DBL_MAX);
			double pol2_min(DBL_MAX);
			//对于多边形的每一个点以原点建立映射
			for (size_t j(0); j < pol1.Extent(); ++j)
			{
				//计算该点在坐标轴投影的长度
				double DropShadow = (Vector2D(double(pol1[j].x) - origin.x, double(pol1[j].y) - origin.y)).Drop(Axes);
				//分别记录投影的最大值和最小值
				if (DropShadow > pol1_max)pol1_max = DropShadow;
				if (DropShadow < pol1_min)pol1_min = DropShadow;
			}
			for (size_t k(0); k < pol2.Extent(); ++k)
			{
				double DropShadow = (Vector2D(double(pol2[k].x) - origin.x, double(pol2[k].y) - origin.y)).Drop(Axes);
				if (DropShadow > pol2_max)pol2_max = DropShadow;
				if (DropShadow < pol2_min)pol2_min = DropShadow;
			}
			//判断投影是否有重叠，没有则说明两个多边形没有重叠，直接返回
			if (pol1_max< pol2_min || pol1_min > pol2_max)return false;
		}
		//以另一个多边形的边垂线建立坐标轴
		for (size_t i(0); i < pol2.Extent(); ++i)
		{

			Vector2D Axes(pol2.getSide(i + 1));
			Axes.Rotate(Vector2D(0, 1).Angle());
			double pol1_max(DBL_MIN);
			double pol1_min(DBL_MAX);
			double pol2_max(DBL_MIN);
			double pol2_min(DBL_MAX);
			for (size_t j(0); j < pol1.Extent(); ++j)
			{
				double DropShadow = (Vector2D(double(pol1[j].x) - origin.x, double(pol1[j].y) - origin.y)).Drop(Axes);
				if (DropShadow > pol1_max)pol1_max = DropShadow;
				if (DropShadow < pol1_min)pol1_min = DropShadow;
			}
			for (size_t k(0); k < pol2.Extent(); ++k)
			{
				double DropShadow = (Vector2D(double(pol2[k].x) - origin.x, double(pol2[k].y) - origin.y)).Drop(Axes);
				if (DropShadow > pol2_max)pol2_max = DropShadow;
				if (DropShadow < pol2_min)pol2_min = DropShadow;
			}

			if (pol1_max< pol2_min && pol1_min > pol2_max)return false;
		}
		return true;
	}


	bool TC::IsHit(const MgGeometryType2D::Polygon& _pol1, const Transform &tf1, const MgGeometryType2D::Polygon& _pol2, const Transform& tf2)
	{
		MgGeometryType2D::Polygon pol1(_pol1);
		MgGeometryType2D::Polygon pol2(_pol2);
		if (pol1.Extent() == 0 || pol2.Extent() == 0)return false;
		for (int i = 0; i < pol1.Extent(); ++i) {
			pol1[i].RotateT(tf1.q) += tf1.p;
		}
		for (int i = 0; i < pol2.Extent(); ++i) {
			pol2[i].RotateT(tf2.q) += tf2.p;
		}



		//选择一个点作为坐标原点
		Vec2D origin = pol1[0];
		for (size_t i(0); i < pol1.Extent(); ++i)
		{
			//选择一条边的垂线作为坐标轴
			Vector2D Axes(pol1.getSide(i + 1));
			Axes.Rotate(Vector2D(0, 1).Angle());
			//分别设置两个多边形的投影边界
			double pol1_max(-DBL_MAX);
			double pol1_min(DBL_MAX);
			double pol2_max(-DBL_MAX);
			double pol2_min(DBL_MAX);
			//对于多边形的每一个点以原点建立映射
			for (size_t j(0); j < pol1.Extent(); ++j)
			{
				//计算该点在坐标轴投影的长度
				double DropShadow = (Vector2D(double(pol1[j].x) - origin.x, double(pol1[j].y) - origin.y)).Drop(Axes);
				//分别记录投影的最大值和最小值
				if (DropShadow > pol1_max)pol1_max = DropShadow;
				if (DropShadow < pol1_min)pol1_min = DropShadow;
			}
			for (size_t k(0); k < pol2.Extent(); ++k)
			{
				double DropShadow = (Vector2D(double(pol2[k].x) - origin.x, double(pol2[k].y) - origin.y)).Drop(Axes);
				if (DropShadow > pol2_max)pol2_max = DropShadow;
				if (DropShadow < pol2_min)pol2_min = DropShadow;
			}
			//判断投影是否有重叠，没有则说明两个多边形没有重叠，直接返回
			if (pol1_max< pol2_min || pol1_min > pol2_max)return false;
		}
		//以另一个多边形的边垂线建立坐标轴
		for (size_t i(0); i < pol2.Extent(); ++i)
		{

			Vector2D Axes(pol2.getSide(i + 1));
			Axes.Rotate(Vector2D(0, 1).Angle());
			double pol1_max(DBL_MIN);
			double pol1_min(DBL_MAX);
			double pol2_max(DBL_MIN);
			double pol2_min(DBL_MAX);
			for (size_t j(0); j < pol1.Extent(); ++j)
			{
				double DropShadow = (Vector2D(double(pol1[j].x) - origin.x, double(pol1[j].y) - origin.y)).Drop(Axes);
				if (DropShadow > pol1_max)pol1_max = DropShadow;
				if (DropShadow < pol1_min)pol1_min = DropShadow;
			}
			for (size_t k(0); k < pol2.Extent(); ++k)
			{
				double DropShadow = (Vector2D(double(pol2[k].x) - origin.x, double(pol2[k].y) - origin.y)).Drop(Axes);
				if (DropShadow > pol2_max)pol2_max = DropShadow;
				if (DropShadow < pol2_min)pol2_min = DropShadow;
			}

			if (pol1_max< pol2_min && pol1_min > pol2_max)return false;
		}
		return true;
	}
	bool TC::IsHit(MgGeometryType2D::Polygon pol, MgGeometryType2D::Cycle cyc)
	{
		//以圆心作为坐标原点
		POINT origin = cyc.position;
		//圆的阴影返回固定
		double cyc_max(cyc.radius);
		double cyc_min(-cyc.radius);
		for (size_t i(0); i < pol.Extent(); ++i)
		{
			//选择一条边的垂线作为坐标轴
			Vector2D Axes(pol.getSide(i + 1));
			Axes.Rotate(Vector2D(0, 1).Angle());
			//设置多边形的投影边界
			double pol_max(-DBL_MAX);
			double pol_min(DBL_MAX);
			
			//对于多边形的每一个点以原点建立映射
			for (size_t j(0); j < pol.Extent(); ++j)
			{
				//计算该点在坐标轴投影的长度
				double DropShadow = (Vector2D(double(pol[j].x) - origin.x, double(pol[j].y) - origin.y)).Drop(Axes);
				//分别记录投影的最大值和最小值
				if (DropShadow > pol_max)pol_max = DropShadow;
				if (DropShadow < pol_min)pol_min = DropShadow;
			}
			//判断投影是否有重叠，没有则说明两个多边形没有重叠，直接返回
			if (pol_max< cyc_min || pol_min > cyc_max)return false;
		}
		return true;
	}
	Vector2D dealHit_fix_mutex_static_dynamic(MgGeometryType2D::Polygon  Still, MgGeometryType2D::Polygon Animal, Vector2D &speed)
	{
		Animal.Move(-speed);
		MgGeometryType2D::Polygon& pol1 = Still;
		MgGeometryType2D::Polygon& pol2 = Animal;

		


		//选择一个点作为坐标原点
		Vec2D origin = pol1[0];
		//速度方向上的最近距离
		double dist_min(-DBL_MAX) ;
		double _dist_min(+DBL_MAX);
		Vector2D vec;
		Vector2D _vec;
		for (size_t i(0); i < pol1.Extent(); ++i)
		{
			//选择一条边的垂线作为坐标轴
			Vector2D Axes(pol1.getSide(i + 1));
			Axes.Rotate(Vector2D(0, 1).Angle());
			//分别设置两个多边形的投影边界
			double pol1_max(-DBL_MAX);
			double pol1_min(DBL_MAX);
			double pol2_max(-DBL_MAX);
			double pol2_min(DBL_MAX);
			//对于多边形的每一个点以原点建立映射
			for (size_t j(0); j < pol1.Extent(); ++j)
			{
				//计算该点在坐标轴投影的长度
				double DropShadow = (Vector2D(double(pol1[j].x) - origin.x, double(pol1[j].y) - origin.y)).Drop(Axes);
				//分别记录投影的最大值和最小值
				if (DropShadow > pol1_max)pol1_max = DropShadow;
				if (DropShadow < pol1_min)pol1_min = DropShadow;
			}
			for (size_t k(0); k < pol2.Extent(); ++k)
			{
				double DropShadow = (Vector2D(double(pol2[k].x) - origin.x, double(pol2[k].y) - origin.y)).Drop(Axes);
				if (DropShadow > pol2_max)pol2_max = DropShadow;
				if (DropShadow < pol2_min)pol2_min = DropShadow;
			}
			//判断投影是否有重叠，没有则说明两个多边形没有重叠
			if (pol1_max <= pol2_min + 0.001 || pol1_min >= pol2_max -0.001)
			{
				double min = abs(pol1_max - pol2_min) < abs(pol1_min - pol2_max) ? abs(pol1_max - pol2_min) : abs(pol1_min - pol2_max);
				/*Axes.Clamp(min);
				min = Axes.Drop(speed);*/

				//如果大与原间距记下投影轴
				vec = min > dist_min ? Axes : vec;
				dist_min = min > dist_min ? min : dist_min;
			}
			else//正常情况下不会触发else
			{
				double _min = abs(pol1_max - pol2_min) < abs(pol1_min - pol2_max) ? abs(pol1_max - pol2_min) : abs(pol1_min - pol2_max);
				_vec = _min < _dist_min ? Axes : _vec;
				_dist_min = _min < _dist_min ? _min : _dist_min;
			}

			
		}
		//以另一个多边形的边垂线建立坐标轴
		for (size_t i(0); i < pol2.Extent(); ++i)
		{

			Vector2D Axes(pol2.getSide(i + 1));
			Axes.Rotate(Vector2D(0, 1).Angle());
			double pol1_max(DBL_MIN);
			double pol1_min(DBL_MAX);
			double pol2_max(DBL_MIN);
			double pol2_min(DBL_MAX);
			for (size_t j(0); j < pol1.Extent(); ++j)
			{
				double DropShadow = (Vector2D(double(pol1[j].x) - origin.x, double(pol1[j].y) - origin.y)).Drop(Axes);
				if (DropShadow > pol1_max)pol1_max = DropShadow;
				if (DropShadow < pol1_min)pol1_min = DropShadow;
			}
			for (size_t k(0); k < pol2.Extent(); ++k)
			{
				double DropShadow = (Vector2D(double(pol2[k].x) - origin.x, double(pol2[k].y) - origin.y)).Drop(Axes);
				if (DropShadow > pol2_max)pol2_max = DropShadow;
				if (DropShadow < pol2_min)pol2_min = DropShadow;
			}
			if (pol1_max <= pol2_min + 0.001 || pol1_min >= pol2_max - 0.001)
			{
				double min = abs(pol1_max - pol2_min) < abs(pol1_min - pol2_max) ? abs(pol1_max - pol2_min) : abs(pol1_min - pol2_max);
				/*Axes.Clamp(min);
				min = Axes.Drop(speed);*/
				vec = min > dist_min ? Axes : vec;
				dist_min = min > dist_min ? min : dist_min;
				
			}
			else//正常情况下不会触发else
			{
				double _min = abs(pol1_max - pol2_min) < abs(pol1_min - pol2_max) ? abs(pol1_max - pol2_min) : abs(pol1_min - pol2_max);
				_vec = _min < _dist_min ? Axes : _vec;
				_dist_min = _min < _dist_min ? _min : _dist_min;
			}
		}
		if (dist_min == -DBL_MAX)//正常情况下不会触发
		{
			double angle = _vec ^ speed;
			if (angle > PI / 2 && angle < -PI / 2)vec = -vec;
			double temp = speed.Drop(vec);
			Vector2D ret = vec;
			ret.Clamp(-(temp + _dist_min+ 1));
			
			_vec.Clamp(_dist_min - 1);
			speed -= vec.Clamp(temp + 0.000001);
			//speed.y /= 2;
			//printf("重叠\n");
			return ret;

		}
		//return speed.Clamp(dist_min);
		//求出和速度小于90度夹角
  		double angle = vec ^ speed;
		if (angle > PI / 2|| angle < -PI / 2)vec = -vec;
		//代入距离
		vec.Clamp(dist_min);

		double temp = speed.Drop(vec);
		/*Vector2D ret = speed; 
		ret.Clamp( -(temp - dist_min) / temp * speed.Length());*/
		Vector2D ret = vec;
		ret.Clamp(-(temp - dist_min + 0.0000001 ));
		//更改速度
		speed -= vec.Clamp( temp + 0.0000000001);
		/*printf("未重叠\n");*/
		return ret;

	}


//
//	Vector2D dealHit(const RECT& still, const RECT& Animal,  Vector2D& speed)
//	{
//		TC::Vector2D vec;
//
//		POINT posa = POINT({ Animal.left, Animal.top });
//		POINT posb = POINT({ Animal.right, Animal.bottom });
//		posa = posa + (-speed);
//		posb = posb + (-speed);
//		RECT plrec = RECT{ posa.x ,posa.y ,posb.x ,posb.y };
//		RECT grrec = still;
//
//		//在下
//		if (plrec.top >= grrec.bottom)
//		{
//			vec.y = (double)grrec.bottom - Animal.top;
//			if (speed.y < 0)speed.y = 0;
//		}
//		//在上
//		else if (plrec.bottom <= grrec.top)
//		{
//			vec.y = (double)grrec.top - Animal.bottom;
//			if (speed.y > 0)speed.y = 0;
//		}
//		//在左
//		else if (plrec.right <= grrec.left)
//		{
//			vec.x = (double)grrec.left - Animal.right;
//			if (speed.x > 0)speed.x = 0;
//		}
//		//在右
//		else if (plrec.left >= grrec.right)
//		{
//			vec.x = (double)grrec.right - Animal.left;
//			if (speed.x < 0)speed.x = 0;
//		}
//
//		return vec;
//		//player.move(vec);
//	}
//	Vector2D dealHit_base_mutex_static_dynamic(const MgGeometryType2D::gtRECT& still, const  MgGeometryType2D::gtRECT& Animal, Vector2D& speed)
//	{
//		TC::Vector2D vec;
//		MgGeometryType2D::gtRECT Animal_be(Animal);
//		Animal_be.Move(-speed);
//		//在下
//		if (Animal_be.top() >= still.bottom())
//		{
//			vec.y = still.bottom() - Animal.top() + 0.000001;
//			if (speed.y < 0)speed.y = 0;
//		}
//		//在上
//		else if (Animal_be.bottom() <= still.top())
//		{
//			vec.y = still.top() - Animal.bottom() - 0.000001;
//			if (speed.y > 0)speed.y = 0;
//		}
//		//在左
//		else if (Animal_be.right() <= still.left())
//		{
//			vec.x = still.left() - Animal.right() - 0.000001;
//			if (speed.x > 0)speed.x = 0;
//		}
//		//在右
//		else if (Animal_be.left() >= still.right())
//		{
//			vec.x = still.right() - Animal.left() + 0.000001;
//			if (speed.x < 0)speed.x = 0;
//		}
//		return vec;
//	}
}






void CollideCircles(
	Manifold* manifold,
	const CircleShape* circleA, const Transform& xfA,
	const CircleShape* circleB, const Transform& xfB)
{
	manifold->pointCount = 0;

	Vec2D pA = Mul(xfA, circleA->m_p);
	Vec2D pB = Mul(xfB, circleB->m_p);

	Vec2D d = pB - pA;
	double distSqr = Dot(d, d);
	double rA = circleA->m_radius, rB = circleB->m_radius;
	double radius = rA + rB;
	if (distSqr > radius * radius)
	{
		return;
	}

	manifold->type = Manifold::e_circles;
	manifold->localPoint = circleA->m_p;
	manifold->localNormal.SetZero();
	manifold->pointCount = 1;

	manifold->points[0].localPoint = circleB->m_p;
	manifold->points[0].id.key = 0;
}

void CollidePolygonAndCircle(
	Manifold* manifold,
	const PolygonShape* polygonA, const Transform& xfA,
	const CircleShape* circleB, const Transform& xfB)
{
	manifold->pointCount = 0;

	// Compute circle position in the frame of the polygon.
	Vec2D c = Mul(xfB, circleB->m_p);
	Vec2D cLocal = MulT(xfA, c);

	// Find the min separating edge.
	int32 normalIndex = 0;
	double separation = -maxDouble;
	double radius = polygonA->m_radius + circleB->m_radius;
	int32 vertexCount = polygonA->m_count;
	const Vec2D* vertices = polygonA->m_vertices;
	const Vec2D* normals = polygonA->m_normals;

	for (int32 i = 0; i < vertexCount; ++i)
	{
		double s = Dot(normals[i], cLocal - vertices[i]);

		if (s > radius)
		{
			// Early out.
			return;
		}

		if (s > separation)
		{
			separation = s;
			normalIndex = i;
		}
	}

	// Vertices that subtend the incident face.
	int32 vertIndex1 = normalIndex;
	int32 vertIndex2 = vertIndex1 + 1 < vertexCount ? vertIndex1 + 1 : 0;
	Vec2D v1 = vertices[vertIndex1];
	Vec2D v2 = vertices[vertIndex2];

	// If the center is inside the polygon ...
	if (separation < _epsilon)
	{
		manifold->pointCount = 1;
		manifold->type = Manifold::e_faceA;
		manifold->localNormal = normals[normalIndex];
		manifold->localPoint = 0.5f * (v1 + v2);
		manifold->points[0].localPoint = circleB->m_p;
		manifold->points[0].id.key = 0;
		return;
	}

	// Compute barycentric coordinates
	double u1 = Dot(cLocal - v1, v2 - v1);
	double u2 = Dot(cLocal - v2, v1 - v2);
	if (u1 <= 0.0)
	{
		if (DistanceSquared(cLocal, v1) > radius * radius)
		{
			return;
		}

		manifold->pointCount = 1;
		manifold->type = Manifold::e_faceA;
		manifold->localNormal = cLocal - v1;
		manifold->localNormal.Normalize();
		manifold->localPoint = v1;
		manifold->points[0].localPoint = circleB->m_p;
		manifold->points[0].id.key = 0;
	}
	else if (u2 <= 0.0)
	{
		if (DistanceSquared(cLocal, v2) > radius * radius)
		{
			return;
		}

		manifold->pointCount = 1;
		manifold->type = Manifold::e_faceA;
		manifold->localNormal = cLocal - v2;
		manifold->localNormal.Normalize();
		manifold->localPoint = v2;
		manifold->points[0].localPoint = circleB->m_p;
		manifold->points[0].id.key = 0;
	}
	else
	{
		Vec2D faceCenter = 0.5 * (v1 + v2);
		double s = Dot(cLocal - faceCenter, normals[vertIndex1]);
		if (s > radius)
		{
			return;
		}

		manifold->pointCount = 1;
		manifold->type = Manifold::e_faceA;
		manifold->localNormal = normals[vertIndex1];
		manifold->localPoint = faceCenter;
		manifold->points[0].localPoint = circleB->m_p;
		manifold->points[0].id.key = 0;
	}
}



// Find the max separation between poly1 and poly2 using edge normals from poly1.
static double FindMaxSeparation(int32* edgeIndex,
	const PolygonShape* poly1, const Transform& xf1,
	const PolygonShape* poly2, const Transform& xf2)
{
	int32 count1 = poly1->m_count;
	int32 count2 = poly2->m_count;
	const Vec2D* n1s = poly1->m_normals;
	const Vec2D* v1s = poly1->m_vertices;
	const Vec2D* v2s = poly2->m_vertices;
	Transform xf = MulT(xf2, xf1);

	int32 bestIndex = 0;
	double maxSeparation = -maxDouble;
	for (int32 i = 0; i < count1; ++i)
	{
		// Get poly1 normal in frame2.
		Vec2D n = Mul(xf.q, n1s[i]);
		Vec2D v1 = Mul(xf, v1s[i]);

		// Find deepest point for normal i.
		double si = maxDouble;
		for (int32 j = 0; j < count2; ++j)
		{
			double sij = Dot(n, v2s[j] - v1);
			if (sij < si)
			{
				si = sij;
			}
		}

		if (si > maxSeparation)
		{
			maxSeparation = si;
			bestIndex = i;
		}
	}

	*edgeIndex = bestIndex;
	return maxSeparation;
}

static void FindIncidentEdge(ClipVertex c[2],
	const PolygonShape* poly1, const Transform& xf1, int32 edge1,
	const PolygonShape* poly2, const Transform& xf2)
{
	const Vec2D* normals1 = poly1->m_normals;

	int32 count2 = poly2->m_count;
	const Vec2D* vertices2 = poly2->m_vertices;
	const Vec2D* normals2 = poly2->m_normals;

	_Assert(0 <= edge1 && edge1 < poly1->m_count);

	// Get the normal of the reference edge in poly2's frame.
	Vec2D normal1 = MulT(xf2.q, Mul(xf1.q, normals1[edge1]));

	// Find the incident edge on poly2.
	int32 index = 0;
	double minDot = maxDouble;
	for (int32 i = 0; i < count2; ++i)
	{
		double dot = Dot(normal1, normals2[i]);
		if (dot < minDot)
		{
			minDot = dot;
			index = i;
		}
	}

	// Build the clip vertices for the incident edge.
	int32 i1 = index;
	int32 i2 = i1 + 1 < count2 ? i1 + 1 : 0;

	c[0].v = Mul(xf2, vertices2[i1]);
	c[0].id.cf.indexA = (uint8)edge1;
	c[0].id.cf.indexB = (uint8)i1;
	c[0].id.cf.typeA = ContactFeature::e_face;
	c[0].id.cf.typeB = ContactFeature::e_vertex;

	c[1].v = Mul(xf2, vertices2[i2]);
	c[1].id.cf.indexA = (uint8)edge1;
	c[1].id.cf.indexB = (uint8)i2;
	c[1].id.cf.typeA = ContactFeature::e_face;
	c[1].id.cf.typeB = ContactFeature::e_vertex;
}
int32 ClipSegmentToLine(ClipVertex vOut[2], const ClipVertex vIn[2],
	const Vec2D& normal, double offset, int32 vertexIndexA)
{
	// Start with no output points
	int32 count = 0;

	// Calculate the distance of end points to the line
	double distance0 = Dot(normal, vIn[0].v) - offset;
	double distance1 = Dot(normal, vIn[1].v) - offset;

	// If the points are behind the plane
	if (distance0 <= 0.0) vOut[count++] = vIn[0];
	if (distance1 <= 0.0) vOut[count++] = vIn[1];

	// If the points are on different sides of the plane
	if (distance0 * distance1 < 0.0)
	{
		// Find intersection point of edge and plane
		double interp = distance0 / (distance0 - distance1);
		vOut[count].v = vIn[0].v + interp * (vIn[1].v - vIn[0].v);

		// VertexA is hitting edgeB.
		vOut[count].id.cf.indexA = static_cast<uint8>(vertexIndexA);
		vOut[count].id.cf.indexB = vIn[0].id.cf.indexB;
		vOut[count].id.cf.typeA = ContactFeature::e_vertex;
		vOut[count].id.cf.typeB = ContactFeature::e_face;
		++count;

		_Assert(count == 2);
	}

	return count;
}

// Find edge normal of max separation on A - return if separating axis is found
// Find edge normal of max separation on B - return if separation axis is found
// Choose reference edge as min(minA, minB)
// Find incident edge
// Clip

// The normal points from 1 to 2
void CollidePolygons(Manifold* manifold,
	const PolygonShape* polyA, const Transform& xfA,
	const PolygonShape* polyB, const Transform& xfB)
{
	manifold->pointCount = 0;
	double totalRadius = polyA->m_radius + polyB->m_radius;

	int32 edgeA = 0;
	double separationA = FindMaxSeparation(&edgeA, polyA, xfA, polyB, xfB);
	if (separationA > totalRadius)
		return;

	int32 edgeB = 0;
	double separationB = FindMaxSeparation(&edgeB, polyB, xfB, polyA, xfA);
	if (separationB > totalRadius)
		return;

	const PolygonShape* poly1;	// reference polygon
	const PolygonShape* poly2;	// incident polygon
	Transform xf1, xf2;
	int32 edge1;					// reference edge
	uint8 flip;
	const double k_tol = 0.1 * linearSlop;

	if (separationB > separationA + k_tol)
	{
		poly1 = polyB;
		poly2 = polyA;
		xf1 = xfB;
		xf2 = xfA;
		edge1 = edgeB;
		manifold->type = Manifold::e_faceB;
		flip = 1;
	}
	else
	{
		poly1 = polyA;
		poly2 = polyB;
		xf1 = xfA;
		xf2 = xfB;
		edge1 = edgeA;
		manifold->type = Manifold::e_faceA;
		flip = 0;
	}

	ClipVertex incidentEdge[2];
	FindIncidentEdge(incidentEdge, poly1, xf1, edge1, poly2, xf2);

	int32 count1 = poly1->m_count;
	const Vec2D* vertices1 = poly1->m_vertices;

	int32 iv1 = edge1;
	int32 iv2 = edge1 + 1 < count1 ? edge1 + 1 : 0;

	Vec2D v11 = vertices1[iv1];
	Vec2D v12 = vertices1[iv2];

	Vec2D localTangent = v12 - v11;
	localTangent.Normalize();

	Vec2D localNormal = Cross(localTangent, 1.0f);
	Vec2D planePoint = 0.5 * (v11 + v12);

	Vec2D tangent = Mul(xf1.q, localTangent);
	Vec2D normal = Cross(tangent, 1.0);

	v11 = Mul(xf1, v11);
	v12 = Mul(xf1, v12);

	// Face offset.
	double frontOffset = Dot(normal, v11);

	// Side offsets, extended by polytope skin thickness.
	double sideOffset1 = -Dot(tangent, v11) + totalRadius;
	double sideOffset2 = Dot(tangent, v12) + totalRadius;

	// Clip incident edge against extruded edge1 side edges.
	ClipVertex clipPoints1[2];
	ClipVertex clipPoints2[2];
	int np;

	// Clip to box side 1
	np = ClipSegmentToLine(clipPoints1, incidentEdge, -tangent, sideOffset1, iv1);

	if (np < 2)
		return;

	// Clip to negative box side 1
	np = ClipSegmentToLine(clipPoints2, clipPoints1, tangent, sideOffset2, iv2);

	if (np < 2)
	{
		return;
	}

	// Now clipPoints2 contains the clipped points.
	manifold->localNormal = localNormal;
	manifold->localPoint = planePoint;

	int32 pointCount = 0;
	for (int32 i = 0; i < maxManifoldPoints; ++i)
	{
		double separation = Dot(normal, clipPoints2[i].v) - frontOffset;

		if (separation <= totalRadius)
		{
			ManifoldPoint* cp = manifold->points + pointCount;
			cp->localPoint = MulT(xf2, clipPoints2[i].v);
			cp->id = clipPoints2[i].id;
			if (flip)
			{
				// Swap features
				ContactFeature cf = cp->id.cf;
				cp->id.cf.indexA = cf.indexB;
				cp->id.cf.indexB = cf.indexA;
				cp->id.cf.typeA = cf.typeB;
				cp->id.cf.typeB = cf.typeA;
			}
			++pointCount;
		}
	}

	manifold->pointCount = pointCount;
}
//bool b2TestOverlap(const Shape* shapeA, int32 indexA,
//	const Shape* shapeB, int32 indexB,
//	const Transform& xfA, const Transform& xfB)
//{
//	DistanceInput input;
//	input.proxyA.Set(shapeA, indexA);
//	input.proxyB.Set(shapeB, indexB);
//	input.transformA = xfA;
//	input.transformB = xfB;
//	input.useRadii = true;
//
//	SimplexCache cache;
//	cache.count = 0;
//
//	DistanceOutput output;
//
//	Distance(&output, &cache, &input);
//
//	return output.distance < 10.0f * b2_epsilon;
//}
