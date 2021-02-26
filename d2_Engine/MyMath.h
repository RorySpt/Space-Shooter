#pragma once
#define _MYMATH_H
#include <cmath>
#include<Windows.h>
#include<float.h>
#include"m_types.h"
#pragma warning(disable : 26812)
//DEFINES////////////////////////


//小于1e-9的浮点数被认为是零
#define DBL_EPS 1e-9
#define ISZERO_DB(val)  (abs(val)<DBL_EPS)
#define NOTZERO_DB(val)  (abs(val)>DBL_EPS)

///尽量用Vec2D来代替POINT_DB
struct POINT_DB
{
	//POINT_DB(const TC::Vector2D& v) { x = v.x;y = v.y; }
	double x;
	double y;
};
//#define POINT_LONG_TO_DB
#define DB_TO_LONG_ROUND(DB) (LONG(DB > 0 ? DB + 0.5 : DB - 0.5))
#define POINT_DB_TO_LONG(_DB) (POINT({ DB_TO_LONG_ROUND((_DB).x),DB_TO_LONG_ROUND((_DB).y) }))

//取较小数
template <typename T>
inline T Min(T a, T b)
{
	return a < b ? a : b;
}

//取较大数
template <typename T>
inline T Max(T a, T b)
{
	return a > b ? a : b;
}

//求绝对值
template <typename T>
inline T Abs(T a)
{
	return a > T(0) ? a : -a;
}
//交换数值
template <typename T>
inline void Swap(T& a, T& b)
{
	T t(a);
	a = b;
	b = t;
}
struct Rot;

namespace TC
{

	//2D矢量,可当作POINT_DB
	class Vector2D
	{
	public:
		Vector2D(const double x_, const double y_);
		Vector2D() :x(0), y(0) {};
		Vector2D(POINT_DB begin, POINT_DB end);
		//Vector2D(double length, double angle);
		Vector2D(const Vector2D& v) :x(v.x), y(v.y) {};
		Vector2D(const double length, const Vector2D& v);
		Vector2D(const Vector2D& v, double angle);

		void Set(double x_, double y_) { x = x_; y = y_; }
		void SetZero() { x = 0.0; y = 0.0; }
		/// Read from and indexed element.
		double operator () (int32 i) const { return (&x)[i]; }
		/// Write to an indexed element.
		double& operator () (int32 i) { return (&x)[i]; }

		//矢量基本运算
		Vector2D operator-  ();
		Vector2D operator-	(const Vector2D& v)const;
		Vector2D operator+	(const Vector2D& v)const;
		Vector2D& operator= (const Vector2D& v);
		Vector2D& operator-= (const Vector2D& v);
		Vector2D& operator+= (const Vector2D& v);

		Vector2D operator*  (double scalar);
		Vector2D operator/  (double scalar);
		Vector2D& operator*=  (double scalar);
		Vector2D& operator/=  (double scalar);

		friend Vector2D operator*(double scalar, const Vector2D& v);

		//比较
		bool operator==(const Vector2D& v)const;
		bool operator!=(const Vector2D& v)const;

		//耗时，误差较大
		//计算角度差，u - v
		friend double operator^ (const Vector2D& v, const Vector2D& u);

		//耗时
		//计算长度差, u - v
		friend double operator% (const Vector2D& v, const Vector2D& u);

		//计算在v投影长度
		double Drop(const Vector2D& v);
		double Dot(const Vector2D& v);


		//获取长度,两次乘法和一次开方
		double Length()const;
		/// Get the length squared. For performance, use this instead of
		/// 取长度平方，较快
		double LengthSquared() const
		{
			return x * x + y * y;
		}
		//获取弧度，-PI到PI
		double Angle()const;
		//取缔长度
		Vector2D& Clamp(const double max);
		//标准矢量化
		Vector2D& Normalize();
		//旋转
		Vector2D& Rotate(const double angle);
		Vector2D& Rotate(const Rot& rot);

		//旋转
		Vector2D& RotateT(const double angle) {
			return Rotate(-angle);
		}
		Vector2D& RotateT(const Rot& rot);
		bool IsValid()const {
			return _finite(x) && _finite(y);
		}

