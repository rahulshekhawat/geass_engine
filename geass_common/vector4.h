#pragma once

#include "pch.h"
#include "gc_lib.h"
#include "vector3.h"

class GEASSCOMMON_API FVector4
{
public:

	__forceinline FVector4() { ; }
	__forceinline FVector4(const FVector3& v3, float ww) : x(v3.x), y(v3.y), z(v3.z), w(ww) { ; }
	__forceinline FVector4(float xx, float yy, float zz, float ww) : x(xx), y(yy), z(zz), w(ww) { ; }
	__forceinline FVector4(const float* f) { x = f[0]; y = f[1]; z = f[2]; w = f[3]; }
	__forceinline explicit FVector4(unsigned long dw)
	{
		const float f = 1.0f / 255.0f;
		x = f * (float)(unsigned char)(dw >> 16);
		y = f * (float)(unsigned char)(dw >> 8);
		z = f * (float)(unsigned char)(dw >> 0);
		w = f * (float)(unsigned char)(dw >> 24);
	}

	__forceinline void Set(float xx, float yy, float zz, float ww) { x = xx; y = yy; z = zz; w = ww; }
	__forceinline FVector4 operator*(const float v) const { return FVector4(x * v, y * v, z * v, w * v); }
	__forceinline FVector4& operator*=(const float v) { x *= v; y *= v; z *= v; w *= v; return *this; }
	__forceinline FVector4 operator/(const float v) const { float i = (float)1.0 / v; return FVector4(x * i, y * i, z * i, w * i); }
	__forceinline FVector4& operator/=(const float v) { float i = (float)1.0 / v; x *= i; y *= i; z *= i; w *= i; return *this; }
	__forceinline FVector4& operator += (const FVector4& v) { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
	__forceinline FVector4 operator+(const FVector4& v) const { return FVector4(x + v.x, y + v.y, z + v.z, w + v.w); }
	__forceinline FVector4& operator -= (const FVector4& v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
	__forceinline FVector4 operator - (const FVector4& v) const { return FVector4(x - v.x, y - v.y, z - v.z, w - v.w); }
	__forceinline bool operator!=(const FVector4& other) const { return other.x != x || other.y != y || other.z != z || other.w != w; }

	/** Returns the length of passed in vector */
	__forceinline float Length(const FVector4& v) { return v.Length(); }

	/** Returns the length of this vector  */
	inline float Length() const 
	{
		float lenSquared = x * x + y * y + z * z + w * w;
		return (float)sqrt(lenSquared);
	}

	/** Dot product of two vectors */
	inline float DotProduct(const FVector4& p) 
	{ 
		return x * p.x + y * p.y + z * p.z + w * p.w;
	}

	inline FVector4 CrossProduct(const FVector4& p) const
	{
		return FVector4(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x, p.w * w);
	}

	inline FVector4 GetInterpolated(const FVector4& other, float d) const;
	inline FVector4 Multiply(const FVector4& other) const;

	//~ Casting
	__forceinline operator float* () { return v; }
	__forceinline operator const float* () const { return (const float*)v; }

	inline operator unsigned long() const;

	static const FVector4 ZERO;

	union
	{
		struct
		{
			float r, g, b, a;
		};
		struct
		{
			float x, y, z, w;
		};
		float v[4];
	};
};

inline FVector4 FVector4::GetInterpolated(const FVector4& other, float d) const
{
	float inv = 1.0f - d;
	return FVector4(other.x * inv + x * d,
		other.y * inv + y * d,
		other.z * inv + z * d,
		other.w * inv + w * d);
}

inline FVector4 FVector4::Multiply(const FVector4& other) const
{
	return FVector4(other.x * x, other.y * y, other.z * z, other.w * w);
}

inline FVector4::operator unsigned long() const
{
	unsigned long dwR = x >= 1.0f ? 0xff : x <= 0.0f ? 0x00 : (unsigned long)(x * 255.0f + 0.5f);
	unsigned long dwG = y >= 1.0f ? 0xff : y <= 0.0f ? 0x00 : (unsigned long)(y * 255.0f + 0.5f);
	unsigned long dwB = z >= 1.0f ? 0xff : z <= 0.0f ? 0x00 : (unsigned long)(z * 255.0f + 0.5f);
	unsigned long dwA = w >= 1.0f ? 0xff : w <= 0.0f ? 0x00 : (unsigned long)(w * 255.0f + 0.5f);

	return (dwA << 24) | (dwR << 16) | (dwG << 8) | dwB;
}
