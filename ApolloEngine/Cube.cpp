
#include "stdafx.h"
#include "Cube.h"
#include "Renderer.h"
#include "DefaultShader.h"

namespace Apollo
{

bool  Cube::bInit = false;
float* Cube::_vertexData = NULL;
unsigned short* Cube::_indexData = NULL;

Cube::Cube()
{
	_numVertics = 24;
	_vertexSize = 48;
	_numIndices = 36;

	if ( !bInit )
	{
		// Initialize vertex and index data
		float vertexArray[] = { 
			-0.5,-0.5,-0.5, 1,1,1,1, 0,0, 0,-1,0,
			0.5,-0.5,-0.5, 1,1,1,1, 0,0, 0,-1,0,
			-0.5,-0.5, 0.5, 1,1,1,1, 0,0, 0,-1,0,
			0.5,-0.5, 0.5, 1,1,1,1, 0,0, 0,-1,0,

			0.5,-0.5,-0.5, 1,1,1,1, 0,0, 1,0,0,
			0.5, 0.5,-0.5, 1,1,1,1, 0,0, 1,0,0,
			0.5,-0.5, 0.5, 1,1,1,1, 0,0, 1,0,0,
			0.5, 0.5, 0.5, 1,1,1,1, 0,0, 1,0,0,

			0.5, 0.5,-0.5, 1,1,1,1, 0,0, 0,1,0,
			-0.5, 0.5,-0.5, 1,1,1,1, 0,0, 0,1,0,
			0.5, 0.5, 0.5, 1,1,1,1, 0,0, 0,1,0,
			-0.5, 0.5, 0.5, 1,1,1,1, 0,0, 0,1,0,

			-0.5, 0.5,-0.5, 1,1,1,1, 0,0, -1,0,0,
			-0.5,-0.5,-0.5, 1,1,1,1, 0,0, -1,0,0,
			-0.5, 0.5, 0.5, 1,1,1,1, 0,0, -1,0,0,
			-0.5,-0.5, 0.5, 1,1,1,1, 0,0, -1,0,0,

			-0.5, 0.5,-0.5, 1,1,1,1, 0,0, 0,0,-1,
			0.5, 0.5,-0.5, 1,1,1,1, 0,0, 0,0,-1,
			-0.5,-0.5,-0.5, 1,1,1,1, 0,0, 0,0,-1,
			0.5,-0.5,-0.5, 1,1,1,1, 0,0, 0,0,-1,

			-0.5,-0.5, 0.5, 1,1,1,1, 0,0, 0,0,1,
			0.5,-0.5, 0.5, 1,1,1,1, 0,0, 0,0,1,
			-0.5, 0.5, 0.5, 1,1,1,1, 0,0, 0,0,1,
			0.5, 0.5, 0.5, 1,1,1,1, 0,0, 0,0,1 
		};


		unsigned short indexArray[] = { 0,1,3, 0,3,2, 4,5,7, 4,7,6, 
			8,9,11, 8,11,10, 12,13,15, 12,15,14, 
			16,17,19, 16,19,18, 20,21,23, 20,23,22 };


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

TransformNode* Cube::GetTransformNode()
{
	return _transformNode;
}

void Cube::Update()
{
	_transformNode->UpdateMatrix();
}

}