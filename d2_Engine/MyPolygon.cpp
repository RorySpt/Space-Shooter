#include "MyPolygon.h"
using namespace MgGeometryType2D;
Polygon::Polygon(int n, const Vec2D pos1, ...)
{
	MultiPOINT.push_back(pos1);
	if(n>1)
	{
		va_list args;
		va_start(args, pos1);
		while (--n)
		{
			MultiPOINT.push_back(va_arg(args,Vec2D));
		}
		va_end(args);
	}
}

Polygon::Polygon(int n, const  Vec2D* pos1)
{
	while (n--)
	{
		MultiPOINT.push_back(*(pos1++));
	}
}

Polygon::Polygon(const RECT rect)
{
	MultiPOINT.push_back({ (double)rect.left,(double)rect.top });
	MultiPOINT.push_back({ (double)rect.right,(double)rect.top });
	MultiPOINT.push_back({ (double)rect.right,(double)rect.bottom });
	MultiPOINT.push_back({ (double)rect.left ,(double)rect.bottom });
}


Polygon::Polygon(const Polygon& pol)
{
	MultiPOINT = pol.MultiPOINT;
}
MgGeometryType2D::Polygon& Polygon::operator=(const Polygon& pol)
{
	MultiPOINT = pol.MultiPOINT;
	return *this;
}


void Polygon::Move(TC::Vector2D vec)
{
	for (auto &cur : MultiPOINT)
	{
		cur = cur + vec;
	}
}
void Polygon::Set(const Vec2D* points, int32 count)
{
	MultiPOINT.resize(count);

	for (int i = 0; i < count; ++i) {
		MultiPOINT[i] = points[i];
	}
}
void Polygon::ComputeAABB(b2AABB* aabb, const Transform& xf, int32 childIndex) {

	_NOT_USED(childIndex);

	Vec2D lower = Mul(xf, MultiPOINT[0]);
	Vec2D upper = lower;

	for (int32 i = 1; i < MultiPOINT.size(); ++i)
	{
		Vec2D v = Mul(xf, MultiPOINT[i]);
		lower = Min(lower, v);
		upper = Max(upper, v);
	}
	Vec2D r(polygonRadius, polygonRadius);
	aabb->lowerBound = lower - r;
	aabb->upperBound = upper + r;
}


Shape* PolygonShape::Clone(/*b2BlockAllocator* allocator*/) const
{
	//void* mem = allocator->Allocate(sizeof(b2PolygonShape));//?
	PolygonShape* clone = new /*(mem)*/ PolygonShape;
	*clone = *this;
	return clone;
}

void PolygonShape::SetAsBox(double hx, double hy)
{
	m_count = 4;
	m_vertices[0].Set(-hx, -hy);
	m_vertices[1].Set(hx, -hy);
	m_vertices[2].Set(hx, hy);
	m_vertices[3].Set(-hx, hy);
	m_normals[0].Set(0.0, -1.0);
	m_normals[1].Set(1.0, 0.0);
	m_normals[2].Set(0.0, 1.0);
	m_normals[3].Set(-1.0, 0.0);
	m_centroid.SetZero();
}

void PolygonShape::SetAsBox(double hx, double hy, const Vec2D& center, double angle)
{
	m_count = 4;
	m_vertices[0].Set(-hx, -hy);
	m_vertices[1].Set(hx, -hy);
	m_vertices[2].Set(hx, hy);
	m_vertices[3].Set(-hx, hy);
	m_normals[0].Set(0.0, -1.0);
	m_normals[1].Set(1.0, 0.0);
	m_normals[2].Set(0.0, 1.0);
	m_normals[3].Set(-1.0, 0.0);
	m_centroid = center;

	Transform xf;
	xf.p = center;
	xf.q.Set(angle);

	// Transform vertices and normals.
	for (int32 i = 0; i < m_count; ++i)
	{
		m_vertices[i] = Mul(xf, m_vertices[i]);
		m_normals[i] = Mul(xf.q, m_normals[i]);
	}
}

int32 PolygonShape::GetChildCount() const
{
	return m_count;
}
static Vec2D ComputeCentroid(const Vec2D* vs, int32 count)
{
	_Assert(count >= 3);

	Vec2D c(0.0, 0.0);
	double area = 0.0;

	// Get a reference point for forming triangles.
	// Use the first vertex to reduce round-off errors.
	Vec2D s = vs[0];

	const double inv3 = 1.0 / 3.0;

	for (int32 i = 0; i < count; ++i)
	{
		// Triangle vertices.
		Vec2D p1 = vs[0] - s;
		Vec2D p2 = vs[i] - s;
		Vec2D p3 = i + 1 < count ? vs[i + 1] - s : vs[0] - s;

		Vec2D e1 = p2 - p1;
		Vec2D e2 = p3 - p1;

		double D = Cross(e1, e2);

		double triangleArea = 0.5 * D;
		area += triangleArea;

		// Area weighted centroid
		c += triangleArea * inv3 * (p1 + p2 + p3);
	}

	// Centroid
	_Assert(area > _epsilon);
	c = (1.0 / area) * c + s;
	return c;
}