		//和POINT做加法
		POINT operator +(const POINT& left);
		friend POINT operator +(const POINT& left, const Vector2D right);

		//和POINT_DB做加法
		POINT_DB operator +(const POINT_DB& left);
		friend POINT_DB operator +(const POINT_DB& left, const Vector2D right);
	public:
		double x;
		double y;
		//可选项
	//private:
	//	double mag = 0;
	//	double ang = 0;
	};
	inline Vector2D Vector2D::operator-  ()
	{
		return { -x,-y };
	}
	//inline Vector2D Vector2D::operator-  ()
	//{
	//	Vector2D result(-x, -y);
	//	return result;
	//}


	inline Vector2D Vector2D::operator-	(const Vector2D& v)const
	{
		Vector2D result;
		result.x = x - v.x;
		result.y = y - v.y;
		return result;
	}
	inline Vector2D Vector2D::operator+	(const Vector2D& v)const
	{
		Vector2D result;
		result.x = x + v.x;
		result.y = y + v.y;
		return result;
	}
	inline Vector2D& Vector2D::operator= (const Vector2D& v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}
	inline Vector2D& Vector2D::operator-= (const Vector2D& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	inline Vector2D& Vector2D::operator+= (const Vector2D& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	inline Vector2D Vector2D::operator*  (double scalar)
	{
		return { x * scalar ,y * scalar };
	}
	inline Vector2D Vector2D::operator/  (double scalar)
	{
		return { x / scalar ,y / scalar };
	}
	inline Vector2D& Vector2D::operator*=  (double scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}
	inline Vector2D& Vector2D::operator/=  (double scalar)
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}


	inline Vector2D operator*(double scalar, const Vector2D& v)
	{
		Vector2D result;
		result.x = v.x * scalar;
		result.y = v.y * scalar;
		return result;
	}


	inline bool Vector2D::operator==(const Vector2D& v)const
	{
		if (ISZERO_DB(x - v.x) && ISZERO_DB(y - v.y))return true;
		else false;
	}
	inline bool Vector2D::operator!=(const Vector2D& v)const
	{
		if (ISZERO_DB(x - v.x) && ISZERO_DB(y - v.y))return false;
		else true;
	}
	inline double operator^ (const Vector2D& v, const Vector2D& u)
	{
		double a = u.Angle();
		double b = v.Angle();
		if (a - b >= PI)return 2 * PI + b - a;
		if (a - b < -PI) return 2 * PI + a - b;
		return a - b;
		//return u.Angle() - v.Angle();
	}
	inline double operator% (const Vector2D& v, const Vector2D& u)
	{
		return u.Length() - v.Length();
	}


	inline double Vector2D::Drop(const Vector2D& vec)
	{

		/*double m_Length = Length();
		if (m_Length < DBL_EPS)
		{
			return 0;
		}
		double t_angle = vec.Angle();
		double m_angle = Angle();
		return m_Length * cos(m_angle - t_angle);*/
		return Dot(vec) / vec.Length();

	}

	inline double Vector2D::Dot(const Vector2D& vec)
	{

		return x * vec.x + y * vec.y;
	}

	inline double Vector2D::Length()const
	{
		return sqrt(x * x + y * y);
	}
	inline double Vector2D::Angle() const
	{
		return atan2(y, x);
	}
	inline Vector2D& Vector2D::Clamp(const double max)
	{
		/*double m_Angle = Angle();
		x = max * cos(m_Angle);
		y = max * sin(m_Angle);*/
		double length = Length();
		if (length < DBL_EPS)
		{
			x = 0.0; y = 0.0;
			return *this;
		}
		double invLength = max / length;
		x *= invLength;
		y *= invLength;
		return *this;
	}
	inline Vector2D& Vector2D::Normalize()
	{
		double length = Length();
		if (length < DBL_EPS)
		{
			x = 0.0; y = 0.0;
			return *this;
		}
		double invLength = 1.0 / length;
		x *= invLength;
		y *= invLength;
		return *this;
	}
	inline Vector2D& Vector2D::Rotate(const double angle)
	{
		/*double m_Angle = Angle();
		double m_Length = Length();
		m_Angle += angle;
		x = m_Length * cos(m_Angle);
		y = m_Length * sin(m_Angle);*/

		double s = sin(angle);
		double c = cos(angle);

		double x1 = x * c - y * s;
		double y1 = y * c + x * s;

		x = x1;
		y = y1;
		return *this;
	}
	

	inline POINT Vector2D::operator+ (const POINT& right)
	{
		POINT ret(right);
		ret.x += DB_TO_LONG_ROUND(x);
		ret.y += DB_TO_LONG_ROUND(y);
		return ret;
	}
	inline POINT operator +(const POINT& left, const Vector2D right)
	{
		POINT ret(left);
		ret.x += DB_TO_LONG_ROUND(right.x);
		ret.y += DB_TO_LONG_ROUND(right.y);
		return ret;
	}
	inline POINT_DB Vector2D::operator+ (const POINT_DB& right)
	{
		POINT_DB ret(right);
		ret.x += x;
		ret.y += y;
		return ret;
	}
	inline POINT_DB operator +(const POINT_DB& left, const Vector2D right)
	{
		POINT_DB ret(left);
		ret.x += (right.x);
		ret.y += (right.y);
		return ret;
	}
}


//math

//取向量矩形极小值
inline TC::Vector2D Min(const TC::Vector2D& a, const TC::Vector2D& b)
{
	return TC::Vector2D(Min(a.x, b.x), Min(a.y, b.y));
}
//取向量矩形极大值
inline TC::Vector2D Max(const TC::Vector2D& a, const TC::Vector2D& b)
{
	return TC::Vector2D(Max(a.x, b.x), Max(a.y, b.y));
}
//取向量绝对值,矩形正方向对角线
inline TC::Vector2D Abs(const TC::Vector2D& a)
{
	return TC::Vector2D(abs(a.x), abs(a.y));
}
//TC::Vector2D可用Vec2D简化表示
typedef	TC::Vector2D Vec2D;
//2*2矩阵
struct Mat22
{
	/// The default constructor does nothing (for performance).
	Mat22() {}

