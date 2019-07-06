#pragma once

#include "pch.h"
#include "glib.h"
#include "vector3.h"
#include "vector4.h"

#include <assert.h>


class GEASSCOMMON_API FMatrix
{
public:

	__forceinline FMatrix() { ; }
	__forceinline FMatrix(const float* f);
	__forceinline FMatrix(const float(*f)[4]);
	__forceinline FMatrix(
		float f11, float f12, float f13, float f14,
		float f21, float f22, float f23, float f24,
		float f31, float f32, float f33, float f34,
		float f41, float f42, float f43, float f44);

	inline FMatrix& operator=(const FMatrix& other);
	inline bool operator==(const FMatrix& other) const;
	inline bool operator!=(const FMatrix& other) const;
	inline FMatrix& operator*=(const FMatrix& other);
	inline FMatrix operator*(const FMatrix& other) const;
	inline FMatrix operator*(float f) const;
	inline FMatrix operator-(const FMatrix& other) const;	// 090716, OZ
	inline FMatrix operator+(const FMatrix& other) const;	// 090716, OZ

	// casting
	__forceinline operator float* () { return m; }
	__forceinline operator const float* () const { return (const float*)m; }

	// transform, mvector * mmatrix �� ��ü����.
	inline friend FVector3 operator*(const FVector3& v, const FMatrix& tm);
	inline friend FVector4 operator*(const FVector4& v, const FMatrix& tm);

	inline void TransformVect(FVector3& vect) const;
	inline void TransformVectHomogeneous(FVector3& vect) const;
	inline void TransformVect(const FVector3& in, FVector3& out) const;
	inline void TransformVect(const FVector3& in, FVector4& out) const;
	inline void TransformNormal(FVector3& vect) const;
	inline void TransformNormal(const FVector3& in, FVector3& out) const;
	//~ @todo
	// inline void TransformPlane(const MPlane& in, MPlane& out) const;

	inline void MultiplyTo(const FMatrix& other, FMatrix& out) const; // out = this * other;

	inline void MakeZero();
	inline void MakeIdentity();

	inline void SetTranslation(const FVector3& trans);
	inline void SetInverseTranslation(const FVector3& trans);
	inline FVector3 GetTranslation() const;
	inline void SetRotationRadians(const FVector3& rotation);
	inline void SetRotationDegrees(const FVector3& rotation);
	inline void SetScale(const FVector3& scale);
	inline void SetScale(float s);
	inline void SetRotationX(float fRadian);
	inline void SetRotationY(float fRadian);
	inline void SetRotationZ(float fRadian);

	inline void SetRotationMatrix(float x, float y, float z) { SetRotationMatrix(FVector3(x, y, z)); }
	inline void SetRotationMatrix(const FVector3& rotation);// ���� : ����
	inline void SetTranslationMatrix(float x, float y, float z) { SetTranslationMatrix(FVector3(x, y, z)); }
	inline void SetTranslationMatrix(const FVector3& trans);
	inline void SetScaleMatrix(float x, float y, float z) { SetScaleMatrix(FVector3(x, y, z)); }
	inline void SetScaleMatrix(const FVector3& scale);
	inline void SetProjectionMatrixRH(float w, float h, float zNear, float zFar);
	inline void SetProjectionMatrixLH(float w, float h, float zNear, float zFar);
	inline void SetProjectionMatrixFovRH(float fFOVy, float fAspectRatio, float zNear, float zFar);
	inline void SetProjectionMatrixFovLH(float fFOVy, float fAspectRatio, float zNear, float zFar);
	inline void SetLookAtMatrixLH(const FVector3& position, const FVector3& target, const FVector3& upVector);
	inline void SetLookAtMatrixRH(const FVector3& position, const FVector3& target, const FVector3& upVector);
	inline void SetOrthoLH(float w, float h, float zn, float zf);
	inline void SetOrthoRH(float w, float h, float zn, float zf);
	inline void SetOrthoOffCenterRH(float l, float r, float b, float t, float zn, float zf);
	inline void SetOrthoOffCenterLH(float l, float r, float b, float t, float zn, float zf);

	inline void SetRotationMatrixAxis(const FVector3& axis, float radian);
	inline void SetRotationYawPitchRoll(float yaw, float pitch, float roll);	// �׽�Ʈ ���� �ʾ���.
	inline void SetLocalMatrix(const FVector3& position, const FVector3& dir, const FVector3& up);
	inline void SetLocalMatrix(const FVector3& position, const FVector3& dir, const FVector3& up, const FVector3& right);

	inline void SetScreenSpaceMatrix(DWORD dwScreenWidth, DWORD dwScreenHeight);

	inline bool GetInverse(FMatrix* pOut, float* fDet) const;
	inline FMatrix GetTranspose() const;

	//~ @todo
	// bool Decompose(FVector3& vecScale, FVector3& vecTranslation, MQuat& quatRotation) const;
	// bool Decompose(FVector3& vecScale, FVector4& vecTranslation, MQuat& quatRotation) const;
	// bool Decompose(FVector3& vecTranslation, MQuat& quatRotation) const;

	inline void ExtractScale(FVector3& vecScale) const;

	static const FMatrix IDENTITY;

	union
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};

		float _m[4][4];
		float m[16];
	};
};

__forceinline FMatrix::FMatrix(const float* f)
{
	memcpy_s(&_11, sizeof(float) * 4 * 4, f, sizeof(float) * 4 * 4);
}

inline FMatrix::FMatrix(const float(*f)[4])
{
	for (int i = 0; i < 4; i++)
		memcpy_s(&_11 + 4 * i, sizeof(float) * 4, f[i], sizeof(float) * 4);
}

