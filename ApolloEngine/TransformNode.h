
#pragma once

#include "core/core.h"

namespace Apollo
{
class TransformNode
{
public:
	TransformNode();
	const Matrix4x4f *GetWorldMatrix() const;
	Matrix4x4f *GetWorldMatrix();
	const Matrix4x4f *GetRotateMatrix();
	void SetWorldMatrix( const Matrix4x4f &matrix );
	const Vector3f*   GetOrigin();
	void SetOrigin( const Vector3f& origin );

private:
	void UpdateMatrix();

private:
	Vector3f _scaleVector;
	Vector3f _origin;
	Matrix4x4f _rotateMatrix;
	Matrix4x4f _worldMatrix;
	Quaternionf _quaternion;
};

}