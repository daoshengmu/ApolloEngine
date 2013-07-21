
#pragma  once

#include "core/core.h"
#include "TransformNode.h"

/**
*
* @file     Camera.h
* @author   Daosheng Mu
* @version  1.0
*
* @section  LICENSE
*
* (C) All rights reserved.
*
* @section	Description
*
* Camera class
*
*/

namespace Apollo
{
class Camera
{
public:

	typedef enum
	{
		CT_PERSPECTIVE,
		CT_ORTHOGONAL
	} ECameraType;

	//--------------------------------------------------------------------------------------
	/// @brief Constructor
	//--------------------------------------------------------------------------------------
	Camera();

	//--------------------------------------------------------------------------------------
	/// @brief Set camera type
	/// 
	/// @param [in] type Camera type: ECameraType
	//--------------------------------------------------------------------------------------
	void SetCameraType( ECameraType type );

	//--------------------------------------------------------------------------------------
	/// @brief Set view port
	/// 
	/// @param [in] width viewport width
	/// 
	/// @param [in] height viewport height
	//--------------------------------------------------------------------------------------
	void SetViewPort( float width, float height );

	//--------------------------------------------------------------------------------------
	/// @brief Get view matrix
	/// 
	/// @return View matrix
	//--------------------------------------------------------------------------------------
	const Matrix4x4f* GetViewMatrix();

	//--------------------------------------------------------------------------------------
	/// @brief Get projection matrix
	/// 
	/// @return Projection matrix
	//--------------------------------------------------------------------------------------
	const Matrix4x4f* GetProjectionMatrix();	
	
	//--------------------------------------------------------------------------------------
	/// @brief Get transform node
	/// 
	/// @return Transform node
	//--------------------------------------------------------------------------------------
	TransformNode* GetTransformNode();	

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