	/// Construct this matrix using columns.
	/// 用列向量生成矩形
	Mat22(const Vec2D& c1, const Vec2D& c2)
	{
		ex = c1;
		ey = c2;
	}

	/// Construct this matrix using scalars.
	/// 元素生成
	Mat22(double a11, double a12, double a21, double a22)
	{
		ex.x = a11; ex.y = a21;
		ey.x = a12; ey.y = a22;
	}

	/// Initialize this matrix using columns.
	/// 列向量初始化
	void Set(const Vec2D& c1, const Vec2D& c2)
	{
		ex = c1;
		ey = c2;
	}

	/// Set this to the identity matrix.
	/// 设为标准矩阵
	void SetIdentity()
	{
		ex.x = 1.0f; ey.x = 0.0f;
		ex.y = 0.0f; ey.y = 1.0f;
	}

	/// Set this matrix to all zeros.
	/// 设为零矩阵
	void SetZero()
	{
		ex.x = 0.0f; ey.x = 0.0f;
		ex.y = 0.0f; ey.y = 0.0f;
	}
	//获取转置矩阵
	Mat22 GetInverse() const
	{
		double a = ex.x, b = ey.x, c = ex.y, d = ey.y;
		Mat22 B;
		double det = a * d - b * c;
		if (det != 0.0f)
		{
			det = 1.0 / det;
		}
		B.ex.x = det * d;	B.ey.x = -det * b;
		B.ex.y = -det * c;	B.ey.y = det * a;
		return B;
	}

	/// Solve A * x = b, where b is a column vector. This is more efficient
	/// than computing the inverse in one-shot cases.
	/// 计算 A*x = b
	Vec2D Solve(const Vec2D& b) const
	{
		double a11 = ex.x, a12 = ey.x, a21 = ex.y, a22 = ey.y;
		double det = a11 * a22 - a12 * a21;
		if (det != 0.0f)
		{
			det = 1.0 / det;
		}
		Vec2D x;
		x.x = det * (a22 * b.x - a12 * b.y);
		x.y = det * (a11 * b.y - a21 * b.x);
		return x;
	}

