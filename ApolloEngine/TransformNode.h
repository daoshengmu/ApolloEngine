
#pragma once

#include "core/core.h"

namespace Apollo
{
class TransformNode
{
public:
	TransformNode();

	const Matrix4x4f* GetWorldMatrix() const;
	Matrix4x4f*		  GetWorldMatrix();
	void			  GetUpVector( Vector3f& vec );
	void			  GetRightVector( Vector3f& vec );
	void			  GetLookVector( Vector3f& vec );
	const Matrix4x4f* GetRotateMatrix();
	void			  SetWorldMatrix( const Matrix4x4f &matrix );
	const Vector3f*   GetOrigin();
	void			  SetOrigin( const Vector3f& origin );
	void			  SetScale( const Vector3f& scale );
	void			  UpdateMatrix();
	void			  SetYawDeltaAngle( float angle );
	void			  SetPitchDeltaAngle( float angle );
	void			  RotateAroundAxis( const Vector3f& axis, float angle );

private:
	

private:
	static Quaternionf _tempQuaternion;
	static Matrix4x4f _tempMatrix;
	static Vector3f _tempVector;

	Vector3f _scaleVector;
	Vector3f _origin;
	Matrix4x4f _rotateMatrix;
	Matrix4x4f _worldMatrix;
	Quaternionf _quaternion;
};

}