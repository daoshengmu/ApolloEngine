
#pragma once

#include "core/core.h"
#include "GraphicsType.h"
#include "Surface.h"
#include "Camera.h"
#include <string>

namespace Apollo
{

class Graphics
{
public:
	Graphics() :_wndHandle( NULL ) {}

	bool Initialize( HWND handle, UINT width, UINT height, bool bFullScreen );
	void ClearColor( const Vector4<float> &color );
	void CreateBuffer( const float* vertexData, const uint16* indexData, Surface* pSurface );
	Program CreateProgram( const std::string& vertexShaderStr, const std::string& fragShaderStr );
	void SetVertexDeclaration( EVertexDecl vtxDclType );
	void SetVertexBufferAt( int index, VertexBuffer buffer );
	void SetProgram( Program program );
	void SetProgramConstantsFromMatrix( int firstRegister, const Matrix4x4f &matrix );
	void SetProgramConstantsFromVector( int firstRegister, const Vector4f &vector );	
	void SetCamera( Camera *pCamera );
	void Draw( const Surface *surf );
	void DrawTriangles( IndexBuffer indexBuffer, uint numIndices );
	void EndFrame();
	void Terminate();
	
private:
	
	HWND _wndHandle;
	HDC _glDev;
	HGLRC _glhRC;

	Matrix4x4f _worldViewProjMatrix;
	Matrix4x4f _viewProjMatrix;
	Matrix4x4f _worldViewMatrix;
	Matrix4x4f _viewMatrix;

};

}