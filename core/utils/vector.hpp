#pragma once

#ifdef NDEBUG
#define Assert( _exp ) ((void)0)
#else
#define Assert(x)
#endif

#include <sstream>

#define CHECK_VALID( _v ) 0

#define FastSqrt(x)	(sqrt)(x)

#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h

#define M_PI_2      (M_PI * 2.f)

#define M_PI_F		((float)(M_PI))	// Shouldn't collide with anything.

#define M_PHI		1.61803398874989484820 // golden ratio

// NJS: Inlined to prevent floats from being autopromoted to doubles, as with the old system.
#ifndef RAD2DEG
#define RAD2DEG(x)  ((float)(x) * (float)(180.f / M_PI_F))
#endif

#ifndef DEG2RAD
#define DEG2RAD(x)  ((float)(x) * (float)(M_PI_F / 180.f))
#endif

// MOVEMENT INFO
enum
{
	PITCH = 0,	// up / down
	YAW,		// left / right
	ROLL		// fall over
};

// decls for aligning data


#define ALIGN16 __declspec(align(16))
#define VALVE_RAND_MAX 0x7fff
#define vectorExpand(v) (v).x, (v).y, (v).z

typedef float vec_t;

class vector
{
public:
	float x, y, z;
	vector(void);
	vector(float X, float Y, float Z);
	void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f);
	bool IsValid() const;
	float operator[](int i) const;
	float& operator[](int i);
	inline void Zero();
	bool operator==(const vector& v) const;
	bool operator!=(const vector& v) const;
	inline vector&	operator+=(const vector &v);
	inline vector&	operator-=(const vector &v);
	inline vector&	operator*=(const vector &v);
	inline vector&	operator*=(float s);
	inline vector&	operator/=(const vector &v);
	inline vector&	operator/=(float s);
	inline vector&	operator+=(float fl);
	inline vector&	operator-=(float fl);
	inline float	Length() const;
	inline float LengthSqr(void) const
	{
		CHECK_VALID(*this);
		return (x*x + y * y + z * z);
	}
	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance &&
			z > -tolerance && z < tolerance);
	}
	vector	Normalize();
	float	NormalizeInPlace();
	inline float	DistTo(const vector &vOther) const;
	inline float	DistToSqr(const vector &vOther) const;
	float	Dot(const vector& vOther) const;
	float	Length2D(void) const;
	float	Length2DSqr(void) const;
	void	MulAdd(const vector& a, const vector& b, float scalar);
	vector& operator=(const vector &vOther);
	vector	operator-(void) const;
	vector	operator+(const vector& v) const;
	vector	operator-(const vector& v) const;
	vector	operator*(const vector& v) const;
	vector	operator/(const vector& v) const;
	vector	operator*(float fl) const;
	vector	operator/(float fl) const;
	// Base address...
	float* Base();
	float const* Base() const;
};