inline FMatrix::FMatrix(
	float f11, float f12, float f13, float f14,
	float f21, float f22, float f23, float f24,
	float f31, float f32, float f33, float f34,
	float f41, float f42, float f43, float f44)
{
	_11 = f11; _12 = f12; _13 = f13; _14 = f14;
	_21 = f21; _22 = f22; _23 = f23; _24 = f24;
	_31 = f31; _32 = f32; _33 = f33; _34 = f34;
	_41 = f41; _42 = f42; _43 = f43; _44 = f44;
}

inline FMatrix& FMatrix::operator=(const FMatrix& other)
{
	__asm
	{
		mov esi, other;
		mov edi, this;
		movdqu xmm0, xmmword ptr[esi];
		movdqu xmm1, xmmword ptr[esi + 0x10];
		movdqu xmm2, xmmword ptr[esi + 0x20];
		movdqu xmm3, xmmword ptr[esi + 0x30];

		movdqu xmmword ptr[edi], xmm0;
		movdqu xmmword ptr[edi + 0x10], xmm1;
		movdqu xmmword ptr[edi + 0x20], xmm2;
		movdqu xmmword ptr[edi + 0x30], xmm3;
	}
	return *this;
}

inline bool FMatrix::operator==(const FMatrix& other) const
{
	for (int i = 0; i < 16; i++)
	{
		if (m[i] != other.m[i]) return false;
	}
	return true;
}

inline bool FMatrix::operator!=(const FMatrix& other) const
{
	return !(*this == other);
}

inline FMatrix& FMatrix::operator*=(const FMatrix& other)
{
	FMatrix ResultMatrix;
	MultiplyTo(other, ResultMatrix);
	memcpy(&m, &ResultMatrix.m, sizeof(float) * 16);
	return *this;
}

inline FMatrix FMatrix::operator*(const FMatrix& other) const
{
	FMatrix ResultMatrix;
	MultiplyTo(other, ResultMatrix);
	return ResultMatrix;
}

inline FMatrix FMatrix::operator*(float f) const
{
	FMatrix mat;
	for (int i = 0; i < 16; i++)
		mat[i] = m[i] * f;
	return mat;
}

inline FMatrix FMatrix::operator-(const FMatrix& mat) const
{
	return FMatrix(
		_11 - mat._11, _12 - mat._12, _13 - mat._13, _14 - mat._14,
		_21 - mat._21, _22 - mat._22, _23 - mat._23, _24 - mat._24,
		_31 - mat._31, _32 - mat._32, _33 - mat._33, _34 - mat._34,
		_41 - mat._41, _42 - mat._42, _43 - mat._43, _44 - mat._44);
}

inline FMatrix FMatrix::operator+(const FMatrix& mat) const
{
	return FMatrix(
		_11 + mat._11, _12 + mat._12, _13 + mat._13, _14 + mat._14,
		_21 + mat._21, _22 + mat._22, _23 + mat._23, _24 + mat._24,
		_31 + mat._31, _32 + mat._32, _33 + mat._33, _34 + mat._34,
		_41 + mat._41, _42 + mat._42, _43 + mat._43, _44 + mat._44);
}

inline FVector3 operator*(const FVector3& v, const FMatrix& tm)
{
	FVector3 ret;
	tm.TransformVect(v, ret);
	return ret;
}

inline FVector4 operator*(const FVector4& v, const FMatrix& tm)
{
	FVector4 vec4;
	vec4.x = v.x * tm._11 + v.y * tm._21 + v.z * tm._31 + v.w * tm._41;
	vec4.y = v.x * tm._12 + v.y * tm._22 + v.z * tm._32 + v.w * tm._42;
	vec4.z = v.x * tm._13 + v.y * tm._23 + v.z * tm._33 + v.w * tm._43;
	vec4.w = v.x * tm._14 + v.y * tm._24 + v.z * tm._34 + v.w * tm._44;

	return vec4;
}

inline void FMatrix::TransformVect(FVector3& vect) const
{
	float vector[3];

	vector[0] = vect.x * _11 + vect.y * _21 + vect.z * _31 + _41;
	vector[1] = vect.x * _12 + vect.y * _22 + vect.z * _32 + _42;
	vector[2] = vect.x * _13 + vect.y * _23 + vect.z * _33 + _43;

	vect.x = vector[0];
	vect.y = vector[1];
	vect.z = vector[2];
}

inline void FMatrix::TransformVectHomogeneous(FVector3& vect) const
{
	float vector[3];

	vector[0] = vect.x * _11 + vect.y * _21 + vect.z * _31 + _41;
	vector[1] = vect.x * _12 + vect.y * _22 + vect.z * _32 + _42;
	vector[2] = vect.x * _13 + vect.y * _23 + vect.z * _33 + _43;
	float invw = 1.f / (vect.x * _14 + vect.y * _24 + vect.z * _34 + _44);

	vect.x = vector[0] * invw;
	vect.y = vector[1] * invw;
	vect.z = vector[2] * invw;
}

inline void FMatrix::TransformVect(const FVector3& in, FVector3& out) const
{
	assert(&in != &out); // ÀÌ°æ¿ì ¿¡·¯³³´Ï´Ù.
	out.x = in.x * _11 + in.y * _21 + in.z * _31 + _41;
	out.y = in.x * _12 + in.y * _22 + in.z * _32 + _42;
	out.z = in.x * _13 + in.y * _23 + in.z * _33 + _43;
}

inline void FMatrix::TransformVect(const FVector3& in, FVector4& out) const
{
	out.x = in.x * _11 + in.y * _21 + in.z * _31 + _41;
	out.y = in.x * _12 + in.y * _22 + in.z * _32 + _42;
	out.z = in.x * _13 + in.y * _23 + in.z * _33 + _43;
	out.w = in.x * _14 + in.y * _24 + in.z * _34 + _44;
}

inline void FMatrix::TransformNormal(FVector3& vect) const
{
	float vector[3];

	vector[0] = vect.x * _11 + vect.y * _21 + vect.z * _31;
	vector[1] = vect.x * _12 + vect.y * _22 + vect.z * _32;
	vector[2] = vect.x * _13 + vect.y * _23 + vect.z * _33;

	vect.x = vector[0];
	vect.y = vector[1];
	vect.z = vector[2];
}

