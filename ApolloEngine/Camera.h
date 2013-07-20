
#pragma  once

#include "core/core.h"
#include "TransformNode.h"

namespace Apollo
{
class Camera
{
typedef enum
{
	CT_PERSPECTIVE,
	CT_ORTHOGONAL
} ECameraType;

public:
	Camera();
	void SetCameraType( ECameraType type );
	void SetViewPort( float width, float height );
	const Matrix4x4f* GetViewMatrix();
	const Matrix4x4f* GetProjectionMatrix();	
	void SetOrigin( const Vector3f& origin );
	const Vector3f* GetOrigin();
	

private:
	TransformNode _transformNode;
	Matrix4x4f    _projectionMatrix;
	Matrix4x4f	  _viewMatrix;
	ECameraType   _type;
	float		  _fovX;
	float		  _fovY;
	float		  _near;
	float		  _far;
	float		  _viewPortW;
	float		  _viewPortH;

};
}