//===============================================
inline void vector::Init(float ix, float iy, float iz)
{
	x = ix; y = iy; z = iz;
	CHECK_VALID(*this);
}
//===============================================
inline vector::vector(float X, float Y, float Z)
{
	x = X; y = Y; z = Z;
	CHECK_VALID(*this);
}
//===============================================
inline vector::vector(void) { }
//===============================================
inline void vector::Zero()
{
	x = y = z = 0.0f;
}
//===============================================
inline void vectorClear(vector& a)
{
	a.x = a.y = a.z = 0.0f;
}
//===============================================
inline vector& vector::operator=(const vector &vOther)
{
	CHECK_VALID(vOther);
	x = vOther.x; y = vOther.y; z = vOther.z;
	return *this;
}
//===============================================
inline float& vector::operator[](int i)
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}
//===============================================
inline float vector::operator[](int i) const
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}
//===============================================
inline bool vector::operator==(const vector& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x == x) && (src.y == y) && (src.z == z);
}
//===============================================
inline bool vector::operator!=(const vector& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x != x) || (src.y != y) || (src.z != z);
}
//===============================================
inline void vectorCopy(const vector& src, vector& dst)
{
	CHECK_VALID(src);
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
}
//===============================================
inline  vector& vector::operator+=(const vector& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x += v.x; y += v.y; z += v.z;
	return *this;
}
//===============================================
inline  vector& vector::operator-=(const vector& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x -= v.x; y -= v.y; z -= v.z;
	return *this;
}
//===============================================
inline  vector& vector::operator*=(float fl)
{
	x *= fl;
	y *= fl;
	z *= fl;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
inline  vector& vector::operator*=(const vector& v)
{
	CHECK_VALID(v);
	x *= v.x;
	y *= v.y;
	z *= v.z;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
inline vector&	vector::operator+=(float fl)
{
	x += fl;
	y += fl;
	z += fl;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
inline vector&	vector::operator-=(float fl)
{
	x -= fl;
	y -= fl;
	z -= fl;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
inline  vector& vector::operator/=(float fl)
{
	Assert(fl != 0.0f);
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
inline  vector& vector::operator/=(const vector& v)
{
	CHECK_VALID(v);
	Assert(v.x != 0.0f && v.y != 0.0f && v.z != 0.0f);
	x /= v.x;
	y /= v.y;
	z /= v.z;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
inline float vector::Length(void) const
{
	CHECK_VALID(*this);

	float root = 0.0f;

	float sqsr = x * x + y * y + z * z;

	root = sqrt(sqsr);

	return root;
}
//===============================================
inline float vector::Length2D(void) const
{
	CHECK_VALID(*this);

	float root = 0.0f;

	float sqst = x * x + y * y;

	root = sqrt(sqst);

	return root;
}
//===============================================
inline float vector::Length2DSqr(void) const
{
	return (x*x + y * y);
}
//===============================================
inline vector CrossProduct(const vector& a, const vector& b)
{
	return vector(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}
//===============================================
float vector::DistTo(const vector &vOther) const
{
	vector delta;

	delta.x = x - vOther.x;
	delta.y = y - vOther.y;
	delta.z = z - vOther.z;

	return delta.Length();
}
float vector::DistToSqr(const vector &vOther) const
{
	vector delta;

	delta.x = x - vOther.x;
	delta.y = y - vOther.y;
	delta.z = z - vOther.z;

	return delta.LengthSqr();
}
//===============================================
inline vector vector::Normalize()
{
	vector vector;
	float length = this->Length();

	if (length != 0)
	{
		vector.x = x / length;
		vector.y = y / length;
		vector.z = z / length;
	}
	else
	{
		vector.x = vector.y = 0.0f; vector.z = 1.0f;
	}

	return vector;
}
//===============================================
// changed that to fit awall, paste from xaE
inline float vector::NormalizeInPlace()
{
	float radius = FastSqrt(x * x + y * y + z * z);

	// FLT_EPSILON is added to the radius to eliminate the possibility of divide by zero.
	float iradius = 1.f / (radius + FLT_EPSILON);

	x *= iradius;
	y *= iradius;
	z *= iradius;

	return radius;
}
//===============================================
inline void vector::MulAdd(const vector& a, const vector& b, float scalar)
{
	x = a.x + b.x * scalar;
	y = a.y + b.y * scalar;
	z = a.z + b.z * scalar;
}
//===============================================
inline float vectorNormalize(vector& v)
{
	Assert(v.IsValid());
	float l = v.Length();
	if (l != 0.0f)
	{
		v /= l;
	}
	else
	{
		// FIXME:
		// Just copying the existing implemenation; shouldn't res.z == 0?
		v.x = v.y = 0.0f; v.z = 1.0f;
	}
	return l;
}
//===============================================
inline float vectorNormalize(float * v)
{
	return vectorNormalize(*(reinterpret_cast<vector *>(v)));
}
//===============================================
inline vector vector::operator+(const vector& v) const
{
	vector res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	return res;
}

//===============================================
inline vector vector::operator-(const vector& v) const
{
	vector res;
	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;
	return res;
}
//===============================================
inline vector vector::operator*(float fl) const
{
	vector res;
	res.x = x * fl;
	res.y = y * fl;
	res.z = z * fl;
	return res;
}
//===============================================
inline vector vector::operator*(const vector& v) const
{
	vector res;
	res.x = x * v.x;
	res.y = y * v.y;
	res.z = z * v.z;
	return res;
}
//===============================================
inline vector vector::operator/(float fl) const
{
	vector res;
	res.x = x / fl;
	res.y = y / fl;
	res.z = z / fl;
	return res;
}
//===============================================
inline vector vector::operator/(const vector& v) const
{
	vector res;
	res.x = x / v.x;
	res.y = y / v.y;
	res.z = z / v.z;
	return res;
}
inline float vector::Dot(const vector& vOther) const
{
	const vector& a = *this;

	return(a.x*vOther.x + a.y*vOther.y + a.z*vOther.z);
}

//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------

inline float vectorLength(const vector& v)
{
	CHECK_VALID(v);
	return (float)FastSqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

//vector SUBTRAC
inline void vectorSubtract(const vector& a, const vector& b, vector& c)
{
	CHECK_VALID(a);
	CHECK_VALID(b);
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
}

//vectorADD
inline void vectorAdd(const vector& a, const vector& b, vector& c)
{
	CHECK_VALID(a);
	CHECK_VALID(b);
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------
inline float* vector::Base()
{
	return (float*)this;
}

inline float const* vector::Base() const
{
	return (float const*)this;
}

inline void vectorMAInline(const float* start, float scale, const float* direction, float* dest)
{
	dest[0] = start[0] + direction[0] * scale;
	dest[1] = start[1] + direction[1] * scale;
	dest[2] = start[2] + direction[2] * scale;
}

inline void vectorMAInline(const vector& start, float scale, const vector& direction, vector& dest)
{
	dest.x = start.x + direction.x*scale;
	dest.y = start.y + direction.y*scale;
	dest.z = start.z + direction.z*scale;
}

inline void vectorMA(const vector& start, float scale, const vector& direction, vector& dest)
{
	vectorMAInline(start, scale, direction, dest);
}

inline void vectorMA(const float * start, float scale, const float *direction, float *dest)
{
	vectorMAInline(start, scale, direction, dest);
}


class ALIGN16 vectorAligned : public vector
{
public:
	inline vectorAligned(void) {};
	inline vectorAligned(float X, float Y, float Z)
	{
		Init(X, Y, Z);
	}

#ifdef vector_NO_SLOW_OPERATIONS

private:
	// No copy constructors allowed if we're in optimal mode
	vectorAligned(const vectorAligned& vOther);
	vectorAligned(const vector &vOther);

#else
public:
	explicit vectorAligned(const vector &vOther)
	{
		Init(vOther.x, vOther.y, vOther.z);
	}

	vectorAligned& operator=(const vector &vOther)
	{
		Init(vOther.x, vOther.y, vOther.z);
		return *this;
	}

#endif
	float w;	// this space is used anyway
};


inline unsigned long& FloatBits(float& f)
{
	return *reinterpret_cast<unsigned long*>(&f);
}

inline bool IsFinite(float f)
{
	return ((FloatBits(f) & 0x7F800000) != 0x7F800000);
}

//=========================================================
// 2D vector2D
//=========================================================

class vector2D
{
public:
	// Members
	float x, y;

	// Construction/destruction
	vector2D(void);
	vector2D(float X, float Y);
	vector2D(const float *pFloat);

	// Initialization
	void Init(float ix = 0.0f, float iy = 0.0f);

	// Got any nasty NAN's?
	bool IsValid() const;

	// array access...
	float  operator[](int i) const;
	float& operator[](int i);

	// Base address...
	float*       Base();
	float const* Base() const;

	// Initialization methods
	void Random(float minVal, float maxVal);

	// equality
	bool operator==(const vector2D& v) const;
	bool operator!=(const vector2D& v) const;

	// arithmetic operations
	vector2D& operator+=(const vector2D& v);
	vector2D& operator-=(const vector2D& v);
	vector2D& operator*=(const vector2D& v);
	vector2D& operator*=(float           s);
	vector2D& operator/=(const vector2D& v);
	vector2D& operator/=(float           s);

	// negate the vector2D components
	void Negate();

	// Get the vector2D's magnitude.
	float Length() const;

	// Get the vector2D's magnitude squared.
	float LengthSqr(void) const;

	// return true if this vector is (0,0) within tolerance
	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance);
	}

	float Normalize();

	// Normalize in place and return the old length.
	float NormalizeInPlace();

	// Compare length.
	bool IsLengthGreaterThan(float val) const;
	bool IsLengthLessThan(float    val) const;

	// Get the distance from this vector2D to the other one.
	float DistTo(const vector2D& vOther) const;

	// Get the distance from this vector2D to the other one squared.
	float DistToSqr(const vector2D& vOther) const;

	// Copy
	void CopyToArray(float* rgfl) const;

	// Multiply, add, and assign to this (ie: *this = a + b * scalar). This
	// is about 12% faster than the actual vector2D equation (because it's done per-component
	// rather than per-vector2D).
	void MulAdd(const vector2D& a, const vector2D& b, float scalar);

	// Dot product.
	float Dot(const vector2D& vOther) const;

	// assignment
	vector2D& operator=(const vector2D& vOther);

#ifndef vector_NO_SLOW_OPERATIONS
	// copy constructors
	vector2D(const vector2D &vOther);

	// arithmetic operations
	vector2D operator-(void) const;

	vector2D operator+(const vector2D& v) const;
	vector2D operator-(const vector2D& v) const;
	vector2D operator*(const vector2D& v) const;
	vector2D operator/(const vector2D& v) const;
	vector2D operator+(const int       i1) const;
	vector2D operator+(const float     fl) const;
	vector2D operator*(const float     fl) const;
	vector2D operator/(const float     fl) const;

	// Cross product between two vectors.
	vector2D Cross(const vector2D& vOther) const;

	// Returns a vector2D with the min or max in X, Y, and Z.
	vector2D Min(const vector2D& vOther) const;
	vector2D Max(const vector2D& vOther) const;

#else

private:
	// No copy constructors allowed if we're in optimal mode
	vector2D(const vector2D& vOther);
#endif
};

//-----------------------------------------------------------------------------

const vector2D vec2_origin(0, 0);
//const vector2D vec2_invalid(3.40282347E+38F, 3.40282347E+38F);

//-----------------------------------------------------------------------------
// vector2D related operations
//-----------------------------------------------------------------------------

// vector2D clear
void vector2DClear(vector2D& a);

// Copy
void vector2DCopy(const vector2D& src, vector2D& dst);

// vector2D arithmetic
void vector2DAdd(const vector2D&      a, const vector2D& b, vector2D&       result);
void vector2DSubtract(const vector2D& a, const vector2D& b, vector2D&       result);
void vector2DMultiply(const vector2D& a, float           b, vector2D&       result);
void vector2DMultiply(const vector2D& a, const vector2D& b, vector2D&       result);
void vector2DDivide(const vector2D&   a, float           b, vector2D&       result);
void vector2DDivide(const vector2D&   a, const vector2D& b, vector2D&       result);
void vector2DMA(const vector2D&       start, float       s, const vector2D& dir, vector2D& result);

// Store the min or max of each of x, y, and z into the result.
void vector2DMin(const vector2D& a, const vector2D& b, vector2D& result);
void vector2DMax(const vector2D& a, const vector2D& b, vector2D& result);

#define vector2DExpand( v ) (v).x, (v).y

// Normalization
float vector2DNormalize(vector2D& v);

// Length
float vector2DLength(const vector2D& v);

// Dot Product
float DotProduct2D(const vector2D& a, const vector2D& b);

// Linearly interpolate between two vectors
void vector2DLerp(const vector2D& src1, const vector2D& src2, float t, vector2D& dest);


//-----------------------------------------------------------------------------
//
// Inlined vector2D methods
//
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// constructors
//-----------------------------------------------------------------------------

inline vector2D::vector2D(void)
{
#ifdef _DEBUG
	// Initialize to NAN to catch errors
	//x = y = float_NAN;
#endif
}

inline vector2D::vector2D(float X, float Y)
{
	x = X; y = Y;
	Assert(IsValid());
}

inline vector2D::vector2D(const float *pFloat)
{
	Assert(pFloat);
	x = pFloat[0]; y = pFloat[1];
	Assert(IsValid());
}


//-----------------------------------------------------------------------------
// copy constructor
//-----------------------------------------------------------------------------

inline vector2D::vector2D(const vector2D &vOther)
{
	Assert(vOther.IsValid());
	x = vOther.x; y = vOther.y;
}

//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------

inline void vector2D::Init(float ix, float iy)
{
	x = ix; y = iy;
	Assert(IsValid());
}

inline void vector2D::Random(float minVal, float maxVal)
{
	x = minVal + ((float)rand() / VALVE_RAND_MAX) * (maxVal - minVal);
	y = minVal + ((float)rand() / VALVE_RAND_MAX) * (maxVal - minVal);
}

inline void vector2DClear(vector2D& a)
{
	a.x = a.y = 0.0f;
}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------

inline vector2D& vector2D::operator=(const vector2D &vOther)
{
	Assert(vOther.IsValid());
	x = vOther.x; y = vOther.y;
	return *this;
}

//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------

inline float& vector2D::operator[](int i)
{
	Assert((i >= 0) && (i < 2));
	return ((float*)this)[i];
}

inline float vector2D::operator[](int i) const
{
	Assert((i >= 0) && (i < 2));
	return ((float*)this)[i];
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------

inline float* vector2D::Base()
{
	return (float*)this;
}

inline float const* vector2D::Base() const
{
	return (float const*)this;
}

//-----------------------------------------------------------------------------
// IsValid?
//-----------------------------------------------------------------------------

inline bool vector2D::IsValid() const
{
	return IsFinite(x) && IsFinite(y);
}

//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------

inline bool vector2D::operator==(const vector2D& src) const
{
	Assert(src.IsValid() && IsValid());
	return (src.x == x) && (src.y == y);
}

inline bool vector2D::operator!=(const vector2D& src) const
{
	Assert(src.IsValid() && IsValid());
	return (src.x != x) || (src.y != y);
}


//-----------------------------------------------------------------------------
// Copy
//-----------------------------------------------------------------------------

inline void vector2DCopy(const vector2D& src, vector2D& dst)
{
	Assert(src.IsValid());
	dst.x = src.x;
	dst.y = src.y;
}

inline void	vector2D::CopyToArray(float* rgfl) const
{
	Assert(IsValid());
	Assert(rgfl);
	rgfl[0] = x; rgfl[1] = y;
}

//-----------------------------------------------------------------------------
// standard math operations
//-----------------------------------------------------------------------------

inline void vector2D::Negate()
{
	Assert(IsValid());
	x = -x; y = -y;
}

inline vector2D& vector2D::operator+=(const vector2D& v)
{
	Assert(IsValid() && v.IsValid());
	x += v.x; y += v.y;
	return *this;
}

inline vector2D& vector2D::operator-=(const vector2D& v)
{
	Assert(IsValid() && v.IsValid());
	x -= v.x; y -= v.y;
	return *this;
}

inline vector2D& vector2D::operator*=(float fl)
{
	x *= fl;
	y *= fl;
	Assert(IsValid());
	return *this;
}

inline vector2D& vector2D::operator*=(const vector2D& v)
{
	x *= v.x;
	y *= v.y;
	Assert(IsValid());
	return *this;
}

inline vector2D& vector2D::operator/=(float fl)
{
	Assert(fl != 0.0f);
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	Assert(IsValid());
	return *this;
}

inline vector2D& vector2D::operator/=(const vector2D& v)
{
	Assert(v.x != 0.0f && v.y != 0.0f);
	x /= v.x;
	y /= v.y;
	Assert(IsValid());
	return *this;
}

inline void vector2DAdd(const vector2D& a, const vector2D& b, vector2D& c)
{
	Assert(a.IsValid() && b.IsValid());
	c.x = a.x + b.x;
	c.y = a.y + b.y;
}

inline void vector2DAdd(const vector2D& a, const int b, vector2D& c)
{
	Assert(a.IsValid());
	c.x = a.x + b;
	c.y = a.y + b;
}

inline void vector2DAdd(const vector2D& a, const float b, vector2D& c)
{
	Assert(a.IsValid());
	c.x = a.x + b;
	c.y = a.y + b;
}

inline void vector2DSubtract(const vector2D& a, const vector2D& b, vector2D& c)
{
	Assert(a.IsValid() && b.IsValid());
	c.x = a.x - b.x;
	c.y = a.y - b.y;
}

inline void vector2DMultiply(const vector2D& a, const float b, vector2D& c)
{
	Assert(a.IsValid() && IsFinite(b));
	c.x = a.x * b;
	c.y = a.y * b;
}

inline void vector2DMultiply(const vector2D& a, const vector2D& b, vector2D& c)
{
	Assert(a.IsValid() && b.IsValid());
	c.x = a.x * b.x;
	c.y = a.y * b.y;
}


inline void vector2DDivide(const vector2D& a, const float b, vector2D& c)
{
	Assert(a.IsValid());
	Assert(b != 0.0f);
	float oob = 1.0f / b;
	c.x = a.x * oob;
	c.y = a.y * oob;
}

inline void vector2DDivide(const vector2D& a, const vector2D& b, vector2D& c)
{
	Assert(a.IsValid());
	Assert((b.x != 0.0f) && (b.y != 0.0f));
	c.x = a.x / b.x;
	c.y = a.y / b.y;
}

inline void vector2DMA(const vector2D& start, float s, const vector2D& dir, vector2D& result)
{
	Assert(start.IsValid() && IsFinite(s) && dir.IsValid());
	result.x = start.x + s * dir.x;
	result.y = start.y + s * dir.y;
}

// FIXME: Remove
// For backwards compatability
inline void	vector2D::MulAdd(const vector2D& a, const vector2D& b, float scalar)
{
	x = a.x + b.x * scalar;
	y = a.y + b.y * scalar;
}

inline void vector2DLerp(const vector2D& src1, const vector2D& src2, float t, vector2D& dest)
{
	dest[0] = src1[0] + (src2[0] - src1[0]) * t;
	dest[1] = src1[1] + (src2[1] - src1[1]) * t;
}

//-----------------------------------------------------------------------------
// dot, cross
//-----------------------------------------------------------------------------
inline float DotProduct2D(const vector2D& a, const vector2D& b)
{
	Assert(a.IsValid() && b.IsValid());
	return(a.x*b.x + a.y*b.y);
}

// for backwards compatability
inline float vector2D::Dot(const vector2D& vOther) const
{
	return DotProduct2D(*this, vOther);
}


//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------
inline float vector2DLength(const vector2D& v)
{
	Assert(v.IsValid());
	return (float)FastSqrt(v.x*v.x + v.y*v.y);
}

inline float vector2D::LengthSqr(void) const
{
	Assert(IsValid());
	return (x*x + y * y);
}

inline float vector2D::NormalizeInPlace()
{
	return vector2DNormalize(*this);
}

inline bool vector2D::IsLengthGreaterThan(float val) const
{
	return LengthSqr() > val*val;
}

inline bool vector2D::IsLengthLessThan(float val) const
{
	return LengthSqr() < val*val;
}

inline float vector2D::Length(void) const
{
	return vector2DLength(*this);
}


inline void vector2DMin(const vector2D &a, const vector2D &b, vector2D &result)
{
	result.x = (a.x < b.x) ? a.x : b.x;
	result.y = (a.y < b.y) ? a.y : b.y;
}


inline void vector2DMax(const vector2D &a, const vector2D &b, vector2D &result)
{
	result.x = (a.x > b.x) ? a.x : b.x;
	result.y = (a.y > b.y) ? a.y : b.y;
}


//-----------------------------------------------------------------------------
// Normalization
//-----------------------------------------------------------------------------
inline float vector2DNormalize(vector2D& v)
{
	Assert(v.IsValid());
	float l = v.Length();
	if (l != 0.0f)
	{
		v /= l;
	}
	else
	{
		v.x = v.y = 0.0f;
	}
	return l;
}


//-----------------------------------------------------------------------------
// Get the distance from this vector2D to the other one
//-----------------------------------------------------------------------------
inline float vector2D::DistTo(const vector2D &vOther) const
{
	vector2D delta;
	vector2DSubtract(*this, vOther, delta);
	return delta.Length();
}

inline float vector2D::DistToSqr(const vector2D &vOther) const
{
	vector2D delta;
	vector2DSubtract(*this, vOther, delta);
	return delta.LengthSqr();
}


//-----------------------------------------------------------------------------
// Computes the closest point to vecTarget no farther than flMaxDist from vecStart
//-----------------------------------------------------------------------------
inline void ComputeClosestPoint2D(const vector2D& vecStart, float flMaxDist, const vector2D& vecTarget, vector2D *pResult)
{
	vector2D vecDelta;
	vector2DSubtract(vecTarget, vecStart, vecDelta);
	float flDistSqr = vecDelta.LengthSqr();
	if (flDistSqr <= flMaxDist * flMaxDist)
	{
		*pResult = vecTarget;
	}
	else
	{
		vecDelta /= FastSqrt(flDistSqr);
		vector2DMA(vecStart, flMaxDist, vecDelta, *pResult);
	}
}



//-----------------------------------------------------------------------------
//
// Slow methods
//
//-----------------------------------------------------------------------------

#ifndef vector_NO_SLOW_OPERATIONS
#endif
//-----------------------------------------------------------------------------
// Returns a vector2D with the min or max in X, Y, and Z.
//-----------------------------------------------------------------------------

inline vector2D vector2D::Min(const vector2D &vOther) const
{
	return vector2D(x < vOther.x ? x : vOther.x,
		y < vOther.y ? y : vOther.y);
}

inline vector2D vector2D::Max(const vector2D &vOther) const
{
	return vector2D(x > vOther.x ? x : vOther.x,
		y > vOther.y ? y : vOther.y);
}


//-----------------------------------------------------------------------------
// arithmetic operations
//-----------------------------------------------------------------------------

inline vector2D vector2D::operator-(void) const
{
	return vector2D(-x, -y);
}

inline vector2D vector2D::operator+(const vector2D& v) const
{
	vector2D res;
	vector2DAdd(*this, v, res);
	return res;
}

inline vector2D vector2D::operator-(const vector2D& v) const
{
	vector2D res;
	vector2DSubtract(*this, v, res);
	return res;
}

inline vector2D vector2D::operator+(const int i1) const
{
	vector2D res;
	vector2DAdd(*this, i1, res);
	return res;
}

inline vector2D vector2D::operator+(const float fl) const
{
	vector2D res;
	vector2DAdd(*this, fl, res);
	return res;
}

inline vector2D vector2D::operator*(const float fl) const
{
	vector2D res;
	vector2DMultiply(*this, fl, res);
	return res;
}

inline vector2D vector2D::operator*(const vector2D& v) const
{
	vector2D res;
	vector2DMultiply(*this, v, res);
	return res;
}

inline vector2D vector2D::operator/(const float fl) const
{
	vector2D res;
	vector2DDivide(*this, fl, res);
	return res;
}

inline vector2D vector2D::operator/(const vector2D& v) const
{
	vector2D res;
	vector2DDivide(*this, v, res);
	return res;
}

inline vector2D operator*(const float fl, const vector2D& v)
{
	return v * fl;
}

class QAngleByValue;
class QAngle
{
public:
	// Members
	float x, y, z;

	// Construction/destruction
	QAngle(void);
	QAngle(float X, float Y, float Z);
	//      QAngle(RadianEuler const &angles);      // evil auto type promotion!!!

	// Allow pass-by-value
	operator QAngleByValue &() { return *((QAngleByValue *)(this)); }
	operator const QAngleByValue &() const { return *((const QAngleByValue *)(this)); }

	// Initialization
	void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f);
	void Random(float minVal, float maxVal);

	// Got any nasty NAN's?
	bool IsValid() const;
	void Invalidate();

	// array access...
	float operator[](int i) const;
	float& operator[](int i);

	// Base address...
	float* Base();
	float const* Base() const;

	// equality
	bool operator==(const QAngle& v) const;
	bool operator!=(const QAngle& v) const;

	// arithmetic operations
	QAngle& operator+=(const QAngle &v);
	QAngle& operator-=(const QAngle &v);
	QAngle& operator*=(float s);
	QAngle& operator/=(float s);

	// Get the vector's magnitude.
	float   Length() const;
	float   LengthSqr() const;

	// negate the QAngle components
	//void  Negate();

	// No assignment operators either...
	QAngle& operator=(const QAngle& src);

#ifndef vector_NO_SLOW_OPERATIONS
	// copy constructors

	// arithmetic operations
	QAngle  operator-(void) const;

	QAngle  operator+(const QAngle& v) const;
	QAngle  operator-(const QAngle& v) const;
	QAngle  operator*(float fl) const;
	QAngle  operator*(const QAngle& v) const;
	QAngle  operator/(float fl) const;
#else

private:
	// No copy constructors allowed if we're in optimal mode
	QAngle(const QAngle& vOther);

#endif
};

//-----------------------------------------------------------------------------
// constructors
//-----------------------------------------------------------------------------
inline QAngle::QAngle(void)
{
#ifdef _DEBUG
#ifdef vector_PARANOIA
	// Initialize to NAN to catch errors
	x = y = z = VEC_T_NAN;
#endif
#endif
}

inline QAngle::QAngle(float X, float Y, float Z)
{
	x = X; y = Y; z = Z;
	CHECK_VALID(*this);
}

//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------
inline void QAngle::Init(float ix, float iy, float iz)
{
	x = ix; y = iy; z = iz;
	CHECK_VALID(*this);
}

inline void QAngle::Random(float minVal, float maxVal)
{
	x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	z = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	CHECK_VALID(*this);
}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------
inline QAngle& QAngle::operator=(const QAngle &vOther)
{
	CHECK_VALID(vOther);
	x = vOther.x; y = vOther.y; z = vOther.z;
	return *this;
}

//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------
inline bool QAngle::operator==(const QAngle& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x == x) && (src.y == y) && (src.z == z);
}

inline bool QAngle::operator!=(const QAngle& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x != x) || (src.y != y) || (src.z != z);
}

//-----------------------------------------------------------------------------
// standard math operations
//-----------------------------------------------------------------------------
inline QAngle& QAngle::operator+=(const QAngle& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x += v.x; y += v.y; z += v.z;
	return *this;
}

inline QAngle& QAngle::operator-=(const QAngle& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x -= v.x; y -= v.y; z -= v.z;
	return *this;
}

inline QAngle& QAngle::operator*=(float fl)
{
	x *= fl;
	y *= fl;
	z *= fl;
	CHECK_VALID(*this);
	return *this;
}

inline QAngle& QAngle::operator/=(float fl)
{
	Assert(fl != 0.0f);
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;
	CHECK_VALID(*this);
	return *this;
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------
inline float* QAngle::Base()
{
	return (float*)this;
}

inline float const* QAngle::Base() const
{
	return (float const*)this;
}

//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------
inline float& QAngle::operator[](int i)
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}

inline float QAngle::operator[](int i) const
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}

//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------
inline float QAngle::Length() const
{
	CHECK_VALID(*this);
	return (float)FastSqrt(LengthSqr());
}


inline float QAngle::LengthSqr() const
{
	CHECK_VALID(*this);
	return x * x + y * y + z * z;
}


//-----------------------------------------------------------------------------
// arithmetic operations (SLOW!!)
//-----------------------------------------------------------------------------
#ifndef vector_NO_SLOW_OPERATIONS

inline QAngle QAngle::operator-(void) const
{
	return QAngle(-x, -y, -z);
}

inline QAngle QAngle::operator+(const QAngle& v) const
{
	QAngle res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	return res;
}

inline QAngle QAngle::operator-(const QAngle& v) const
{
	QAngle res;
	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;
	return res;
}

inline QAngle QAngle::operator*(float fl) const
{
	QAngle res;
	res.x = x * fl;
	res.y = y * fl;
	res.z = z * fl;
	return res;
}

inline QAngle QAngle::operator*(const QAngle& v) const
{
	QAngle res;
	res.x = x * v.x;
	res.y = y * v.y;
	res.z = z * v.z;
	return res;
}

inline QAngle QAngle::operator/(float fl) const
{
	QAngle res;
	res.x = x / fl;
	res.y = y / fl;
	res.z = z / fl;
	return res;
}

inline QAngle operator*(float fl, const QAngle& v)
{
	return v * fl;
}

#endif // vector_NO_SLOW_OPERATIONS


//QANGLE SUBTRAC
inline void QAngleSubtract(const QAngle& a, const QAngle& b, QAngle& c)
{
	CHECK_VALID(a);
	CHECK_VALID(b);
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
}

//QANGLEADD
inline void QAngleAdd(const QAngle& a, const QAngle& b, QAngle& c)
{
	CHECK_VALID(a);
	CHECK_VALID(b);
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
}