inline void FMatrix::TransformNormal(const FVector3& in, FVector3& out) const
{
	out.x = in.x * _11 + in.y * _21 + in.z * _31;
	out.y = in.x * _12 + in.y * _22 + in.z * _32;
	out.z = in.x * _13 + in.y * _23 + in.z * _33;
}

inline void FMatrix::MultiplyTo(const FMatrix& other, FMatrix& mout) const // out = this * other;
{
	__asm
	{
		mov		   eax, mout	   	   // dst
		mov		   ecx, other	  	   // src1
		mov		   edx, this	  	   // src2

		movups	 xmm0, xmmword ptr[ecx]	  	   // xmm0 = src1[00, 01, 02, 03]
		movups	 xmm1, xmmword ptr[ecx + 0x10]	   // xmm1 = src1[04, 05, 06, 07]
		movups	 xmm2, xmmword ptr[ecx + 0x20]	   // xmm2 = src1[08, 09, 10, 11]
		movups	 xmm3, xmmword ptr[ecx + 0x30]	   // xmm3 = src1[12, 13, 14, 15]

		movss	  xmm7, dword ptr[edx]		   // xmm7 = src2[00, xx, xx, xx]
		movss	  xmm4, dword ptr[edx + 0x4]	  // xmm4 = src2[01, xx, xx, xx]
		movss	  xmm5, dword ptr[edx + 0x8]	  // xmm5 = src2[02, xx, xx, xx]
		movss	  xmm6, dword ptr[edx + 0xc]	  	   // xmm6 = src2[03, xx, xx, xx]

		shufps	 xmm7, xmm7, 0x0	  	   // xmm7 = src2[00, 00, 00, 00]
		shufps	 xmm4, xmm4, 0x0	  	   // xmm4 = src2[01, 01, 01, 01]
		shufps	 xmm5, xmm5, 0x0	  	   // xmm5 = src2[02, 02, 02, 02]
		shufps	 xmm6, xmm6, 0x0	  	   // xmm6 = src2[03, 03, 03, 03]

		mulps	  xmm7, xmm0	   	   	   // xmm7 *= xmm0
		mulps	  xmm4, xmm1	   	   	   // xmm4 *= xmm1
		mulps	  xmm5, xmm2	   	   	   // xmm5 *= xmm2
		mulps	  xmm6, xmm3	   	   	   // xmm6 *= xmm3

		addps	  xmm7, xmm4	   	   	   // xmm7 += xmm4
		addps	  xmm7, xmm5	   	   	   // xmm7 += xmm5
		addps	  xmm7, xmm6	   	   	   // xmm7 += xmm6

		movups	 xmmword ptr[eax], xmm7		   // eax = xmm7

		movss	  xmm7, dword ptr[edx + 0x10]	 // xmm7 = src2[04, xx, xx, xx]
		movss	  xmm4, dword ptr[edx + 0x14]	 // xmm4 = src2[05, xx, xx, xx]
		movss	  xmm5, dword ptr[edx + 0x18]	 // xmm5 = src2[06, xx, xx, xx]
		movss	  xmm6, dword ptr[edx + 0x1c]	 // xmm6 = src2[07, xx, xx, xx]

		shufps	 xmm7, xmm7, 0x0	  	   // xmm7 = src2[04, 04, 04, 04]
		shufps	 xmm4, xmm4, 0x0	  	   // xmm4 = src2[05, 05, 05, 05]
		shufps	 xmm5, xmm5, 0x0	  	   // xmm5 = src2[06, 06, 06, 06]
		shufps	 xmm6, xmm6, 0x0	  	   // xmm6 = src2[07, 07, 07, 07]

		mulps	  xmm7, xmm0	   	   	   // xmm7 *= xmm0
		mulps	  xmm4, xmm1	   	   	   // xmm4 *= xmm1
		mulps	  xmm5, xmm2	   	   	   // xmm5 *= xmm2
		mulps	  xmm6, xmm3	   	   	   // xmm6 *= xmm3

		addps	  xmm7, xmm4	   	   	   // xmm7 += xmm4
		addps	  xmm7, xmm5	   	   	   // xmm7 += xmm5
		addps	  xmm7, xmm6	   	   	   // xmm7 += xmm6

		movups	 xmmword ptr[eax + 0x10], xmm7	 // eax = xmm7

		movss	  xmm7, dword ptr[edx + 0x20]	 // xmm7 = src2[08, xx, xx, xx]
		movss	  xmm4, dword ptr[edx + 0x24]	 // xmm4 = src2[09, xx, xx, xx]
		movss	  xmm5, dword ptr[edx + 0x28]	 // xmm5 = src2[10, xx, xx, xx]
		movss	  xmm6, dword ptr[edx + 0x2c]	 // xmm6 = src2[11, xx, xx, xx]

		shufps	 xmm7, xmm7, 0x0	  	   // xmm7 = src2[08, 08, 08, 08]
		shufps	 xmm4, xmm4, 0x0	  	   // xmm4 = src2[09, 09, 09, 09]
		shufps	 xmm5, xmm5, 0x0	  	   // xmm5 = src2[10, 10, 10, 10]
		shufps	 xmm6, xmm6, 0x0	  	   // xmm6 = src2[11, 11, 11, 11]

		mulps	  xmm7, xmm0	   	   	   // xmm7 *= xmm0
		mulps	  xmm4, xmm1	   	   	   // xmm4 *= xmm1
		mulps	  xmm5, xmm2	   	   	   // xmm5 *= xmm2
		mulps	  xmm6, xmm3	   	   	   // xmm6 *= xmm3

		addps	  xmm7, xmm4	   	   	   // xmm7 += xmm4
		addps	  xmm7, xmm5	   	   	   // xmm7 += xmm5
		addps	  xmm7, xmm6	   	   	   // xmm7 += xmm6

		movups	 xmmword ptr[eax + 0x20], xmm7	 // eax = xmm7

		movss	  xmm7, dword ptr[edx + 0x30]	 // xmm7 = src2[12, xx, xx, xx]
		movss	  xmm4, dword ptr[edx + 0x34]	 // xmm4 = src2[13, xx, xx, xx]
		movss	  xmm5, dword ptr[edx + 0x38]	 // xmm5 = src2[14, xx, xx, xx]
		movss	  xmm6, dword ptr[edx + 0x3c]	 // xmm6 = src2[15, xx, xx, xx]

		shufps	 xmm7, xmm7, 0x0	  	   // xmm7 = src2[12, 12, 12, 12]
		shufps	 xmm4, xmm4, 0x0	  	   // xmm4 = src2[13, 13, 13, 13]
		shufps	 xmm5, xmm5, 0x0	  	   // xmm5 = src2[14, 14, 14, 14]
		shufps	 xmm6, xmm6, 0x0	  	   // xmm6 = src2[15, 15, 15, 15]

		mulps	  xmm7, xmm0	   	   	   // xmm7 *= xmm0
		mulps	  xmm4, xmm1	   	   	   // xmm4 *= xmm1
		mulps	  xmm5, xmm2	   	   	   // xmm5 *= xmm2
		mulps	  xmm6, xmm3	   	   	   // xmm6 *= xmm3

		addps	  xmm7, xmm4	   	   	   // xmm7 += xmm4
		addps	  xmm7, xmm5	   	   	   // xmm7 += xmm5
		addps	  xmm7, xmm6	   	   	   // xmm7 += xmm6

		movups	 xmmword ptr[eax + 0x30], xmm7	 // eax = xmm7
	}
}

