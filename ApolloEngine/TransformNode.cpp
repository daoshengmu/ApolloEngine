#include "stdafx.h"
#include "TransformNode.h"

namespace Apollo
{

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

}