#pragma once

#include "pch.h"
#include "gc_lib.h"

class FVector3;


/**
 * Vector with floating-point compression. Size = 6 bytes.
 * Since error rate is high, use it only for normal vectors
 */

class GEASSCOMMON_API MSVector
{
	friend class MSVector2;

public:

	__forceinline MSVector() { ; }
	__forceinline MSVector(const MSVector& other) : m_x(other.m_x), m_y(other.m_y), m_z(other.m_z) { ; }
	__forceinline MSVector(float x, float y, float z);
	__forceinline MSVector(float* f);
	__forceinline MSVector(const float* f);

	__forceinline void SetX(float x) { m_x = _32To16(x); }
	__forceinline void SetY(float y) { m_y = _32To16(y); }
	__forceinline void SetZ(float z) { m_z = _32To16(z); }
	__forceinline float X() { return halfToFloat(m_x); }
	__forceinline float Y() { return halfToFloat(m_y); }
	__forceinline float Z() { return halfToFloat(m_z); }

	__forceinline bool IsEqual(const MSVector& other) const;

	__forceinline MSVector& operator=(const MSVector& other) { m_x = other.m_x; m_y = other.m_y; m_z = other.m_z; return *this; }
	__forceinline bool operator==(const MSVector& other) const { return IsEqual(other); }

	MSVector& operator=(const FVector3& other);

private:

	inline unsigned short _32To16(float t);
	inline unsigned short floatToHalf(float i);
	inline float halfToFloat(unsigned short var);

	static unsigned int floatToHalfI(unsigned int i);
	static unsigned int halfToFloatI(unsigned short var);

	union
	{
		struct
		{
			unsigned short m_x, m_y, m_z;
		};
		unsigned short m_v[3];
	};
};


class GEASSCOMMON_API MSVector2
{

public:

	__forceinline MSVector2() { ; }
	__forceinline MSVector2(const MSVector& other) : m_x(other.m_x), m_y(other.m_y) { ; }
	__forceinline MSVector2(float x, float y);
	__forceinline MSVector2(float* f);
	__forceinline MSVector2(const float* f);

	__forceinline void SetX(float x) { m_x = _32To16(x); }
	__forceinline void SetY(float y) { m_y = _32To16(y); }
	__forceinline float X() { return _16To32(m_x); }
	__forceinline float Y() { return _16To32(m_y); }

	__forceinline bool IsEqual(const MSVector2& other) const;

	__forceinline MSVector2& operator=(const MSVector2& other) { m_x = other.m_x; m_y = other.m_y; return *this; }
	__forceinline bool operator==(const MSVector2& other) const { return IsEqual(other); }

	MSVector2& operator=(const FVector3& other);

private:

	inline unsigned short _32To16(float t);
	inline float _16To32(unsigned short t);

	union
	{
		struct
		{
			unsigned short m_x, m_y;
		};
		unsigned short m_v[2];
	};
};


__forceinline MSVector::MSVector(float x, float y, float z)
{
	m_x = _32To16(x);
	m_y = _32To16(y);
	m_z = _32To16(z);
}

__forceinline MSVector::MSVector(float* f)
{
	m_x = _32To16(f[0]);
	m_y = _32To16(f[1]);
	m_z = _32To16(f[2]);
}

__forceinline MSVector::MSVector(const float* f)
{
	m_x = _32To16(f[0]);
	m_y = _32To16(f[1]);
	m_z = _32To16(f[2]);
}

__forceinline bool MSVector::IsEqual(const MSVector& other) const
{
	return (m_x == other.m_x && m_y == other.m_y && m_z == other.m_z);
}

inline unsigned short MSVector::_32To16(float t)
{
	int s = ((*((unsigned long*)& t) & 0x80000000) >> 31);
	int e = ((*((unsigned long*)& t) & 0x7F800000) >> 23) - 127;
	int m = (*((unsigned long*)& t) & 0x007FFFFF);

	if (e < -7) return 0;

	return (unsigned short)((s << 15) | ((e + 7) << 11) | (m >> (23 - 11)));
}

inline unsigned short MSVector::floatToHalf(float i)
{
	union { float f; unsigned int i; } v;
	v.f = i;
	return floatToHalfI(v.i);
}

inline float MSVector::halfToFloat(unsigned short var)
{
	union { float f; unsigned int i; } v;
	v.i = halfToFloatI(var);
	return v.f;
}

__forceinline MSVector2::MSVector2(float x, float y)
{
	m_x = _32To16(x);
	m_y = _32To16(y);
}

__forceinline MSVector2::MSVector2(float* f)
{
	m_x = _32To16(f[0]);
	m_y = _32To16(f[1]);
}

__forceinline MSVector2::MSVector2(const float* f)
{
	m_x = _32To16(f[0]);
	m_y = _32To16(f[1]);
}

__forceinline bool MSVector2::IsEqual(const MSVector2& other) const
{
	return (m_x == other.m_x && m_y == other.m_y);
}

inline unsigned short MSVector2::_32To16(float t)
{
	int s = ((*((unsigned long*)& t) & 0x80000000) >> 31);
	int e = ((*((unsigned long*)& t) & 0x7F800000) >> 23) - 127;
	int m = (*((unsigned long*)& t) & 0x007FFFFF);

	if (e < -7) return 0;

	return (unsigned short)((s << 15) | ((e + 7) << 11) | (m >> (23 - 11)));
}

inline float MSVector2::_16To32(unsigned short t)
{
	int s = ((t & 0x8000) >> 15);
	int e = ((t & 0x7800) >> 11) - 7;
	int m = (t & 0x007FF);

	if (t == 0) return 0.0f;

	unsigned long f = (s << 31) | ((e + 127) << 23) | (m << (23 - 11));
	return *((float*)& f);
}