inline void FMatrix::MakeZero()
{
	memset(&m, 0, sizeof(float) * 16);
}

inline void FMatrix::MakeIdentity()
{
	MakeZero();
	m[0] = m[5] = m[10] = m[15] = 1.0f;
}

inline void FMatrix::SetTranslation(const FVector3& trans)
{
	_41 = trans.x;
	_42 = trans.y;
	_43 = trans.z;
}

inline void FMatrix::SetInverseTranslation(const FVector3& trans)
{
	_41 = -trans.x;
	_42 = -trans.y;
	_43 = -trans.z;
}

inline FVector3 FMatrix::GetTranslation() const
{
	return FVector3(_41, _42, _43);
}

inline void FMatrix::SetRotationRadians(const FVector3& rotation)
{
	double cr = cos(rotation.x);
	double sr = sin(rotation.x);
	double cp = cos(rotation.y);
	double sp = sin(rotation.y);
	double cy = cos(rotation.z);
	double sy = sin(rotation.z);

	m[0] = float(cp * cy);
	m[1] = float(cp * sy);
	m[2] = float(-sp);

	double srsp = sr * sp;
	double crsp = cr * sp;

	m[4] = (float)(srsp * cy - cr * sy);
	m[5] = (float)(srsp * sy + cr * cy);
	m[6] = (float)(sr * cp);

	m[8] = (float)(crsp * cy + sr * sy);
	m[9] = (float)(crsp * sy - sr * cy);
	m[10] = (float)(cr * cp);
}

inline void FMatrix::SetRotationDegrees(const FVector3& rotation)
{
	SetRotationRadians(rotation * (float)3.1415926535897932384626433832795 / 180.0);
}

inline void FMatrix::SetScale(const FVector3& scale)
{
	_11 = scale.x;
	_22 = scale.y;
	_33 = scale.z;
}

inline void FMatrix::SetScale(float s)
{
	_11 = _22 = _33 = s;
}

inline void FMatrix::SetRotationX(float fRadian)
{
	float c = (float)cos(fRadian);
	float s = (float)sin(fRadian);

	MakeIdentity();
	_22 = c;	_23 = s;
	_32 = -s;	_33 = c;
}

inline void FMatrix::SetRotationY(float fRadian)
{
	float c = (float)cos(fRadian);
	float s = (float)sin(fRadian);

	MakeIdentity();
	_11 = c;	_13 = -s;
	_31 = s;	_33 = c;
}

inline void FMatrix::SetRotationZ(float fRadian)
{
	float c = (float)cos(fRadian);
	float s = (float)sin(fRadian);

	MakeIdentity();
	_11 = c;	_12 = s;
	_21 = -s;	_22 = c;
}

inline void FMatrix::SetRotationMatrix(const FVector3& rotation)
{
	MakeIdentity();
	SetRotationRadians(rotation);
}

inline void FMatrix::SetTranslationMatrix(const FVector3& trans)
{
	MakeIdentity();
	SetTranslation(trans);
}

inline void FMatrix::SetScaleMatrix(const FVector3& scale)
{
	MakeIdentity();
	SetScale(scale);
}

inline void FMatrix::SetProjectionMatrixRH(float w, float h, float zNear, float zFar)
{
	_11 = 2 * zNear / w;
	_12 = 0;
	_13 = 0;
	_14 = 0;

	_21 = 0;
	_22 = 2 * zNear / h;
	_23 = 0;
	_24 = 0;

	_31 = 0;
	_32 = 0;
	_33 = zFar / (zNear - zFar);
	_34 = -1;

	_41 = 0;
	_42 = 0;
	_43 = zNear * zFar / (zNear - zFar);
	_44 = 0;
}

inline void FMatrix::SetProjectionMatrixLH(float w, float h, float zNear, float zFar)
{
	_11 = 2 * zNear / w;
	_12 = 0;
	_13 = 0;
	_14 = 0;

	_21 = 0;
	_22 = 2 * zNear / h;
	_23 = 0;
	_24 = 0;

	_31 = 0;
	_32 = 0;
	_33 = zFar / (zFar - zNear);
	_34 = 1;

	_41 = 0;
	_42 = 0;
	_43 = zNear * zFar / (zNear - zFar);
	_44 = 0;
}

