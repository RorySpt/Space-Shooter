#pragma once
#include<Windows.h>
#include"MyMath.h"





//多边形命名空间
namespace MgGeometryType2D
{
	//多边形基本单位，点
	typedef  POINT_DB Point;
	typedef POINT POINT;

	struct Cycle
	{
		POINT position;
		double radius;
	};
}
const uint8 nullFeature = UCHAR_MAX;


/*
* 修改自BOX2D	
*/


/// The features that intersect to form the contact point
/// This must be 4 bytes or less.
//struct ContactFeature
//{
//	enum Type
//	{
//		e_vertex = 0,
//		e_face = 1
//	};
//
//	uint8 indexA;		///< Feature index on shapeA
//	uint8 indexB;		///< Feature index on shapeB
//	uint8 typeA;		///< The feature type on shapeA
//	uint8 typeB;		///< The feature type on shapeB
//};
///// Contact ids to facilitate warm starting.
//union ContactID
//{
//	ContactFeature cf;
//	uint32 key;					///< Used to quickly compare contact ids.
//};
///// Used for computing contact manifolds.
//struct ClipVertex
//{
//	TC::Vector2D v;
//	ContactID id;
//};

/// Ray-cast input data. The ray extends from p1 to p1 + maxFraction * (p2 - p1).
struct RayCastInput
{
	TC::Vector2D p1, p2;
	double maxFraction;
};

/// Ray-cast output data. The ray hits at p1 + fraction * (p2 - p1), where p1 and p2
/// come from b2RayCastInput.
struct RayCastOutput
{
	TC::Vector2D normal;
	double fraction;
};

struct b2AABB
{
	/// Verify that the bounds are sorted.
	bool IsValid() const;
	void Sort() {
		TC::Vector2D _lowerBound(lowerBound);
		lowerBound = Min(_lowerBound, upperBound);
		upperBound = Max(_lowerBound, upperBound);
	}
	/// Get the center of the AABB.
	TC::Vector2D GetCenter() const
	{
		return 0.5 * (lowerBound + upperBound);
	}

	/// Get the extents of the AABB (half-widths).
	TC::Vector2D GetExtents() const
	{
		return 0.5 * (upperBound - lowerBound);
	}

	/// Get the perimeter length
	double GetPerimeter() const
	{
		double wx = upperBound.x - lowerBound.x;
		double wy = upperBound.y - lowerBound.y;
		return 2.0 * (wx + wy);
	}

	/// Combine an AABB into this one.
	void Combine(const b2AABB& aabb)
	{
		lowerBound = Min(lowerBound, aabb.lowerBound);
		upperBound = Max(upperBound, aabb.upperBound);
	}

	/// Combine two AABBs into this one.
	void Combine(const b2AABB& aabb1, const b2AABB& aabb2)
	{
		lowerBound = Min(aabb1.lowerBound, aabb2.lowerBound);
		upperBound = Max(aabb1.upperBound, aabb2.upperBound);
	}

	/// Does this aabb contain the provided AABB.
	bool Contains(const b2AABB& aabb) const
	{
		bool result = true;
		result = result && lowerBound.x <= aabb.lowerBound.x;
		result = result && lowerBound.y <= aabb.lowerBound.y;
		result = result && aabb.upperBound.x <= upperBound.x;
		result = result && aabb.upperBound.y <= upperBound.y;
		return result;
	}

	bool RayCast(RayCastOutput* output, const RayCastInput& input) const;


	TC::Vector2D lowerBound;	// the lower vertex
	TC::Vector2D upperBound;	// the upper vertex
};

inline bool b2AABB::IsValid() const
{
	TC::Vector2D d = upperBound - lowerBound;
	bool valid = d.x >= 0.0f && d.y >= 0.0f;
	valid = valid && lowerBound.IsValid() && upperBound.IsValid();
	return valid;
}
struct MassData
{
	/// The mass of the shape, usually in kilograms.
	double mass;

	/// The position of the shape's centroid relative to the shape's origin.
	Vec2D center;

	/// The rotational inertia of the shape about the local origin.
	double I;
};
class Shape
{
public:
	enum Type
	{
		e_circle = 0,
		e_edge = 1,
		e_polygon = 2,
		e_chain = 3,
		e_typeCount = 4
	};
	Shape() :m_type(e_circle), m_radius(0) {};
	virtual ~Shape() {}

	/// Clone the concrete shape using the provided allocator.
	virtual Shape* Clone(/*BlockAllocator* allocator*/) const = 0;

	/// Get the type of this shape. You can use this to down cast to the concrete shape.
	/// @return the shape type.
	Type GetType() const { return m_type; }

	/// Get the number of child primitives.
	virtual int32 GetChildCount() const = 0;

	/// Test a point for containment in this shape. This only works for convex shapes.
	/// @param xf the shape world transform.
	/// @param p a point in world coordinates.
	virtual bool TestPoint(const Transform& xf, const TC::Vector2D& p) const = 0;

