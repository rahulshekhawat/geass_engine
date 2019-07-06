#pragma once

#include "pch.h"
#include "glib.h"

class MSVector;
class MSVector2;

class GEASS_API FVector3
{
public:

	__forceinline FVector3() { ; }
	__forceinline FVector3(int i) : x(static_cast<float>(i)), y(static_cast<float>(i)), z(static_cast<float>(i)) { ; }
	__forceinline FVector3(float f) : x(f), y(f), z(f) { ; }
	__forceinline FVector3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) { ; }
	__forceinline FVector3(float* f) : x(f[0]), y(f[1]), z(f[2]) { ; }
	__forceinline FVector3(const float* f) : x(f[0]), y(f[1]), z(f[2]) { ; }

	// operator
	__forceinline FVector3 operator+() const { return FVector3(x, y, z); }
	__forceinline FVector3 operator-() const { return FVector3(-x, -y, -z); }
	__forceinline FVector3& operator=(const FVector3& other) { x = other.x; y = other.y; z = other.z; return *this; }

	FVector3& operator=(const MSVector& other);
	FVector3& operator=(const MSVector2& other);

	__forceinline FVector3 operator+(const FVector3& other) const { return FVector3(x + other.x, y + other.y, z + other.z); }
	__forceinline FVector3& operator+=(const FVector3& other) { x += other.x; y += other.y; z += other.z; return *this; }

	__forceinline FVector3 operator-(const FVector3& other) const { return FVector3(x - other.x, y - other.y, z - other.z); }
	__forceinline FVector3& operator-=(const FVector3& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }

	__forceinline FVector3 operator*(const FVector3& other) const { return FVector3(x * other.x, y * other.y, z * other.z); }
	__forceinline FVector3& operator*=(const FVector3& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
	__forceinline FVector3 operator*(const float v) const { return FVector3(x * v, y * v, z * v); }
	__forceinline FVector3& operator*=(const float v) { x *= v; y *= v; z *= v; return *this; }

	__forceinline FVector3 operator/(const FVector3& other) const { return FVector3(x / other.x, y / other.y, z / other.z); }
	__forceinline FVector3& operator/=(const FVector3& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }
	__forceinline FVector3 operator/(const float v) const { float i = (float)1.0 / v; return FVector3(x * i, y * i, z * i); }
	__forceinline FVector3& operator/=(const float v) { float i = (float)1.0 / v; x *= i; y *= i; z *= i; return *this; }

	__forceinline bool operator<=(const FVector3& other) const { return x <= other.x && y <= other.y && z <= other.z; };
	__forceinline bool operator< (const FVector3& other) const { return x < other.x && y < other.y && z < other.z; };
	__forceinline bool operator>=(const FVector3& other) const { return x >= other.x && y >= other.y && z >= other.z; };
	__forceinline bool operator> (const FVector3& other) const { return x > other.x && y > other.y && z > other.z; };
	__forceinline bool operator==(const FVector3& other) const { return IsEqual(other); }
	__forceinline bool operator!=(const FVector3& other) const { return other.x != x || other.y != y || other.z != z; }

	__forceinline friend FVector3 operator*(float f, const class FVector3& v) { return FVector3(f * v.x, f * v.y, f * v.z); }

	// casting
	__forceinline operator float* () { return v; }
	__forceinline operator const float* () const { return (const float*)v; }

	// function
	__forceinline void Set(float x, float y, float z) { FVector3::x = x; FVector3::y = y; FVector3::z = z; }
	__forceinline void Set(const FVector3& p) { FVector3::x = p.x; FVector3::y = p.y; FVector3::z = p.z; }
	
	__forceinline float Length() const { float lenSquare = x * x + y * y + z * z; return (float)sqrt(lenSquare); }
	__forceinline float LengthSq() const { return (x * x + y * y + z * z); }
	__forceinline float ZDistanceTo(const FVector3& tar) const { return tar.z - z; }
	__forceinline float DotProduct(const FVector3& other) const { return x * other.x + y * other.y + z * other.z; }
	__forceinline FVector3 CrossProduct(const FVector3& p) const { return FVector3(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x); }

	inline float DistanceTo(const FVector3& tar) const;
	inline float DistanceToSq(const FVector3& tar) const;
	inline float XYDistanceTo(const FVector3& tar) const;
	inline float XYDistanceToSq(const FVector3& tar) const;

	inline FVector3& Normalize();
	inline FVector3& FastNormalize();
	inline void UnsafeFastNormalize();

	__forceinline void SetLength(float newlength) { Normalize(); *this *= newlength; }
	__forceinline void Invert() { x *= -1.0f; y *= -1.0f; z *= -1.0f; }

	inline FVector3 GetInterpolated(const FVector3& other, float d) const;
	inline void InterpolateTo(const FVector3& other, float d, FVector3& out) const;
	inline float AngleBetween(const FVector3& other) const;
	inline float AngleToXY(const FVector3& other) const;
	inline float GetAngleXY() const;
	inline float FixConvVar(float var, bool isZ = false) const;
	inline void  DoFixes();

	inline bool IsEqual(const FVector3& other, float Tolerance = 0.001f) const;

	static const FVector3 ZERO;
	static const FVector3 AXISX;
	static const FVector3 AXISY;
	static const FVector3 AXISZ;

	union
	{
		float v[3];
		struct
		{
			float x, y, z;
		};
	};

};

inline float FVector3::DistanceTo(const FVector3& tar) const
{
	float x1 = tar.x - x;
	float y1 = tar.y - y;
	float z1 = tar.z - z;

	float lenSquare = x1 * x1 + y1 * y1 + z1 * z1;
	return (float)sqrt(lenSquare);
}

