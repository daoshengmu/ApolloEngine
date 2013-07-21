#include "stdafx.h"
#include "Square.h"
#include "Surface.h"
#include "DefaultShader.h"
#include "Renderer.h"

namespace Apollo
{
bool  Square::bInit = false;
float* Square::_vertexData = NULL;
unsigned short* Square::_indexData = NULL;

Square::Square()
{
	_numVertics = 4;
	_vertexSize = 48;
	_numIndices = 6;

	if ( !bInit )
	{
		// Initialize vertex and index data
		float vertexArray[] = { 
			-0.5,0.0,-0.5, 1,1,1,1, 0,0, 0,-1,0,
			0.5,0.0,-0.5, 1,1,1,1, 0,0, 0,-1,0,
			-0.5,0.0, 0.5, 1,1,1,1, 0,0, 0,-1,0,
			0.5,0.0, 0.5, 1,1,1,1, 0,0, 0,-1,0		
		};

		unsigned short indexArray[] = { 0,1,3, 0,3,2 }; 

		_vertexData = (float *)malloc( _vertexSize * _numVertics );
		memcpy_s( _vertexData, _vertexSize * _numVertics, vertexArray, sizeof( vertexArray ) );

		_indexData = (uint16 *)malloc( _numIndices * sizeof(uint16) );
		memcpy_s( _indexData, _numIndices * sizeof(uint16), indexArray, sizeof( indexArray ) );

		Material* pMaterial = Renderer::Instance().CreateMaterial();
		DefaultShader shader;
		pMaterial->CreateProgram( *shader.GetVertexShader(), *shader.GetFragmentShader() );
		pMaterial->SetVertexDeclaration( VD_POS_COLOR_NORMAL );

		_surface = Renderer::Instance().CreateSurface( _numVertics, _vertexSize, _numIndices, pMaterial );
		Renderer::Instance().CreateBuffer( _vertexData, _indexData, _surface );

		_transformNode = new TransformNode();

		_surface->SetWorldMatrixRef( _transformNode->GetWorldMatrix() );

	}
}

TransformNode* Square::GetTransformNode()
{
	return _transformNode;
}

void Square::Update()
{
	_transformNode->UpdateMatrix();
}

}