inline void FMatrix::SetProjectionMatrixFovRH(float fFOVy, float fAspectRatio, float zNear, float zFar)
{
	float yScale = 1 / (float)tan(fFOVy / 2);
	float xScale = yScale / fAspectRatio;

	_11 = xScale;
	_12 = 0;
	_13 = 0;
	_14 = 0;

	_21 = 0;
	_22 = yScale;
	_23 = 0;
	_24 = 0;

	_31 = 0;
	_32 = 0;
	_33 = zFar / (zNear - zFar);
	_34 = -1;

	_41 = 0;
	_42 = 0;
	_43 = zNear * zFar / (zNear - zFar);
	_44 = 0;
}

inline void FMatrix::SetProjectionMatrixFovLH(float fFOVy, float fAspectRatio, float zNear, float zFar)
{
	float yScale = 1 / (float)tan(fFOVy / 2);
	float xScale = yScale / fAspectRatio;

	_11 = xScale;
	_12 = 0;
	_13 = 0;
	_14 = 0;

	_21 = 0;
	_22 = yScale;
	_23 = 0;
	_24 = 0;

	_31 = 0;
	_32 = 0;
	_33 = zFar / (zFar - zNear);
	_34 = 1;

	_41 = 0;
	_42 = 0;
	_43 = zNear * zFar / (zNear - zFar);
	_44 = 0;
}

inline void FMatrix::SetLookAtMatrixLH(const FVector3& eye, const FVector3& at, const FVector3& up)
{
	FVector3 zaxis = at - eye;
	zaxis.Normalize();

	FVector3 xaxis = up.CrossProduct(zaxis);
	xaxis.Normalize();

	FVector3 yaxis = zaxis.CrossProduct(xaxis);
	yaxis.Normalize();

	_11 = xaxis.x;
	_12 = yaxis.x;
	_13 = zaxis.x;
	_14 = 0;

	_21 = xaxis.y;
	_22 = yaxis.y;
	_23 = zaxis.y;
	_24 = 0;

	_31 = xaxis.z;
	_32 = yaxis.z;
	_33 = zaxis.z;
	_34 = 0;

	_41 = -xaxis.DotProduct(eye);
	_42 = -yaxis.DotProduct(eye);
	_43 = -zaxis.DotProduct(eye);
	_44 = 1.0f;
}

inline void FMatrix::SetLookAtMatrixRH(const FVector3& eye, const FVector3& at, const FVector3& up)
{
	FVector3 zaxis = eye - at;
	zaxis.Normalize();

	FVector3 xaxis = up.CrossProduct(zaxis);
	xaxis.Normalize();

	FVector3 yaxis = zaxis.CrossProduct(xaxis);
	yaxis.Normalize();

	_11 = xaxis.x;
	_12 = yaxis.x;
	_13 = zaxis.x;
	_14 = 0;

	_21 = xaxis.y;
	_22 = yaxis.y;
	_23 = zaxis.y;
	_24 = 0;

	_31 = xaxis.z;
	_32 = yaxis.z;
	_33 = zaxis.z;
	_34 = 0;

	_41 = -xaxis.DotProduct(eye);
	_42 = -yaxis.DotProduct(eye);
	_43 = -zaxis.DotProduct(eye);
	_44 = 1.0f;
}

inline void FMatrix::SetOrthoLH(float w, float h, float zn, float zf)
{
	_11 = 2.0f / (w);	_12 = 0.0f;		_13 = 0.0f;			_14 = 0.0f;
	_21 = 0.0f;		_22 = 2.0f / (h);	_23 = 0.0f;			_24 = 0.0f;
	_31 = 0.0f;		_32 = 0.0f;		_33 = 1.0f / (zf - zn);	_34 = 0.0f;
	_41 = 0.0f;		_42 = 0.0f;		_43 = zn / (zn - zf);	_44 = 1.0f;

	return;
}

inline void FMatrix::SetOrthoRH(float w, float h, float zn, float zf)
{
	_11 = 2.0f / (w);	_12 = 0.0f;		_13 = 0.0f;			_14 = 0.0f;
	_21 = 0.0f;		_22 = 2.0f / (h);	_23 = 0.0f;			_24 = 0.0f;
	_31 = 0.0f;		_32 = 0.0f;		_33 = 1.0f / (zn - zf);	_34 = 0.0f;
	_41 = 0.0f;		_42 = 0.0f;		_43 = zn / (zn - zf);	_44 = 1.0f;

	return;
}

inline void FMatrix::SetOrthoOffCenterRH(float l, float r, float b, float t, float zn, float zf)
{
	_11 = 2.0f / (r - l);	_12 = 0.0f;	_13 = 0.0f;	_14 = 0.0f;
	_21 = 0.0f;	_22 = 2.0f / (t - b);	_23 = 0.0f;	_24 = 0.0f;
	_31 = 0.0f;	_32 = 0.0f;	_33 = 1.0f / (zn - zf);	_34 = 0.0f;
	_41 = (l + r) / (l - r); _42 = (b + t) / (b - t);	_43 = zn / (zn - zf);	_44 = 1.0f;

	return;
}

inline void FMatrix::SetOrthoOffCenterLH(float l, float r, float b, float t, float zn, float zf)
{
	_11 = 2.0f / (r - l);	_12 = 0.0f;	_13 = 0.0f;	_14 = 0.0f;
	_21 = 0.0f;	_22 = 2.0f / (t - b);	_23 = 0.0f;	_24 = 0.0f;
	_31 = 0.0f;	_32 = 0.0f;	_33 = 1.0f / (zf - zn);	_34 = 0.0f;
	_41 = (l + r) / (l - r); _42 = (b + t) / (b - t);	_43 = -zn / (zf - zn);	_44 = 1.0f;

	return;
}

