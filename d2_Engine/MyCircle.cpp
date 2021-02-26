#include "MyCircle.h"
Shape* CircleShape::Clone(/*BlockAllocator* allocator*/) const
{
	//void* mem = allocator->Allocate(sizeof(CircleShape));
	CircleShape* clone = new /*(mem)*/ CircleShape;
	*clone = *this;
	return clone;
}

int32 CircleShape::GetChildCount() const
{
	return 1;
}

bool CircleShape::TestPoint(const Transform& transform, const Vec2D& p) const
{
	Vec2D center = transform.p + Mul(transform.q, m_p);
	Vec2D d = p - center;
	return Dot(d, d) <= m_radius * m_radius;
}

// Collision Detection in Interactive 3D Environments by Gino van den Bergen
// From Section 3.1.2
// x = s + a * r
// norm(x) = radius
bool CircleShape::RayCast(RayCastOutput* output, const RayCastInput& input,
	const Transform& transform, int32 childIndex) const
{
	_NOT_USED(childIndex);

	Vec2D position = transform.p + Mul(transform.q, m_p);
	Vec2D s = input.p1 - position;
	double b = Dot(s, s) - m_radius * m_radius;

	// Solve quadratic equation.
	Vec2D r = input.p2 - input.p1;
	double c = Dot(s, r);
	double rr = Dot(r, r);
	double sigma = c * c - rr * b;

	// Check for negative discriminant and short segment.
	if (sigma < 0.0 || rr < _epsilon)
	{
		return false;
	}

	// Find the point of intersection of the line with the circle.
	double a = -(c + sqrt(sigma));

	// Is the intersection point on the segment?
	if (0.0 <= a && a <= input.maxFraction * rr)
	{
		a /= rr;
		output->fraction = a;
		output->normal = s + a * r;
		output->normal.Normalize();
		return true;
	}

	return false;
}

void CircleShape::ComputeAABB(b2AABB* aabb, const Transform& transform, int32 childIndex) const
{
	_NOT_USED(childIndex);

	Vec2D p = transform.p + Mul(transform.q, m_p);
	aabb->lowerBound.Set(p.x - m_radius, p.y - m_radius);
	aabb->upperBound.Set(p.x + m_radius, p.y + m_radius);
}

void CircleShape::ComputeMass(MassData* massData, double density) const
{
	massData->mass = density * PI * m_radius * m_radius;
	massData->center = m_p;

	// inertia about the local origin
	massData->I = massData->mass * (0.5 * m_radius * m_radius + Dot(m_p, m_p));
}
