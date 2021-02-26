#pragma once
#include"MyShape.h"
#include<vector>
#include"myVector.h"
namespace MgGeometryType2D
{
	class Polygon;
}
class MgGeometryType2D::Polygon
{
public:
	Polygon() {};
	Polygon(int n,const Vec2D pos1, ...);
	Polygon(int n, const  Vec2D* pos1);		//数组生成
	Polygon(const RECT rect);					//rect生成
	//copy
	Polygon(const Polygon& pol);
	virtual Polygon& operator=(const Polygon& pol);

	void Set(const Vec2D* points, int32 count);
	//获取个点的数据
	Vec2D& operator[](const size_t n);
	const Vec2D& operator[](const size_t n) const ;

	//获取某条边的向量数据
	TC::Vector2D getSide(const size_t n);

	//获取组数据
	std::vector<Vec2D>& getData();

	void ComputeAABB(b2AABB* aabb, const Transform& transform, int32 childIndex = 0);

	//获取维数
	size_t Extent();

	//平移
	void Move(TC::Vector2D);


protected:
	std::vector<Vec2D> MultiPOINT;
};

namespace MgGeometryType2D
{
	inline size_t Polygon::Extent() { return MultiPOINT.size(); }

	inline  std::vector<Vec2D>& Polygon::getData()
	{
		return MultiPOINT;
	}

	inline Vec2D& Polygon::operator[](const size_t n)
	{
		return MultiPOINT[n];
	}
	inline const Vec2D& Polygon::operator[] (const size_t n)const
	{
		return MultiPOINT[n];
	}
	inline TC::Vector2D Polygon::getSide(size_t n)
	{
		if (n > MultiPOINT.size() && n < 1)return TC::Vector2D(0, 0);
		if (n != MultiPOINT.size())return TC::Vector2D((double)MultiPOINT[n].x - MultiPOINT[n - 1].x, (double)MultiPOINT[n].y - MultiPOINT[n - 1].y);
		else return TC::Vector2D((double)MultiPOINT[0].x - MultiPOINT[n - 1].x, (double)MultiPOINT[0].y - MultiPOINT[n - 1].y);
	}
}

#define Good
#define maxPolygonVertices	16
class PolygonShape : public Shape
{
public:
	PolygonShape();

	/// Implement b2Shape.
	Good Shape* Clone(/*b2BlockAllocator* allocator*/) const override;

	/// @see b2Shape::GetChildCount
	Good int32 GetChildCount() const override;

	/// Create a convex hull from the given array of local points.
	/// The count must be in the range [3, b2_maxPolygonVertices].
	/// @warning the points may be re-ordered, even if they form a convex polygon
	/// @warning collinear points are handled but not removed. Collinear points
	/// may lead to poor stacking behavior.
	Good void Set(const Vec2D* points, int32 count);

	/// Build vertices to represent an axis-aligned box centered on the local origin.
	/// @param hx the half-width.
	/// @param hy the half-height.
	Good void SetAsBox(double hx, double hy);

	/// Build vertices to represent an oriented box.
	/// @param hx the half-width.
	/// @param hy the half-height.
	/// @param center the center of the box in local coordinates.
	/// @param angle the rotation of the box in local coordinates.
	Good void SetAsBox(double hx, double hy, const Vec2D& center, double angle);

	/// @see b2Shape::TestPoint
	Good bool TestPoint(const Transform& transform, const Vec2D& p) const override;

	/// Implement b2Shape.
	/// @note because the polygon is solid, rays that start inside do not hit because the normal is
	/// not defined.
	Good bool RayCast(RayCastOutput* output, const RayCastInput& input,
		const Transform& transform, int32 childIndex) const override;

	/// @see b2Shape::ComputeAABB
	Good void ComputeAABB(b2AABB* aabb, const Transform& transform, int32 childIndex) const override;

	/// @see b2Shape::ComputeMass
	Good void ComputeMass(MassData* massData, double density) const override;

	/// Validate convexity. This is a very time consuming operation.
	/// @returns true if valid
	Good bool Validate() const;

	Vec2D m_centroid;
	Vec2D m_vertices[maxPolygonVertices];
	Vec2D m_normals[maxPolygonVertices];
	int32 m_count;
};

inline PolygonShape::PolygonShape()
{
	m_type = e_polygon;
	m_radius = polygonRadius;
	m_count = 0;
	m_centroid.SetZero();
}