	Vec2D ex, ey;
};
/// Rotation
/// 旋转量，由sin,cos组成,可看作矢量
struct Rot
{
	Rot():s(0),c(1) {};

	/// Initialize from an angle in radians
	/// 通过弧度生成
	explicit Rot(double angle)
	{
		/// TODO_ERIN optimize
		s = sin(angle);
		c = cos(angle);
	}
	explicit Rot(double s_, double c_) {
		s = s_;
		c = c_;
	}
	Rot operator-()const  {
		return Rot{-s,c};
	}
	/// Set using an angle in radians.
	/// 通过弧度初始化
	void Set(double angle)
	{
		/// TODO_ERIN optimize
		s = sin(angle);
		c = cos(angle);
	}

	/// Set to the identity rotation
	/// 标准旋转量，0
	void SetIdentity()
	{
		s = 0.0;
		c = 1.0;
	}

	/// Get the angle in radians
	double GetAngle() const
	{
		return atan2(s, c);
	}

	/// Get the x-axis
	TC::Vector2D GetXAxis() const
	{
		return TC::Vector2D(c, s);
	}

	/// Get the u-axis
	TC::Vector2D GetYAxis() const
	{
		return TC::Vector2D(-s, c);
	}

	/// Sine and cosine
	double s, c;
};

inline TC::Vector2D& TC::Vector2D::Rotate(const Rot& rot)
{
	/*double m_Angle = Angle();
	double m_Length = Length();
	m_Angle += angle;
	x = m_Length * cos(m_Angle);
	y = m_Length * sin(m_Angle);*/

	double s = rot.s;
	double c = rot.c;

	double x1 = x * c - y * s;
	double y1 = y * c + x * s;

	x = x1;
	y = y1;
	return *this;
}
inline TC::Vector2D& TC::Vector2D::RotateT(const Rot& rot) {
	double s = rot.s;
	double c = rot.c;

	double x1 = x * c + y * s;
	double y1 = y * c - x * s;

	x = x1;
	y = y1;
	return *this;
}
//一个基本变换
//包括一个平移(用2D矢量表示)、一个旋转(用旋转量Rot表示)
struct Transform
{
	/// The default constructor does nothing.
	Transform() {}

	/// Initialize using a position vector and a rotation.
	Transform(const TC::Vector2D& position, const Rot& rotation) : p(position), q(rotation) {}

	/// Set this to the identity transform.
	void SetIdentity()
	{
		p.SetZero();
		q.SetIdentity();
	}

	/// Set this based on the position and angle.
	void Set(const TC::Vector2D& position, double angle)
	{
		p = position;
		q.Set(angle);
	}