void PolygonShape::Set(const Vec2D* vertices, int32 count)
{
	_Assert(3 <= count && count <= maxPolygonVertices);
	if (count < 3)
	{
		SetAsBox(1.0, 1.0);
		return;
	}

	int32 n = Min(count, maxPolygonVertices);

	// Perform welding and copy vertices into local buffer.
	Vec2D ps[maxPolygonVertices];
	int32 tempCount = 0;
	for (int32 i = 0; i < n; ++i)
	{
		Vec2D v = vertices[i];

		bool unique = true;
		for (int32 j = 0; j < tempCount; ++j)
		{
			if (DistanceSquared(v, ps[j]) < ((0.5f * linearSlop) * (0.5 * linearSlop)))
			{
				unique = false;
				break;
			}
		}

		if (unique)
		{
			ps[tempCount++] = v;
		}
	}

	n = tempCount;
	if (n < 3)
	{
		// Polygon is degenerate.
		_Assert(false);
		SetAsBox(1.0, 1.0);
		return;
	}

	// Create the convex hull using the Gift wrapping algorithm
	// http://en.wikipedia.org/wiki/Gift_wrapping_algorithm

	// Find the right most point on the hull
	int32 i0 = 0;
	double x0 = ps[0].x;
	for (int32 i = 1; i < n; ++i)
	{
		double x = ps[i].x;
		if (x > x0 || (x == x0 && ps[i].y < ps[i0].y))
		{
			i0 = i;
			x0 = x;
		}
	}

	int32 hull[maxPolygonVertices];
	int32 m = 0;
	int32 ih = i0;

	for (;;)
	{
		_Assert(m < maxPolygonVertices);
		hull[m] = ih;

		int32 ie = 0;
		for (int32 j = 1; j < n; ++j)
		{
			if (ie == ih)
			{
				ie = j;
				continue;
			}

			Vec2D r = ps[ie] - ps[hull[m]];
			Vec2D v = ps[j] - ps[hull[m]];
			double c = Cross(r, v);
			if (c < 0.0)
			{
				ie = j;
			}

			// Collinearity check
			if (c == 0.0 && v.LengthSquared() > r.LengthSquared())
			{
				ie = j;
			}
		}

		++m;
		ih = ie;

		if (ie == i0)
		{
			break;
		}
	}

	if (m < 3)
	{
		// Polygon is degenerate.
		_Assert(false);
		SetAsBox(1.0, 1.0);
		return;
	}

	m_count = m;

	// Copy vertices.
	for (int32 i = 0; i < m; ++i)
	{
		m_vertices[i] = ps[hull[i]];
	}

	// Compute normals. Ensure the edges have non-zero length.
	for (int32 i = 0; i < m; ++i)
	{
		int32 i1 = i;
		int32 i2 = i + 1 < m ? i + 1 : 0;
		Vec2D edge = m_vertices[i2] - m_vertices[i1];
		_Assert(edge.LengthSquared() > _epsilon * _epsilon);
		m_normals[i] = Cross(edge, 1.0);
		m_normals[i].Normalize();
	}

	// Compute the polygon centroid.
	m_centroid = ComputeCentroid(m_vertices, m);
}
bool PolygonShape::RayCast(RayCastOutput* output, const RayCastInput& input,
	const Transform& xf, int32 childIndex) const
{
	_NOT_USED(childIndex);

	// Put the ray into the polygon's frame of reference.
	Vec2D p1 = MulT(xf.q, input.p1 - xf.p);
	Vec2D p2 = MulT(xf.q, input.p2 - xf.p);
	Vec2D d = p2 - p1;

	double lower = 0.0, upper = input.maxFraction;

	int32 index = -1;

	for (int32 i = 0; i < m_count; ++i)
	{
		// p = p1 + a * d
		// dot(normal, p - v) = 0
		// dot(normal, p1 - v) + a * dot(normal, d) = 0
		double numerator = Dot(m_normals[i], m_vertices[i] - p1);
		double denominator = Dot(m_normals[i], d);

		if (denominator == 0.0)
		{
			if (numerator < 0.0)
			{
				return false;
			}
		}
		else
		{
			// Note: we want this predicate without division:
			// lower < numerator / denominator, where denominator < 0
			// Since denominator < 0, we have to flip the inequality:
			// lower < numerator / denominator <==> denominator * lower > numerator.
			if (denominator < 0.0 && numerator < lower * denominator)
			{
				// Increase lower.
				// The segment enters this half-space.
				lower = numerator / denominator;
				index = i;
			}
			else if (denominator > 0.0 && numerator < upper * denominator)
			{
				// Decrease upper.
				// The segment exits this half-space.
				upper = numerator / denominator;
			}
		}

		// The use of epsilon here causes the assert on lower to trip
		// in some cases. Apparently the use of epsilon was to make edge
		// shapes work, but now those are handled separately.
		//if (upper < lower - _epsilon)
		if (upper < lower)
		{
			return false;
		}
	}

	_Assert(0.0 <= lower && lower <= input.maxFraction);

	if (index >= 0)
	{
		output->fraction = lower;
		output->normal = Mul(xf.q, m_normals[index]);
		return true;
	}

	return false;
}
bool PolygonShape::TestPoint(const Transform& xf, const Vec2D& p) const
{
	Vec2D pLocal = MulT(xf.q, p - xf.p);

	for (int32 i = 0; i < m_count; ++i)
	{
		double dot = Dot(m_normals[i], pLocal - m_vertices[i]);
		if (dot > 0.0)
		{
			return false;
		}
	}

	return true;
}
void PolygonShape::ComputeAABB(b2AABB* aabb, const Transform& xf, int32 childIndex) const
{
	_NOT_USED(childIndex);

	Vec2D lower = Mul(xf, m_vertices[0]);
	Vec2D upper = lower;

	for (int32 i = 1; i < m_count; ++i)
	{
		Vec2D v = Mul(xf, m_vertices[i]);
		lower = Min(lower, v);
		upper = Max(upper, v);
	}

	Vec2D r(m_radius, m_radius);
	aabb->lowerBound = lower - r;
	aabb->upperBound = upper + r;
}

