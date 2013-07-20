#include "stdafx.h"
#include "TransformNode.h"

namespace Apollo
{

Quaternionf TransformNode::_tempQuaternion;
Matrix4x4f TransformNode::_tempMatrix;
Vector3f TransformNode::_tempVector;

TransformNode::TransformNode()
{
	_scaleVector.x = _scaleVector.y = _scaleVector.z = 1.0f;

}

const Matrix4x4f* TransformNode::GetWorldMatrix() const
{
	return &_worldMatrix;
}

Matrix4x4f* TransformNode::GetWorldMatrix()
{
	return &_worldMatrix;
}

const Matrix4x4f * TransformNode::GetRotateMatrix()
{
	return &_rotateMatrix;
}

void TransformNode::UpdateMatrix()
{	
	_worldMatrix.SetIdentity();

	_worldMatrix.Scale( _scaleVector );
	_worldMatrix *= _rotateMatrix;
	_worldMatrix.Translate( _origin );
	
}

void TransformNode::SetWorldMatrix( const Matrix4x4f &matrix )
{
	_worldMatrix = matrix;

	_worldMatrix.MatrixToSRT( _scaleVector, _quaternion, _origin );
	_rotateMatrix = _quaternion.ConvertToMatrix4();

	//_matrixModified = true;
	
}

const Vector3f* TransformNode::GetOrigin()
{
	return &_origin;
}

void TransformNode::SetOrigin( const Vector3f& origin )
{
	_origin = origin;
}

void TransformNode::SetScale( const Vector3f& scale )
{
	_scaleVector = scale;
}

void TransformNode::SetYawDeltaAngle( float angle )
{
	float radianYaw = DEGREE_TO_RADIAN( angle );

	this->GetUpVector( _tempVector );
	_tempQuaternion.x = sin( (float)( radianYaw / 2.0 ) ) * _tempVector.x;
	_tempQuaternion.y = sin( (float)( radianYaw / 2.0 ) ) * _tempVector.y;
	_tempQuaternion.z = sin( (float)( radianYaw / 2.0 ) ) * _tempVector.z;
	_tempQuaternion.w = cos( (float)( radianYaw / 2.0 ) );

	_tempQuaternion *= _quaternion;
	_quaternion = _tempQuaternion;
	_rotateMatrix = _quaternion.ConvertToMatrix4();
}

void TransformNode::SetPitchDeltaAngle( float angle )
{
	float radianPitch = DEGREE_TO_RADIAN( angle );

	this->GetRightVector( _tempVector );
	_tempQuaternion.x = sin( (float)( radianPitch / 2.0 ) ) * _tempVector.x;
	_tempQuaternion.y = sin( (float)( radianPitch / 2.0 ) ) * _tempVector.y;
	_tempQuaternion.z = sin( (float)( radianPitch / 2.0 ) ) * _tempVector.z;
	_tempQuaternion.w = cos( (float)( radianPitch / 2.0 ) );

	_tempQuaternion *= _quaternion;
	_quaternion = _tempQuaternion;
	_rotateMatrix = _quaternion.ConvertToMatrix4();
}

void TransformNode::GetUpVector( Vector3f& vec )
{
	vec.x = _rotateMatrix.GetItems()[ 8 ];
	vec.y = _rotateMatrix.GetItems()[ 9 ];
	vec.z = _rotateMatrix.GetItems()[ 10 ];

	if ( vec.Length() != 1.0 )
	{
		vec.Normalize();
	}
}

void TransformNode::GetRightVector( Vector3f& vec )
{
	vec.x = _rotateMatrix.GetItems()[ 0 ];
	vec.y = _rotateMatrix.GetItems()[ 1 ];
	vec.z = _rotateMatrix.GetItems()[ 2 ];

	if ( vec.Length() != 1.0 )
	{
		vec.Normalize();
	}
}

}