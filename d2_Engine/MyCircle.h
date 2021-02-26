#pragma once
#include"MyShape.h"
class CircleShape:public Shape
{

public:
	CircleShape();

	/// Implement Shape.
	Shape* Clone(/*BlockAllocator* allocator*/) const override;

	/// @see Shape::GetChildCount
	int32 GetChildCount() const override;

	/// Implement Shape.
	bool TestPoint(const Transform& transform, const Vec2D& p) const override;

	/// Implement Shape.
	/// @note because the circle is solid, rays that start inside do not hit because the normal is
	/// not defined.
	bool RayCast(RayCastOutput* output, const RayCastInput& input,
		const Transform& transform, int32 childIndex) const override;

	/// @see Shape::ComputeAABB
	void ComputeAABB(b2AABB* aabb, const Transform& transform, int32 childIndex) const override;

	/// @see Shape::ComputeMass
	void ComputeMass(MassData* massData, double density) const override;

	/// Position
	Vec2D m_p;
};
inline CircleShape::CircleShape()
{
	m_type = e_circle;
	m_radius = 0.0f;
	m_p.SetZero();
}

