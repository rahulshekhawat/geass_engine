#pragma once

#include "pch.h"
#include "glib.h"
#include "vector3.h"
#include "vector4.h"

#pragma intrinsic ( _mm_hadd_ps )

class GEASS_API FMatrix
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

	/*
	FMatrix& operator=(const FMatrix& other);
	bool operator==(const FMatrix& other) const;
	bool operator!=(const FMatrix& other) const;
	FMatrix& operator*=(const FMatrix& other);
	FMatrix operator*(const FMatrix& other) const;
	FMatrix operator*(float f) const;
	FMatrix operator-(const FMatrix& other) const;	// 090716, OZ
	FMatrix operator+(const FMatrix& other) const;	// 090716, OZ

	// casting
	operator float* () { return m; }
	operator const float* () const { return (const float*)m; }

	// transform, mvector * mmatrix �� ��ü����.
	friend FVector3 operator * (const FVector3& v, const FMatrix& tm);
	friend FVector4 operator * (const FVector4& v, const FMatrix& tm);

	void TransformVect(FVector3& vect) const;
	void TransformVectHomogeneous(FVector3& vect) const;
	void TransformVect(const FVector3& in, FVector3& out) const;
	void TransformVect(const FVector3& in, FVector4& out) const;
	void TransformNormal(FVector3& vect) const;
	void TransformNormal(const FVector3& in, FVector3& out) const;
	void TransformPlane(const MPlane& in, MPlane& out) const;

	void MultiplyTo(const FMatrix& other, FMatrix& out) const; // out = this * other;

	void MakeZero();
	void MakeIdentity();

	// ������Ʈ�� ����
	void SetTranslation(const FVector3& trans);
	void SetInverseTranslation(const FVector3& trans);
	FVector3 GetTranslation() const;
	void SetRotationRadians(const FVector3& rotation);
	void SetRotationDegrees(const FVector3& rotation);
	void SetScale(const FVector3& scale);
	void SetScale(float s);
	void SetRotationX(float fRadian);
	void SetRotationY(float fRadian);
	void SetRotationZ(float fRadian);

	// matrix ��ü�� �������ִ� ������ǵ�
	void SetRotationMatrix(float x, float y, float z) { SetRotationMatrix(FVector3(x, y, z)); }
	void SetRotationMatrix(const FVector3& rotation);// ���� : ����
	void SetTranslationMatrix(float x, float y, float z) { SetTranslationMatrix(FVector3(x, y, z)); }
	void SetTranslationMatrix(const FVector3& trans);
	void SetScaleMatrix(float x, float y, float z) { SetScaleMatrix(FVector3(x, y, z)); }
	void SetScaleMatrix(const FVector3& scale);
	void SetProjectionMatrixRH(float w, float h, float zNear, float zFar);
	void SetProjectionMatrixLH(float w, float h, float zNear, float zFar);
	void SetProjectionMatrixFovRH(float fFOVy, float fAspectRatio, float zNear, float zFar);
	void SetProjectionMatrixFovLH(float fFOVy, float fAspectRatio, float zNear, float zFar);
	void SetLookAtMatrixLH(const FVector3& position, const FVector3& target, const FVector3& upVector);
	void SetLookAtMatrixRH(const FVector3& position, const FVector3& target, const FVector3& upVector);
	void SetOrthoLH(float w, float h, float zn, float zf);
	void SetOrthoRH(float w, float h, float zn, float zf);
	void SetOrthoOffCenterRH(float l, float r, float b, float t, float zn, float zf);
	void SetOrthoOffCenterLH(float l, float r, float b, float t, float zn, float zf);

	void SetRotationMatrixAxis(const FVector3& axis, float radian);
	void SetRotationYawPitchRoll(float yaw, float pitch, float roll);	// �׽�Ʈ ���� �ʾ���.
	void SetLocalMatrix(const FVector3& position, const FVector3& dir, const FVector3& up);
	void SetLocalMatrix(const FVector3& position, const FVector3& dir, const FVector3& up, const FVector3& right);

	void SetScreenSpaceMatrix(DWORD dwScreenWidth, DWORD dwScreenHeight);

	bool GetInverse(FMatrix* pOut, float* fDet) const;
	FMatrix GetTranspose() const;

	/// ����� scale,translation,rotation ���� ����
	bool Decompose(FVector3& vecScale, FVector3& vecTranslation, MQuat& quatRotation) const;
	// ���̴��� �Ѱ��ִ� ������ ��� ���� �� Vector4�� ���ϴ�. Decompose Vector4¥�� - 090722, OZ
	bool Decompose(FVector3& vecScale, FVector4& vecTranslation, MQuat& quatRotation) const;
	// �������� ���� �ʴ� Decompose() - 090724, OZ
	bool Decompose(FVector3& vecTranslation, MQuat& quatRotation) const;

	/// ����� scale ���� ����
	void ExtractScale(FVector3& vecScale) const;
	*/
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
