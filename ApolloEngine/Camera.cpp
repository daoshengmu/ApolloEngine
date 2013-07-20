#include "stdafx.h"
#include "Camera.h"
#include <assert.h>

namespace Apollo
{

Camera::Camera()
	: _fovX( 90.0f ), _fovY( 73.74f ), _near( 4.0f ), _far( 1000.f ),
	  _viewPortW(0), _viewPortH(0)
{
// 	_transformNode.SetWorldMatrix( Matrix4x4f(
// 		0.0f	  ,0.0f	  ,-1.0f	,0.0f,
// 		1.0f      ,0.0f   ,0.0f		,0.0f,
// 		0.0f	  ,1.0f	  ,0.0f		,0.0f,
// 		0.0f	  ,0.0f	  ,0.0f		,1.0f ) );
	SetCameraType( CT_PERSPECTIVE );
}

const Matrix4x4f* Camera::GetProjectionMatrix()
{
	return &_projectionMatrix;
}

const Matrix4x4f* Camera::GetViewMatrix()
{
	Vector3f origin( *_transformNode.GetOrigin() );
	origin *= -1; 

	_viewMatrix.SetIdentity();
	const Matrix4x4f *rotate = _transformNode.GetRotateMatrix();

 	const float *raws = rotate->GetItems();

	_viewMatrix.SetItems(
		raws[0], raws[8],  raws[4], 0.0,
		raws[1], raws[9],  raws[5], 0.0,
		raws[2], raws[10],  raws[6], 0.0,
		origin.x, origin.z,  origin.y, 1.0		
		);

	return &_viewMatrix;
}

void Camera::SetCameraType( ECameraType type )
{
	if ( type == CT_PERSPECTIVE )
	{
		float fov_x;
		float fov_y;
		float Q;

		_projectionMatrix.SetIdentity();
		fov_x =  DEGREE_TO_RADIAN( _fovX );
		fov_y =  DEGREE_TO_RADIAN( _fovY );
		Q     =  _far / (_far - _near); 

	

		_projectionMatrix.SetItems( 
			1.0f/tan(fov_x*0.5f), 0.0f                , 0.0f          , 0.0f,
			0.0f                , 1.0f/tan(fov_y*0.5f), 0.0f          , 0.0f,
			0.0f                , 0.0f                , Q             , 1.0f,
			0.0f                , 0.0f                , (-_near * Q) , 0.0f );

	}
	else if ( type == CT_ORTHOGONAL )
	{
		float l, r, b, t;

		l = (float)-_viewPortW / 2;
		r = (float)_viewPortW / 2;
		b = (float)-_viewPortH / 2;
		t = (float)_viewPortH / 2;	

		_projectionMatrix.SetItems(  
			2.0f/(r-l)             , 0.0f                , 0.0f						, 0.0f,
			0.0f	               , 2.0f/(t-b)  		 , 0.0f						, 0.0f,
			0.0f		           , 0.0f                , 1.0f/(_far - _near)    , 0.0f,
			-(l+r)/(r-l)		   , -(t+b)/(t-b)        , -_near/(_far-_near)	, 1.0f );
	}
	else
	{
		assert( 0 && "Error camera type ");
	}
}

void Camera::SetViewPort( float width, float height )
{
	_viewPortW = width;
	_viewPortH = height;
}

TransformNode* Camera::GetTransformNode()
{
	return &_transformNode;
}

}