#pragma once
#include<graphics.h>
#include"tools.h"
class World;
class Fixture;
//sprite基类
class Sprite
{
public:
	Vec2D site;  //sprite的坐标原点,默认(0,0)
	Transform tran;	//该Sprite贴图相对原点的平移和旋转数据，这里只用平移
	IMAGIF<LONGLONG> map;		//贴图
	//Shape* sprite_shape;
	Sprite* son_sprite = NULL;	//子Sprite;
	Sprite* next = NULL;		//同级下一个Sprite;
	Sprite* last = NULL;		//同级上一个Sprite;
	Sprite() {
		site = { 0,0 };
		tran.SetIdentity();
	};
	//将该元素及其子元素以变换tf绘制到目标画布上
	void Draw(IMAGE* pImgDst, const Transform& tf/*, Vec2D pos*/);

	


};

class SpriteBody :public Sprite
{
public:
	MgGeometryType2D::Polygon SpriteShape;
	b2AABB OriginalShapeBox;
	b2AABB OriginalBox;
	b2AABB TempBox;

	//使用之前必须有调用过CalAABB()
	b2AABB& CalAABB(const Transform& tf);
	void DrawNormal(IMAGE* pImgDst, const Transform& tf);

	b2AABB& CalAABB();
};
void DrawAABB(const b2AABB& _box, const Transform& tf = Transform());
void DrawShape(const MgGeometryType2D::Polygon& _shape, const Transform& tf);































enum BodyType
{
	staticBody = 0,
	kinematicBody,
	dynamicBody
};
struct BodyDef
{
	/// This constructor sets the body definition default values.
	BodyDef()
	{
		position.Set(0.0, 0.0);
		angle = 0.0f;
		linearVelocity.Set(0.0, 0.0);
		angularVelocity = 0.0;
		linearDamping = 0.0;
		angularDamping = 0.0;
		allowSleep = true;
		awake = true;
		fixedRotation = false;
		bullet = false;
		type = staticBody;
		enabled = true;
		gravityScale = 1.0f;
	}

	/// 物体的类型: static(静态刚体), kinematic(动态刚体), or dynamic.
	/// Note: if a dynamic body would have zero mass, the mass is set to one.
	BodyType type;

	/// 物体在世界的位置. Avoid creating bodies at the origin
	/// since this can lead to many overlapping shapes.
	TC::Vector2D position;

	/// The world angle of the body in radians.
	float angle;

	/// The linear velocity of the body's origin in world co-ordinates.
	TC::Vector2D linearVelocity;

	/// 物体角速度
	float angularVelocity;

	/// 阻尼Linear damping is use to reduce the linear velocity. The damping parameter
	/// can be larger than 1.0f but the damping effect becomes sensitive to the
	/// time step when the damping parameter is large.
	/// Units are 1/time
	float linearDamping;

	/// Angular damping is use to reduce the angular velocity. The damping parameter
	/// can be larger than 1.0f but the damping effect becomes sensitive to the
	/// time step when the damping parameter is large.
	/// Units are 1/time
	float angularDamping;

	/// Set this flag to false if this body should never fall asleep. Note that
	/// this increases CPU usage.
	bool allowSleep;

	/// Is this body initially awake or sleeping?
	bool awake;

	/// Should this body be prevented from rotating? Useful for characters.
	bool fixedRotation;

	/// Is this a fast moving body that should be prevented from tunneling through
	/// other moving bodies? Note that all bodies are prevented from tunneling through
	/// kinematic and static bodies. This setting is only considered on dynamic bodies.
	/// @warning You should use this flag sparingly since it increases processing time.
	bool bullet;

	/// Does this body start out enabled?
	bool enabled;

	/*/// Use this to store application specific body data.
	b2BodyUserData userData;*/

	/// Scale the gravity applied to this body.
	float gravityScale;
};
struct Body
{
	friend class World;
	// m_flags
	enum
	{
		e_islandFlag = 0x0001,
		e_awakeFlag = 0x0002,
		e_autoSleepFlag = 0x0004,
		e_bulletFlag = 0x0008,
		e_fixedRotationFlag = 0x0010,
		e_enabledFlag = 0x0020,
		e_toiFlag = 0x0040
	};
	Body(const BodyDef* bd, World* world);
	~Body();


	
	BodyType m_type;

	uint16 m_flags;

	int32 m_islandIndex;

	//b2Transform m_xf;		// the body origin transform
	//b2Sweep m_sweep;		// the swept motion for CCD

	TC::Vector2D m_linearVelocity;
	float m_angularVelocity;

	TC::Vector2D m_force;
	float m_torque;

	World* m_world;
	Body* m_prev;
	Body* m_next;

	Fixture* m_fixtureList;
	int32 m_fixtureCount;

	/*b2JointEdge* m_jointList;
	b2ContactEdge* m_contactList;*/

	float m_mass, m_invMass;

	// Rotational inertia about the center of mass.
	float m_I, m_invI;

	float m_linearDamping;
	float m_angularDamping;
	float m_gravityScale;

	float m_sleepTime;

	//b2BodyUserData m_userData;
};
#define lengthUnitsPerMeter 1.0
struct b2FixtureDef
{
	/// The constructor sets the default fixture definition values.
	b2FixtureDef()
	{
		shape = nullptr;
		friction = 0.2f;
		restitution = 0.0f;
		restitutionThreshold = 1.0f * lengthUnitsPerMeter;
		density = 0.0f;
		isSensor = false;
	}

	/// The shape, this must be set. The shape will be cloned, so you
	/// can create the shape on the stack.
	const Shape* shape;

	/// Use this to store application specific fixture data.
	//b2FixtureUserData userData;

	/// The friction coefficient, usually in the range [0,1].
	float friction;

	/// The restitution (elasticity) usually in the range [0,1].
	float restitution;

	/// Restitution velocity threshold, usually in m/s. Collisions above this
	/// speed have restitution applied (will bounce).
	float restitutionThreshold;

	/// The density, usually in kg/m^2.
	float density;

	/// A sensor shape collects contact information but never generates a collision
	/// response.
	bool isSensor;

	/// Contact filtering data.
	//b2Filter filter;
};
struct b2FixtureProxy
{
	//BOXAABB aabb;
	Fixture* fixture;
	int32 childIndex;
	int32 proxyId;
};
class Fixture
{

};
