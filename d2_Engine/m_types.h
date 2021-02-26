#pragma once
#include<limits.h>
#include<assert.h>
typedef signed char	int8;
typedef signed short int16;
typedef signed int int32;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
// basic unsigned types
typedef unsigned short USHORT;
typedef unsigned short WORD;
typedef unsigned char  UCHAR;
typedef unsigned char  BYTE;
//////////////////////////////////////////////////////////////////
//这里需要Windows.h头文件
#include<WinUser.h>
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)
//////////////////////////////////////////////////////////////////


#define _NOT_USED(x) ((void)(x))
#define _Assert(A) assert(A)

#define	maxDouble		DBL_MAX
#define	_epsilon		DBL_EPSILON
//#define _pi				3.14159265359
constexpr double PI ((double)3.1415926535897932384626433832795028841971);

#define CONNECT_LIST(LAST,NEXT) LAST.next = &NEXT;NEXT.last = &LAST

template<typename T>
inline void ConnectList(T* const last, T* const next) {
	last->next = next;
	next->last = last;
}
template<typename T>
inline void InsertList(T* const last, T* const next, T* const node) {
	node->next = next;
	node->last = last;
	if (last != NULL)last->next = node;
	if (next != NULL)next->last = node;
}
template<typename T>
inline void InsertList_front(T* const next, T* const node) {
	T* last = (T*)next->last;
	node->next = next;
	node->last = last;
	if (last != NULL)last->next = node;
	if (next != NULL)next->last = node;
}

template<typename T>
inline void InsertList_back(T* const last, T* const node) {
	T* const next = (T* const)last->next;
	node->next = next;
	node->last = last;
	if (last != NULL)last->next = node;
	if (next != NULL)next->last = node;
}
template<typename T>
inline void RemoveList(T* const node) {
	T* const last = (T* const)node->last;
	T* const next = (T* const)node->next;
	if (last != NULL)last->next = next;
	if (next != NULL)next->last = last;
	node->last = NULL; node->next = NULL;
}



//Transplantation in b2Box

/// @file
/// Global tuning constants based on meters-kilograms-seconds (MKS) units.
///

// Collision
#define lengthUnitsPerMeter 1.0
/// The maximum number of contact points between two convex shapes. Do
/// not change this value.
#define maxManifoldPoints	2

/// This is used to fatten AABBs in the dynamic tree. This allows proxies
/// to move by a small amount without triggering a tree adjustment.
/// This is in meters.
#define aabbExtension		(0.1 * lengthUnitsPerMeter)

/// This is used to fatten AABBs in the dynamic tree. This is used to predict
/// the future position based on the current displacement.
/// This is a dimensionless multiplier.
#define aabbMultiplier		4.0

/// A small length used as a collision and constraint tolerance. Usually it is
/// chosen to be numerically significant, but visually insignificant. In meters.
#define linearSlop			(0.005 * lengthUnitsPerMeter)

/// A small angle used as a collision and constraint tolerance. Usually it is
/// chosen to be numerically significant, but visually insignificant.
#define angularSlop			(2.0 / 180.0 * PI)

/// The radius of the polygon/edge shape skin. This should not be modified. Making
/// this smaller means polygons will have an insufficient buffer for continuous collision.
/// Making it larger may create artifacts for vertex collision.
#define polygonRadius		(2.0 * linearSlop)

/// Maximum number of sub-steps per contact in continuous physics simulation.
#define maxSubSteps			8


// Dynamics

/// Maximum number of contacts to be handled to solve a TOI impact.
#define maxTOIContacts			32

/// The maximum linear position correction used when solving constraints. This helps to
/// prevent overshoot. Meters.
#define maxLinearCorrection		(0.2 * lengthUnitsPerMeter)

/// The maximum angular position correction used when solving constraints. This helps to
/// prevent overshoot.
#define maxAngularCorrection		(8.0 / 180.0 * PI)

/// The maximum linear translation of a body per step. This limit is very large and is used
/// to prevent numerical problems. You shouldn't need to adjust this. Meters.
#define maxTranslation			(2.0 * lengthUnitsPerMeter)
#define maxTranslationSquared	(maxTranslation * maxTranslation)

/// The maximum angular velocity of a body. This limit is very large and is used
/// to prevent numerical problems. You shouldn't need to adjust this.
#define maxRotation				(0.5 * PI)
#define maxRotationSquared		(maxRotation * maxRotation)

/// This scale factor controls how fast overlap is resolved. Ideally this would be 1 so
/// that overlap is removed in one time step. However using values close to 1 often lead
/// to overshoot.
#define baumgarte				0.2
#define toiBaumgarte				0.75


// Sleep

/// The time that a body must be still before it will go to sleep.
#define b2_timeToSleep				0.5

/// A body cannot sleep if its linear velocity is above this tolerance.
#define b2_linearSleepTolerance		(0.01 * lengthUnitsPerMeter)

/// A body cannot sleep if its angular velocity is above this tolerance.
#define b2_angularSleepTolerance	(2.0 / 180.0 * PI)