void PolygonShape::ComputeMass(MassData* massData, double density) const
{
	// Polygon mass, centroid, and inertia.
	// Let rho be the polygon density in mass per unit area.
	// Then:
	// mass = rho * int(dA)
	// centroid.x = (1/mass) * rho * int(x * dA)
	// centroid.y = (1/mass) * rho * int(y * dA)
	// I = rho * int((x*x + y*y) * dA)
	//
	// We can compute these integrals by summing all the integrals
	// for each triangle of the polygon. To evaluate the integral
	// for a single triangle, we make a change of variables to
	// the (u,v) coordinates of the triangle:
	// x = x0 + e1x * u + e2x * v
	// y = y0 + e1y * u + e2y * v
	// where 0 <= u && 0 <= v && u + v <= 1.
	//
	// We integrate u from [0,1-v] and then v from [0,1].
	// We also need to use the Jacobian of the transformation:
	// D = cross(e1, e2)
	//
	// Simplification: triangle centroid = (1/3) * (p1 + p2 + p3)
	//
	// The rest of the derivation is handled by computer algebra.

	_Assert(m_count >= 3);

	Vec2D center(0.0, 0.0);
	double area = 0.0;
	double I = 0.0;

	// Get a reference point for forming triangles.
	// Use the first vertex to reduce round-off errors.
	Vec2D s = m_vertices[0];

	const double k_inv3 = 1.0 / 3.0;

	for (int32 i = 0; i < m_count; ++i)
	{
		// Triangle vertices.
		Vec2D e1 = m_vertices[i] - s;
		Vec2D e2 = i + 1 < m_count ? m_vertices[i + 1] - s : m_vertices[0] - s;

		double D = Cross(e1, e2);

		double triangleArea = 0.5 * D;
		area += triangleArea;

		// Area weighted centroid
		center += triangleArea * k_inv3 * (e1 + e2);

		double ex1 = e1.x, ey1 = e1.y;
		double ex2 = e2.x, ey2 = e2.y;

		double intx2 = ex1 * ex1 + ex2 * ex1 + ex2 * ex2;
		double inty2 = ey1 * ey1 + ey2 * ey1 + ey2 * ey2;

		I += (0.25 * k_inv3 * D) * (intx2 + inty2);
	}

	// Total mass
	massData->mass = density * area;

	// Center of mass
	_Assert(area > _epsilon);
	center *= 1.0 / area;
	massData->center = center + s;

	// Inertia tensor relative to the local origin (point s).
	massData->I = density * I;

	// Shift to center of mass then to original body origin.
	massData->I += massData->mass * (Dot(massData->center, massData->center) - Dot(center, center));
}

bool PolygonShape::Validate() const
{
	for (int32 i = 0; i < m_count; ++i)
	{
		int32 i1 = i;
		int32 i2 = i < m_count - 1 ? i1 + 1 : 0;
		Vec2D p = m_vertices[i1];
		Vec2D e = m_vertices[i2] - p;

		for (int32 j = 0; j < m_count; ++j)
		{
			if (j == i1 || j == i2)
			{
				continue;
			}

			Vec2D v = m_vertices[j] - p;
			double c = Cross(e, v);
			if (c < 0.0f)
			{
				return false;
			}
		}
	}

	return true;
}
