#include "pch.h"
#include "msvector.h"
#include "vector3.h"

MSVector& MSVector::operator=(const FVector3& other)
{
	//~ @todo
	/*
	m_x = _32To16(other.x);
	m_y = _32To16(other.y);
	m_z = _32To16(other.z);
	*/
	return *this;
}

unsigned int MSVector::floatToHalfI(unsigned int i)
{
	int s = (i >> 16) & 0x00008000;
	int e = ((i >> 23) & 0x000000ff) - (127 - 15);
	int m = i & 0x007fffff;

	if (e <= 0)
	{
		if (e < -10)
		{
			return 0;
		}
		m = (m | 0x00800000) >> (1 - e);

		return s | (m >> 13);
	}
	else if (e == 0xff - (127 - 15))
	{
		if (m == 0) // Inf
		{
			return s | 0x7c00;
		}
		else    // NAN
		{
			m >>= 13;
			return s | 0x7c00 | m | (m == 0);
		}
	}
	else
	{
		if (e > 30) // Overflow
		{
			return s | 0x7c00;
		}

		return s | (e << 10) | (m >> 13);
	}
}

unsigned int MSVector::halfToFloatI(unsigned short var)
{
	int s = (var >> 15) & 0x00000001;
	int e = (var >> 10) & 0x0000001f;
	int m = var & 0x000003ff;

	if (e == 0)
	{
		if (m == 0) // Plus or minus zero
		{
			return s << 31;
		}
		else // Denormalized number -- renormalize it
		{
			while (!(m & 0x00000400))
			{
				m <<= 1;
				e -= 1;
			}

			e += 1;
			m &= ~0x00000400;
		}
	}
	else if (e == 31)
	{
		if (m == 0) // Inf
		{
			return (s << 31) | 0x7f800000;
		}
		else // NaN
		{
			return (s << 31) | 0x7f800000 | (m << 13);
		}
	}

	e = e + (127 - 15);
	m = m << 13;

	return (s << 31) | (e << 23) | m;
}

MSVector2& MSVector2::operator=(const FVector3& other)
{
	//~ @todo
	/*
	m_x = _32To16(other.x);
	m_y = _32To16(other.y);
	*/
	return *this;
}
