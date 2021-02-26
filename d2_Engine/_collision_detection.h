#pragma once
#include"_shapes.h"
#include<Windows.h>
#include<cmath>
namespace TC {

	/*********
	 *碰撞检测
	 *********/

	/*简单检测*/
	//圆，圆
	bool IsHit(MgGeometryType2D::Cycle cyc1, MgGeometryType2D::Cycle cyc2);
	//矩形，矩形
	bool IsHit(RECT rect1, RECT rect2);
	//浮点矩形
	//bool IsHit(const MgGeometryType2D::gtRECT &rect1, const  MgGeometryType2D::gtRECT &rect2);

	bool IsHit(const b2AABB &a, const Transform&tf1, const b2AABB &b, const Transform& tf2 );

	bool IsHit(const b2AABB& a, const b2AABB& b);


	/*复杂检测*/
	//凸多边形，凸多边形
	//凹多边形会当作凸多边形处理
	bool IsHit(MgGeometryType2D::Polygon pol1, MgGeometryType2D::Polygon pol2);
	//凸多边形，圆
	bool IsHit(MgGeometryType2D::Polygon pol, MgGeometryType2D::Cycle cyc);

	bool IsHit(const MgGeometryType2D::Polygon& pol1, const  Transform& tf1, const  MgGeometryType2D::Polygon& pol2, const  Transform& tf2);
	////凸多边形，圆
	//bool IsHit(MgGeometryType2D::Polygon pol, MgGeometryType2D::Cycle cyc);



	/**********
	 *碰撞处理
	 **********/

	//碰撞处理,静态和动态物体
	Vector2D dealHit_fix_mutex_static_dynamic(MgGeometryType2D::Polygon  still, MgGeometryType2D::Polygon Animal, Vector2D &speed);
	Vector2D dealHit(const RECT& still, const RECT& Animal, Vector2D& speed);//用dealHit_base_mutex_static_dynamic代替
	Vector2D dealHit_base_mutex_static_dynamic(const MgGeometryType2D::gtRECT& rect1, const  MgGeometryType2D::gtRECT& rect2, Vector2D& speed);//浮点矩形


}
struct ContactFeature
{
	enum Type
	{
		e_vertex = 0,
		e_face = 1
	};

	uint8 indexA;		///< Feature index on shapeA
	uint8 indexB;		///< Feature index on shapeB
	uint8 typeA;		///< The feature type on shapeA
	uint8 typeB;		///< The feature type on shapeB
};
union ContactID
{
	ContactFeature cf;
	uint32 key;					///< Used to quickly compare contact ids.
};
/// A manifold point is a contact point belonging to a contact
/// manifold. It holds details related to the geometry and dynamics
/// of the contact points.
/// The local point usage depends on the manifold type:
/// -e_circles: the local center of circleB
/// -e_faceA: the local center of cirlceB or the clip point of polygonB
/// -e_faceB: the clip point of polygonA
/// This structure is stored across time steps, so we keep it small.
/// Note: the impulses are used for internal caching and may not
/// provide reliable contact forces, especially for high speed collisions.
struct ManifoldPoint
{
	Vec2D localPoint;		///< usage depends on manifold type
	double normalImpulse;	///< the non-penetration impulse
	double tangentImpulse;	///< the friction impulse
	ContactID id;			///< uniquely identifies a contact point between two shapes
};

/// Used for computing contact manifolds.
struct ClipVertex
{
	Vec2D v;
	ContactID id;
};
/// A manifold for two touching convex shapes.
/// Box2D supports multiple types of contact:
/// - clip point versus plane with radius
/// - point versus point with radius (circles)
/// The local point usage depends on the manifold type:
/// -e_circles: the local center of circleA
/// -e_faceA: the center of faceA
/// -e_faceB: the center of faceB
/// Similarly the local normal usage:
/// -e_circles: not used
/// -e_faceA: the normal on polygonA
/// -e_faceB: the normal on polygonB
/// We store contacts in this way so that position correction can
/// account for movement, which is critical for continuous physics.
/// All contact scenarios must be expressed in one of these types.
/// This structure is stored across time steps, so we keep it small.
struct Manifold
{
	enum Type
	{
		e_circles,
		e_faceA,
		e_faceB
	};

	ManifoldPoint points[maxManifoldPoints];	///< the points of contact
	Vec2D localNormal;								///< not use for Type::e_points
	Vec2D localPoint;								///< usage depends on manifold type
	Type type;
	int32 pointCount;								///< the number of manifold points
};

/// Compute the collision manifold between two circles.
void CollideCircles(Manifold* manifold,
	const CircleShape* circleA, const Transform& xfA,
	const CircleShape* circleB, const Transform& xfB);

/// Compute the collision manifold between a polygon and a circle.
void CollidePolygonAndCircle(Manifold* manifold,
	const PolygonShape* polygonA, const Transform& xfA,
	const CircleShape* circleB, const Transform& xfB);

/// Compute the collision manifold between two polygons.
void CollidePolygons(Manifold* manifold,
	const PolygonShape* polygonA, const Transform& xfA,
	const PolygonShape* polygonB, const Transform& xfB);

///// Compute the collision manifold between an edge and a circle.
//void CollideEdgeAndCircle(Manifold* manifold,
//	const EdgeShape* polygonA, const Transform& xfA,
//	const CircleShape* circleB, const Transform& xfB);

///// Compute the collision manifold between an edge and a polygon.
//void CollideEdgeAndPolygon(Manifold* manifold,
//	const EdgeShape* edgeA, const Transform& xfA,
//	const PolygonShape* circleB, const Transform& xfB);

///// Clipping for contact manifolds.
//int32 ClipSegmentToLine(ClipVertex vOut[2], const ClipVertex vIn[2],
//	const Vec2D& normal, float offset, int32 vertexIndexA);

/// Determine if two generic shapes overlap.
bool TestOverlap(const Shape* shapeA, int32 indexA,
	const Shape* shapeB, int32 indexB,
	const Transform& xfA, const Transform& xfB);
