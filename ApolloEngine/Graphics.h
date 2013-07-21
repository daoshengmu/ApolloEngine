
#pragma once

#include "core/core.h"
#include "GraphicsType.h"
#include "Surface.h"
#include "Camera.h"
#include <string>

/**
*
* @file     Graphics.h
* @author   Daosheng Mu
* @version  1.0
*
* @section  LICENSE
*
* (C) All rights reserved.
*
* @section	Description
*
* Graphics class, here handle OpenGL API method
*
*/

namespace Apollo
{

class Graphics
{
public:
	//--------------------------------------------------------------------------------------
	/// @brief Constructor
	//--------------------------------------------------------------------------------------
	Graphics() :_wndHandle( NULL ) {}

	//--------------------------------------------------------------------------------------
	/// @brief Initialize
	/// 
	/// @param [in] handle CreateWindow handle
	///
	/// @param [in] width Window width
	///
	/// @param [in] height Window height
	///
	/// @param [in] bFullScreen If using full screen
	//--------------------------------------------------------------------------------------
	bool Initialize( HWND handle, UINT width, UINT height, bool bFullScreen );
	
	//--------------------------------------------------------------------------------------
	/// @brief Clear color
	/// 
	/// @param [in] color Set ClearColor from color
	//--------------------------------------------------------------------------------------
	void ClearColor( const Vector4<float> &color );
	
	//--------------------------------------------------------------------------------------
	/// @brief Create buffer
	/// 
	/// @param [in] vertexData Create vertex buffer by vertex data
	///
	/// @param [in] indexData Create index buffer by index data
	///
	/// @param [in] pSurface Store vertex/index buffer to pSurface
	//--------------------------------------------------------------------------------------
	void CreateBuffer( const float* vertexData, const uint16* indexData, Surface* pSurface );

	//--------------------------------------------------------------------------------------
	/// @brief Create program
	/// 
	/// @param [in] vertexShaderStr vertex shader text
	///
	/// @param [in] fragShaderStr fragment shader text
	/// 
	/// @return OpenGL program
	//--------------------------------------------------------------------------------------
	Program CreateProgram( const std::string& vertexShaderStr, const std::string& fragShaderStr );
	
	//--------------------------------------------------------------------------------------
	/// @brief Set view port
	/// 
	/// @param [in] x View port x position
	///
	/// @param [in] y View port y position
	///
	/// @param [in] w View port width
	///
	/// @param [in[ h View port height
	//--------------------------------------------------------------------------------------
	void SetViewPort( uint x, uint y, uint w, uint h ); 

	//--------------------------------------------------------------------------------------
	/// @brief Set vertex declaration
	/// 
	/// @param [in] vtxDclType Vertex declaration type: EVertexDecl
	/// 
	/// @return Self
	//--------------------------------------------------------------------------------------
	void SetVertexDeclaration( EVertexDecl vtxDclType );

	//--------------------------------------------------------------------------------------
	/// @brief Set vertex buffer
	/// 
	/// @param [in] index Set which channel
	///
	/// @param [in] buffer Vertex buffer
	//--------------------------------------------------------------------------------------
	void SetVertexBufferAt( int index, VertexBuffer buffer );

	//--------------------------------------------------------------------------------------
	/// @brief Set program
	/// 
	/// @param [in] program set the program to API
	//--------------------------------------------------------------------------------------
	void SetProgram( Program program );

	//--------------------------------------------------------------------------------------
	/// @brief Set constants from matrix
	/// 
	/// @param [in] first register The first register to be set
	///
	/// @param [in] matrix Matrix to program
	//--------------------------------------------------------------------------------------
	void SetProgramConstantsFromMatrix( int firstRegister, const Matrix4x4f &matrix );

	//--------------------------------------------------------------------------------------
	/// @brief Set constants from vector
	/// 
	/// @param [in] first register The first register to be set
	/// 
	/// @param [in] vector Vector to program
	//--------------------------------------------------------------------------------------
	void SetProgramConstantsFromVector( int firstRegister, const Vector4f &vector );

	//--------------------------------------------------------------------------------------
	/// @brief Set camera
	/// 
	/// @param [in] camera Set camera to program
	//--------------------------------------------------------------------------------------
	void SetCamera( Camera *pCamera );

	//--------------------------------------------------------------------------------------
	/// @brief Draw surface
	/// 
	/// @param [in] surf Surface wanna be draw
	//--------------------------------------------------------------------------------------
	void Draw( const Surface *surf );

	//--------------------------------------------------------------------------------------
	/// @brief End of frame, swap frame buffer
	//--------------------------------------------------------------------------------------
	void EndFrame();

	//--------------------------------------------------------------------------------------
	/// @brief Terminate OpenGL
	//--------------------------------------------------------------------------------------
	void Terminate();
	
private:

	void DrawTriangles( IndexBuffer indexBuffer, uint numIndices );
	
	HWND _wndHandle;
	HDC _glDev;
	HGLRC _glhRC;

	Matrix4x4f _worldViewProjMatrix;
	Matrix4x4f _viewProjMatrix;
	Matrix4x4f _worldViewMatrix;
	Matrix4x4f _viewMatrix;
	Vector3f   _eyePosition;

};

}