inline void FMatrix::SetRotationMatrixAxis(const FVector3& axis, float radian)
{
	float c = (float)cos(radian);
	float s = (float)sin(radian);

	float xx = axis.x * axis.x;
	float yy = axis.y * axis.y;
	float zz = axis.z * axis.z;

	float xy = axis.x * axis.y;
	float xz = axis.x * axis.z;
	float yz = axis.y * axis.z;

	_11 = c + (1.f - c) * xx;
	_12 = (1 - c) * xy + s * axis.z;
	_13 = (1 - c) * xz - s * axis.y;
	_14 = 0.0f;

	_21 = (1 - c) * xy - s * axis.z;
	_22 = c + (1 - c) * yy;
	_23 = (1 - c) * yz + s * axis.x;
	_24 = 0.0f;

	_31 = (1 - c) * xz + s * axis.y;
	_32 = (1 - c) * yz - s * axis.x;
	_33 = c + (1 - c) * zz;
	_34 = 0.0f;

	_41 = 0.0f;
	_42 = 0.0f;
	_43 = 0.0f;
	_44 = 1.0f;

	return;
}

inline void FMatrix::SetRotationYawPitchRoll(float yaw, float pitch, float roll)
{
	float cy = (float)cos(yaw);
	float sy = (float)sin(yaw);

	float cp = (float)cos(pitch);
	float sp = (float)sin(pitch);
	float cr = (float)cos(roll);
	float sr = (float)sin(roll);

	_11 = cy * cp;
	_12 = sy * cp;
	_13 = -sy;
	_14 = 0.0f;

	_21 = cy * sp * sr - sy * sr;
	_22 = sy * sp * sr + cy * cr;
	_23 = cp * sy;
	_24 = 0.0f;

	_31 = cy * sp * cr + sy * sr;
	_32 = sy * sp * cr - cy * sp;
	_33 = cy * cr;
	_34 = 0.0f;

	_41 = _42 = _43 = 0.0f;
	_44 = 1.0f;
}

inline void FMatrix::SetLocalMatrix(const FVector3& position, const FVector3& dir, const FVector3& up)
{
	FVector3 NRight = dir.CrossProduct(up);

	if (NRight == FVector3::ZERO)
	{
		NRight = dir.CrossProduct(FVector3(0, 1, 0));
	}

	FVector3 NDir = dir;
	FVector3 NUp = CrossProduct(NRight, dir);

	// È¸Àü °ª¸¸ ÀÖ´Â Çà·ÄÀ» ¸¸µé±â À§ÇØ¼­ °¢ Ãà¼ººÐÀ» NormalizeÇØÁà¾ß ÇÑ´Ù.
	NRight.Normalize();
	NDir.Normalize();
	NUp.Normalize();

	SetLocalMatrix(position, NDir, NUp, NRight);
}

inline void FMatrix::SetLocalMatrix(const FVector3& position, const FVector3& dir, const FVector3& up, const FVector3& right)
{
	_11 = right.x;
	_12 = right.y;
	_13 = right.z;
	_14 = 0;

	_21 = dir.x;
	_22 = dir.y;
	_23 = dir.z;
	_24 = 0;

	_31 = up.x;
	_32 = up.y;
	_33 = up.z;
	_34 = 0;

	_41 = position.x;
	_42 = position.y;
	_43 = position.z;
	_44 = 1.0f;
}

inline void FMatrix::SetScreenSpaceMatrix(DWORD dwScreenWidth, DWORD dwScreenHeight)
{
	MakeIdentity();
	SetTranslation(FVector3(0.5f + 0.5f / dwScreenWidth, 0.5f + 0.5f / dwScreenHeight, 0.0f));
	SetScale(FVector3(0.5f, -0.5f, 1.0f));
}