inline float FVector3::DistanceToSq(const FVector3& tar) const
{
	float x1 = tar.x - x;
	float y1 = tar.y - y;
	float z1 = tar.z - z;

	return (x1 * x1 + y1 * y1 + z1 * z1);
}

inline float FVector3::XYDistanceTo(const FVector3& tar) const
{
	float x1 = tar.x - x;
	float y1 = tar.y - y;

	float lenSquare = x1 * x1 + y1 * y1;
	return (float)sqrt(lenSquare);
}

inline float FVector3::XYDistanceToSq(const FVector3& tar) const
{
	float x1 = tar.x - x;
	float y1 = tar.y - y;

	return (x1 * x1 + y1 * y1);
}

inline FVector3& FVector3::Normalize()
{
	float scale = (float)Length();

	if (scale == 0)
		return *this;

	scale = (float)1.0f / scale;
	x *= scale;
	y *= scale;
	z *= scale;
	return *this;
}

inline FVector3& FVector3::FastNormalize()
{
	float fx = LengthSq();
	{	// fast invert-sqrtf code
		float vhalf = 0.5f * fx;
		int i = *(int*)& fx;
		i = 0x5f3759df - (i >> 1);
		fx = *(float*)& i;
		fx = fx * (1.5f - vhalf * fx * fx);
	}

	x *= fx;
	y *= fx;
	z *= fx;

	return *this;
}

//
// MSM: Fast float inverse square root using SSE.
// Accurate to within 1 LSB.
//
inline float appInvSqrt(float F)
{
	const float fThree = 3.0f;
	const float fOneHalf = 0.5f;
	float temp;

	__asm
	{
		movss	xmm1, [F]
		rsqrtss	xmm0, xmm1			// 1/sqrt estimate (12 bits)

		// Newton-Raphson iteration (X1 = 0.5*X0*(3-(Y*X0)*X0))
		movss	xmm3, [fThree]
		movss	xmm2, xmm0
		mulss	xmm0, xmm1			// Y*X0
		mulss	xmm0, xmm2			// Y*X0*X0
		mulss	xmm2, [fOneHalf]		// 0.5*X0
		subss	xmm3, xmm0			// 3-Y*X0*X0
		mulss	xmm3, xmm2			// 0.5*X0*(3-Y*X0*X0)
		movss[temp], xmm3
	}

	return temp;
}

inline void FVector3::UnsafeFastNormalize()
{
	float scale = appInvSqrt(x * x + y * y + z * z);
	x *= scale;
	y *= scale;
	z *= scale;
}

inline FVector3 FVector3::GetInterpolated(const FVector3& other, float d) const
{
	float inv = 1.0f - d;
	return FVector3(other.x * inv + x * d,
		other.y * inv + y * d,
		other.z * inv + z * d);
}

inline void FVector3::InterpolateTo(const FVector3& other, float d, FVector3& out) const
{
	out.x = (other.x - x) * d + x;
	out.y = (other.y - y) * d + y;
	out.z = (other.z - z) * d + z;
}

inline float FVector3::AngleBetween(const FVector3& other) const
{
	float lenProduct = Length() * other.Length();

	// Divide by zero check
	if (lenProduct < 1e-6f)
		lenProduct = 1e-6f;

	float fDot = this->DotProduct(other) / lenProduct;

	if (fDot < -1.0f) fDot = -1.0f;
	if (fDot > 1.0f) fDot = 1.0f;
	return acosf(fDot);
}

inline float FVector3::AngleToXY(const FVector3& other) const
{
	if ((this->x == 0.0f) && (this->y == 0.0f) && (this->z == 0.0f)) return 0;
	if ((other.x == 0.0f) && (other.y == 0.0f) && (other.z == 0.0f)) return 0;

	FVector3 a = *this;
	FVector3 b = other;

	a.z = 0; a.Normalize();
	b.z = 0; b.Normalize();

	float aa = a.GetAngleXY();

	float x = (float)(b.x * cos(aa) + b.y * sin(aa));
	float y = (float)(b.x * (-sin(aa)) + b.y * cos(aa));

	FVector3 ret(x, y, 0);
	return ret.GetAngleXY();
}

inline float FVector3::GetAngleXY() const
{
	if (x >= 1.0f) return 0.0f;
	if (x <= -1.0f) return -3.1415926535f;
	if (y > 0)
		return (float)acos(x);
	else
		return (float)-acos(x);
}

inline float FVector3::FixConvVar(float var, bool isZ) const
{
	int m = ((*((int*)& var))) & (signed int)(0x007FFFFF);
	int tvar = 32767;
	if ((*((int*)& var) & (unsigned int)0x007FFFFF) <= (signed int)0x47FFEFFF)
	{
		if (m >= (signed int)0x38800000)
		{
			unsigned int test = m - (signed int)0x38000000;
			tvar = ((((test >> (signed int)13) & (signed int)1) + test + (signed int)0xFFF) >> (signed int)13) & (signed int)0x7FFF;
		}
		else
		{
			unsigned int test = (*((unsigned long*)& var) & (signed int)0x7FFFFF | (unsigned int)0x800000) >> ((signed int)113 - (m >> (signed int)23));
			tvar = ((((test >> (signed int)13) & (signed int)1) + test + (signed int)0xFFF) >> (signed int)13) & (signed int)0x7FFF;
		}
	}
	return (float)(tvar | ((*((unsigned int*)& var))) & 0x8000);
}

inline void FVector3::DoFixes()
{
	x = FixConvVar(x);
	y = FixConvVar(y);
	z = FixConvVar(z);
}

inline bool FVector3::IsEqual(const FVector3& other, float Tolerance) const
{
	return
		((other.x - x) <= Tolerance) &&
		((other.y - y) <= Tolerance) &&
		((other.z - z) <= Tolerance);
}