	TC::Vector2D p;
	Rot q;
};

/// Perform the dot product on two vectors.
inline double Dot(const Vec2D& a, const Vec2D& b)
{
	return a.x * b.x + a.y * b.y;
}

/// Perform the cross product on two vectors. In 2D this produces a scalar.
inline double Cross(const Vec2D& a, const Vec2D& b)
{
	return a.x * b.y - a.y * b.x;
}

/// Perform the cross product on a vector and a scalar. In 2D this produces
/// a vector.
inline Vec2D Cross(const Vec2D& a, double s)
{
	return Vec2D(s * a.y, -s * a.x);
}

/// Perform the cross product on a scalar and a vector. In 2D this produces
/// a vector.
inline Vec2D Cross(double s, const Vec2D& a)
{
	return Vec2D(-s * a.y, s * a.x);
}

/// Multiply a matrix times a vector. If a rotation matrix is provided,
/// then this transforms the vector from one frame to another.
inline Vec2D Mul(const Mat22& A, const Vec2D& v)
{
	return Vec2D(A.ex.x * v.x + A.ey.x * v.y, A.ex.y * v.x + A.ey.y * v.y);
}

/// Multiply a matrix transpose times a vector. If a rotation matrix is provided,
/// then this transforms the vector from one frame to another (inverse transform).
inline Vec2D MulT(const Mat22& A, const Vec2D& v)
{
	return Vec2D(Dot(v, A.ex), Dot(v, A.ey));
}
inline double Distance(const Vec2D& a, const Vec2D& b)
{
	Vec2D c = a - b;
	return c.Length();
}

inline double DistanceSquared(const Vec2D& a, const Vec2D& b)
{
	Vec2D c = a - b;
	return Dot(c, c);
}

inline Mat22 operator + (const Mat22& A, const Mat22& B)
{
	return Mat22(A.ex + B.ex, A.ey + B.ey);
}

// A * B
inline Mat22 Mul(const Mat22& A, const Mat22& B)
{
	return Mat22(Mul(A, B.ex), Mul(A, B.ey));
}

// A^T * B
inline Mat22 MulT(const Mat22& A, const Mat22& B)
{
	Vec2D c1(Dot(A.ex, B.ex), Dot(A.ey, B.ex));
	Vec2D c2(Dot(A.ex, B.ey), Dot(A.ey, B.ey));
	return Mat22(c1, c2);
}


/// Multiply two rotations: q * r
inline Rot Mul(const Rot& q, const Rot& r)
{
	// [qc -qs] * [rc -rs] = [qc*rc-qs*rs -qc*rs-qs*rc]
	// [qs  qc]   [rs  rc]   [qs*rc+qc*rs -qs*rs+qc*rc]
	// s = qs * rc + qc * rs
	// c = qc * rc - qs * rs
	Rot qr;
	qr.s = q.s * r.c + q.c * r.s;
	qr.c = q.c * r.c - q.s * r.s;
	return qr;
}

/// Transpose multiply two rotations: qT * r
inline Rot MulT(const Rot& q, const Rot& r)
{
	// [ qc qs] * [rc -rs] = [qc*rc+qs*rs -qc*rs+qs*rc]
	// [-qs qc]   [rs  rc]   [-qs*rc+qc*rs qs*rs+qc*rc]
	// s = qc * rs - qs * rc
	// c = qc * rc + qs * rs
	Rot qr;
	qr.s = q.c * r.s - q.s * r.c;
	qr.c = q.c * r.c + q.s * r.s;
	return qr;
}

/// Rotate a vector
inline Vec2D Mul(const Rot& q, const Vec2D& v)
{
	return Vec2D(q.c * v.x - q.s * v.y, q.s * v.x + q.c * v.y);
}

/// Inverse rotate a vector
inline Vec2D MulT(const Rot& q, const Vec2D& v)
{
	return Vec2D(q.c * v.x + q.s * v.y, -q.s * v.x + q.c * v.y);
}

inline Vec2D Mul(const Transform& T, const Vec2D& v)
{
	double x = (T.q.c * v.x - T.q.s * v.y) + T.p.x;
	double y = (T.q.s * v.x + T.q.c * v.y) + T.p.y;

	return Vec2D(x, y);
}

inline Vec2D MulT(const Transform& T, const Vec2D& v)
{
	double px = v.x - T.p.x;
	double py = v.y - T.p.y;
	double x = (T.q.c * px + T.q.s * py);
	double y = (-T.q.s * px + T.q.c * py);

	return Vec2D(x, y);
}

// v2 = A.q.Rot(B.q.Rot(v1) + B.p) + A.p
//    = (A.q * B.q).Rot(v1) + A.q.Rot(B.p) + A.p
inline Transform Mul(const Transform& A, const Transform& B)
{
	Transform C;
	C.q = Mul(A.q, B.q);
	C.p = Mul(A.q, B.p) + A.p;
	return C;
}

// v2 = A.q' * (B.q * v1 + B.p - A.p)
//    = A.q' * B.q * v1 + A.q' * (B.p - A.p)
inline Transform MulT(const Transform& A, const Transform& B)
{
	Transform C;
	C.q = MulT(A.q, B.q);
	C.p = MulT(A.q, B.p - A.p);
	return C;
}

//ret.p = A.p
//ret.q = Mul(A.q,B);
inline Transform Add(const Transform& A, const Rot& B)
{
	Transform C(A);
	C.q = Mul(A.q, B);
	return C;
}