inline bool FMatrix::GetInverse(FMatrix* pOut, float* fDet) const
{
	const FMatrix& m = *this;

	float d = (m._11 * m._22 - m._12 * m._21) * (m._33 * m._44 - m._34 * m._43) - (m._11 * m._23 - m._13 * m._21) * (m._32 * m._44 - m._34 * m._42)
		+ (m._11 * m._24 - m._14 * m._21) * (m._32 * m._43 - m._33 * m._42) + (m._12 * m._23 - m._13 * m._22) * (m._31 * m._44 - m._34 * m._41)
		- (m._12 * m._24 - m._14 * m._22) * (m._31 * m._43 - m._33 * m._41) + (m._13 * m._24 - m._14 * m._23) * (m._31 * m._42 - m._32 * m._41);

	if (fDet)* fDet = d;

	if (d == 0.f)
		return false;

	d = 1.f / d;

	FMatrix& out = *pOut;

	out._11 = d * (m._22 * (m._33 * m._44 - m._34 * m._43) + m._23 * (m._34 * m._42 - m._32 * m._44) + m._24 * (m._32 * m._43 - m._33 * m._42));
	out._12 = d * (m._32 * (m._13 * m._44 - m._14 * m._43) + m._33 * (m._14 * m._42 - m._12 * m._44) + m._34 * (m._12 * m._43 - m._13 * m._42));
	out._13 = d * (m._42 * (m._13 * m._24 - m._14 * m._23) + m._43 * (m._14 * m._22 - m._12 * m._24) + m._44 * (m._12 * m._23 - m._13 * m._22));
	out._14 = d * (m._12 * (m._24 * m._33 - m._23 * m._34) + m._13 * (m._22 * m._34 - m._24 * m._32) + m._14 * (m._23 * m._32 - m._22 * m._33));
	out._21 = d * (m._23 * (m._31 * m._44 - m._34 * m._41) + m._24 * (m._33 * m._41 - m._31 * m._43) + m._21 * (m._34 * m._43 - m._33 * m._44));
	out._22 = d * (m._33 * (m._11 * m._44 - m._14 * m._41) + m._34 * (m._13 * m._41 - m._11 * m._43) + m._31 * (m._14 * m._43 - m._13 * m._44));
	out._23 = d * (m._43 * (m._11 * m._24 - m._14 * m._21) + m._44 * (m._13 * m._21 - m._11 * m._23) + m._41 * (m._14 * m._23 - m._13 * m._24));
	out._24 = d * (m._13 * (m._24 * m._31 - m._21 * m._34) + m._14 * (m._21 * m._33 - m._23 * m._31) + m._11 * (m._23 * m._34 - m._24 * m._33));
	out._31 = d * (m._24 * (m._31 * m._42 - m._32 * m._41) + m._21 * (m._32 * m._44 - m._34 * m._42) + m._22 * (m._34 * m._41 - m._31 * m._44));
	out._32 = d * (m._34 * (m._11 * m._42 - m._12 * m._41) + m._31 * (m._12 * m._44 - m._14 * m._42) + m._32 * (m._14 * m._41 - m._11 * m._44));
	out._33 = d * (m._44 * (m._11 * m._22 - m._12 * m._21) + m._41 * (m._12 * m._24 - m._14 * m._22) + m._42 * (m._14 * m._21 - m._11 * m._24));
	out._34 = d * (m._14 * (m._22 * m._31 - m._21 * m._32) + m._11 * (m._24 * m._32 - m._22 * m._34) + m._12 * (m._21 * m._34 - m._24 * m._31));
	out._41 = d * (m._21 * (m._33 * m._42 - m._32 * m._43) + m._22 * (m._31 * m._43 - m._33 * m._41) + m._23 * (m._32 * m._41 - m._31 * m._42));
	out._42 = d * (m._31 * (m._13 * m._42 - m._12 * m._43) + m._32 * (m._11 * m._43 - m._13 * m._41) + m._33 * (m._12 * m._41 - m._11 * m._42));
	out._43 = d * (m._41 * (m._13 * m._22 - m._12 * m._23) + m._42 * (m._11 * m._23 - m._13 * m._21) + m._43 * (m._12 * m._21 - m._11 * m._22));
	out._44 = d * (m._11 * (m._22 * m._33 - m._23 * m._32) + m._12 * (m._23 * m._31 - m._21 * m._33) + m._13 * (m._21 * m._32 - m._22 * m._31));

	return true;
}

inline FMatrix FMatrix::GetTranspose() const
{
	FMatrix ret;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			ret._m[j][i] = _m[i][j];
		}
	}
	return ret;
}

inline void FMatrix::ExtractScale(FVector3& vecScale) const
{
	vecScale.x = FVector3(_11, _12, _13).Length();
	vecScale.y = FVector3(_21, _22, _23).Length();
	vecScale.z = FVector3(_31, _32, _33).Length();
}


//////////////////////////////////////////////////////////////////////////
// Aligned 16 Matrix (for SSE)
__declspec(align(16))
class GEASSCOMMON_API FMatrixA16 : public FMatrix
{
public:
	inline FMatrixA16& operator=(const FMatrixA16& other);
	inline FMatrixA16& operator=(const FMatrix& other);

	inline void MultiplyTo(const FMatrixA16& other, FMatrixA16& out) const; // out = this * other;
};

inline FMatrixA16& FMatrixA16::operator=(const FMatrixA16& other)
{
	__asm
	{
		mov esi, other;
		mov edi, this;
		movdqa xmm0, xmmword ptr[esi];
		movdqa xmm1, xmmword ptr[esi + 0x10];
		movdqa xmm2, xmmword ptr[esi + 0x20];
		movdqa xmm3, xmmword ptr[esi + 0x30];

		movdqa xmmword ptr[edi], xmm0;
		movdqa xmmword ptr[edi + 0x10], xmm1;
		movdqa xmmword ptr[edi + 0x20], xmm2;
		movdqa xmmword ptr[edi + 0x30], xmm3;
	}
	return *this;
}

inline FMatrixA16& FMatrixA16::operator=(const FMatrix& other)
{
	__asm
	{
		mov esi, other;
		mov edi, this;
		movdqu xmm0, xmmword ptr[esi];
		movdqu xmm1, xmmword ptr[esi + 0x10];
		movdqu xmm2, xmmword ptr[esi + 0x20];
		movdqu xmm3, xmmword ptr[esi + 0x30];

		movdqa xmmword ptr[edi], xmm0;
		movdqa xmmword ptr[edi + 0x10], xmm1;
		movdqa xmmword ptr[edi + 0x20], xmm2;
		movdqa xmmword ptr[edi + 0x30], xmm3;
	}
	return *this;
}