	/// Cast a ray against a child shape.
	/// @param output the ray-cast results.
	/// @param input the ray-cast input parameters.
	/// @param transform the transform to be applied to the shape.
	/// @param childIndex the child shape index
	virtual bool RayCast(RayCastOutput* output, const RayCastInput& input,
		const Transform& transform, int32 childIndex) const = 0;

	/// Given a transform, compute the associated axis aligned bounding box for a child shape.
	/// @param aabb returns the axis aligned box.
	/// @param xf the world transform of the shape.
	/// @param childIndex the child shape
	virtual void ComputeAABB(b2AABB* aabb, const Transform& xf, int32 childIndex) const = 0;

	/// Compute the mass properties of this shape using its dimensions and density.
	/// The inertia tensor is computed about the local origin.
	/// @param massData returns the mass data for this shape.
	/// @param density the density in kilograms per meter squared.
	virtual void ComputeMass(MassData* massData, double density) const = 0;

	Type m_type;

	/// Radius of a shape. For polygonal shapes this must be b2_polygonRadius. There is no support for
	/// making rounded polygons.
	double m_radius;

};

/// A distance proxy is used by the GJK algorithm.
/// It encapsulates any shape.
struct DistanceProxy
{
	DistanceProxy() : m_vertices(nullptr), m_count(0), m_radius(0.0f) {}

	/// Initialize the proxy using the given shape. The shape
	/// must remain in scope while the proxy is in use.
	void Set(const Shape* shape, int32 index);

	/// Initialize the proxy using a vertex cloud and radius. The vertices
	/// must remain in scope while the proxy is in use.
	void Set(const Vec2D* vertices, int32 count, double radius);

	/// Get the supporting vertex index in the given direction.
	int32 GetSupport(const Vec2D& d) const;

	/// Get the supporting vertex in the given direction.
	const Vec2D& GetSupportVertex(const Vec2D& d) const;

	/// Get the vertex count.
	int32 GetVertexCount() const;

	/// Get a vertex by index. Used by Distance.
	const Vec2D& GetVertex(int32 index) const;

	Vec2D m_buffer[2];
	const Vec2D* m_vertices;
	int32 m_count;
	double m_radius;
};

/// Used to warm start Distance.
/// Set count to zero on first call.
struct SimplexCache
{
	double metric;		///< length or area
	uint16 count;
	uint8 indexA[3];	///< vertices on shape A
	uint8 indexB[3];	///< vertices on shape B
};

/// Input for Distance.
/// You have to option to use the shape radii
/// in the computation. Even
struct DistanceInput
{
	DistanceProxy proxyA;
	DistanceProxy proxyB;
	Transform transformA;
	Transform transformB;
	bool useRadii;
};

/// Output for Distance.
struct DistanceOutput
{
	Vec2D pointA;		///< closest point on shapeA
	Vec2D pointB;		///< closest point on shapeB
	double distance;
	int32 iterations;	///< number of GJK iterations used
};

/// Compute the closest points between two shapes. Supports any combination of:
/// CircleShape, PolygonShape, EdgeShape. The simplex cache is input/output.
/// On the first call set SimplexCache.count to zero.
void Distance(DistanceOutput* output,
	SimplexCache* cache,
	const DistanceInput* input);

/// Input parameters for ShapeCast
struct ShapeCastInput
{
	DistanceProxy proxyA;
	DistanceProxy proxyB;
	Transform transformA;
	Transform transformB;
	Vec2D translationB;
};

/// Output results for ShapeCast
struct ShapeCastOutput
{
	Vec2D point;
	Vec2D normal;
	double lambda;
	int32 iterations;
};

/// Perform a linear shape cast of shape B moving and shape A fixed. Determines the hit point, normal, and translation fraction.
/// @returns true if hit, false if there is no hit or an initial overlap
bool ShapeCast(ShapeCastOutput* output, const ShapeCastInput* input);

//////////////////////////////////////////////////////////////////////////

inline int32 DistanceProxy::GetVertexCount() const
{
	return m_count;
}

inline const Vec2D& DistanceProxy::GetVertex(int32 index) const
{
	_Assert(0 <= index && index < m_count);
	return m_vertices[index];
}

inline int32 DistanceProxy::GetSupport(const Vec2D& d) const
{
	int32 bestIndex = 0;
	double bestValue = Dot(m_vertices[0], d);
	for (int32 i = 1; i < m_count; ++i)
	{
		double value = Dot(m_vertices[i], d);
		if (value > bestValue)
		{
			bestIndex = i;
			bestValue = value;
		}
	}

	return bestIndex;
}

inline const Vec2D& DistanceProxy::GetSupportVertex(const Vec2D& d) const
{
	int32 bestIndex = 0;
	double bestValue = Dot(m_vertices[0], d);
	for (int32 i = 1; i < m_count; ++i)
	{
		double value = Dot(m_vertices[i], d);
		if (value > bestValue)
		{
			bestIndex = i;
			bestValue = value;
		}
	}

	return m_vertices[bestIndex];
}

