#include "pch.h"
#include "vector3.h"
#include "msvector.h"

FVector3& FVector3::operator=(const MSVector& other)
{
	MSVector other2 = other;
	x = other2.X();
	y = other2.Y();
	z = other2.Z();
	return *this;
}

FVector3& FVector3::operator=(const MSVector2& other)
{
	MSVector2 other2 = other;
	x = other2.X();
	y = other2.Y();
	z = 0.0f;
	return *this;
}