inline void FMatrixA16::MultiplyTo(const FMatrixA16& other, FMatrixA16& mOut) const
{
	__asm
	{
		mov		   eax, mOut	   	   // dst
		mov		   ecx, other	  	   // src1
		mov		   edx, this	  	   // src2

		movaps	 xmm0, xmmword ptr[ecx]	  	   // xmm0 = src1[00, 01, 02, 03]
		movaps	 xmm1, xmmword ptr[ecx + 0x10]	   // xmm1 = src1[04, 05, 06, 07]
		movaps	 xmm2, xmmword ptr[ecx + 0x20]	   // xmm2 = src1[08, 09, 10, 11]
		movaps	 xmm3, xmmword ptr[ecx + 0x30]	   // xmm3 = src1[12, 13, 14, 15]

		movss	  xmm7, dword ptr[edx]		   // xmm7 = src2[00, xx, xx, xx]
		movss	  xmm4, dword ptr[edx + 0x4]	  // xmm4 = src2[01, xx, xx, xx]
		movss	  xmm5, dword ptr[edx + 0x8]	  // xmm5 = src2[02, xx, xx, xx]
		movss	  xmm6, dword ptr[edx + 0xc]	  	   // xmm6 = src2[03, xx, xx, xx]

		shufps	 xmm7, xmm7, 0x0	  	   // xmm7 = src2[00, 00, 00, 00]
		shufps	 xmm4, xmm4, 0x0	  	   // xmm4 = src2[01, 01, 01, 01]
		shufps	 xmm5, xmm5, 0x0	  	   // xmm5 = src2[02, 02, 02, 02]
		shufps	 xmm6, xmm6, 0x0	  	   // xmm6 = src2[03, 03, 03, 03]

		mulps	  xmm7, xmm0	   	   	   // xmm7 *= xmm0
		mulps	  xmm4, xmm1	   	   	   // xmm4 *= xmm1
		mulps	  xmm5, xmm2	   	   	   // xmm5 *= xmm2
		mulps	  xmm6, xmm3	   	   	   // xmm6 *= xmm3

		addps	  xmm7, xmm4	   	   	   // xmm7 += xmm4
		addps	  xmm7, xmm5	   	   	   // xmm7 += xmm5
		addps	  xmm7, xmm6	   	   	   // xmm7 += xmm6

		movaps	 xmmword ptr[eax], xmm7		   // eax = xmm7

		movss	  xmm7, dword ptr[edx + 0x10]	 // xmm7 = src2[04, xx, xx, xx]
		movss	  xmm4, dword ptr[edx + 0x14]	 // xmm4 = src2[05, xx, xx, xx]
		movss	  xmm5, dword ptr[edx + 0x18]	 // xmm5 = src2[06, xx, xx, xx]
		movss	  xmm6, dword ptr[edx + 0x1c]	 // xmm6 = src2[07, xx, xx, xx]

		shufps	 xmm7, xmm7, 0x0	  	   // xmm7 = src2[04, 04, 04, 04]
		shufps	 xmm4, xmm4, 0x0	  	   // xmm4 = src2[05, 05, 05, 05]
		shufps	 xmm5, xmm5, 0x0	  	   // xmm5 = src2[06, 06, 06, 06]
		shufps	 xmm6, xmm6, 0x0	  	   // xmm6 = src2[07, 07, 07, 07]

		mulps	  xmm7, xmm0	   	   	   // xmm7 *= xmm0
		mulps	  xmm4, xmm1	   	   	   // xmm4 *= xmm1
		mulps	  xmm5, xmm2	   	   	   // xmm5 *= xmm2
		mulps	  xmm6, xmm3	   	   	   // xmm6 *= xmm3

		addps	  xmm7, xmm4	   	   	   // xmm7 += xmm4
		addps	  xmm7, xmm5	   	   	   // xmm7 += xmm5
		addps	  xmm7, xmm6	   	   	   // xmm7 += xmm6

		movaps	 xmmword ptr[eax + 0x10], xmm7	 // eax = xmm7

		movss	  xmm7, dword ptr[edx + 0x20]	 // xmm7 = src2[08, xx, xx, xx]
		movss	  xmm4, dword ptr[edx + 0x24]	 // xmm4 = src2[09, xx, xx, xx]
		movss	  xmm5, dword ptr[edx + 0x28]	 // xmm5 = src2[10, xx, xx, xx]
		movss	  xmm6, dword ptr[edx + 0x2c]	 // xmm6 = src2[11, xx, xx, xx]

		shufps	 xmm7, xmm7, 0x0	  	   // xmm7 = src2[08, 08, 08, 08]
		shufps	 xmm4, xmm4, 0x0	  	   // xmm4 = src2[09, 09, 09, 09]
		shufps	 xmm5, xmm5, 0x0	  	   // xmm5 = src2[10, 10, 10, 10]
		shufps	 xmm6, xmm6, 0x0	  	   // xmm6 = src2[11, 11, 11, 11]

		mulps	  xmm7, xmm0	   	   	   // xmm7 *= xmm0
		mulps	  xmm4, xmm1	   	   	   // xmm4 *= xmm1
		mulps	  xmm5, xmm2	   	   	   // xmm5 *= xmm2
		mulps	  xmm6, xmm3	   	   	   // xmm6 *= xmm3

		addps	  xmm7, xmm4	   	   	   // xmm7 += xmm4
		addps	  xmm7, xmm5	   	   	   // xmm7 += xmm5
		addps	  xmm7, xmm6	   	   	   // xmm7 += xmm6

		movaps	 xmmword ptr[eax + 0x20], xmm7	 // eax = xmm7

		movss	  xmm7, dword ptr[edx + 0x30]	 // xmm7 = src2[12, xx, xx, xx]
		movss	  xmm4, dword ptr[edx + 0x34]	 // xmm4 = src2[13, xx, xx, xx]
		movss	  xmm5, dword ptr[edx + 0x38]	 // xmm5 = src2[14, xx, xx, xx]
		movss	  xmm6, dword ptr[edx + 0x3c]	 // xmm6 = src2[15, xx, xx, xx]

		shufps	 xmm7, xmm7, 0x0	  	   // xmm7 = src2[12, 12, 12, 12]
		shufps	 xmm4, xmm4, 0x0	  	   // xmm4 = src2[13, 13, 13, 13]
		shufps	 xmm5, xmm5, 0x0	  	   // xmm5 = src2[14, 14, 14, 14]
		shufps	 xmm6, xmm6, 0x0	  	   // xmm6 = src2[15, 15, 15, 15]

		mulps	  xmm7, xmm0	   	   	   // xmm7 *= xmm0
		mulps	  xmm4, xmm1	   	   	   // xmm4 *= xmm1
		mulps	  xmm5, xmm2	   	   	   // xmm5 *= xmm2
		mulps	  xmm6, xmm3	   	   	   // xmm6 *= xmm3

		addps	  xmm7, xmm4	   	   	   // xmm7 += xmm4
		addps	  xmm7, xmm5	   	   	   // xmm7 += xmm5
		addps	  xmm7, xmm6	   	   	   // xmm7 += xmm6

		movaps	 xmmword ptr[eax + 0x30], xmm7	 // eax = xmm7
	}
}
//////////////////////////////////////////////////////////////////////////
