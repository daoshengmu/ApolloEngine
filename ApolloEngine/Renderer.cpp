
#include "stdafx.h"
#include "Renderer.h"

namespace Apollo
{

void Renderer::Initialize( HWND handle, UINT width, UINT height )
{
	if ( _pGraphics == NULL )
	{
		_pGraphics = new Graphics();
		_pGraphics->Initialize( handle, width, height, false );
	}
}

void Renderer::Update()
{
	if ( !_pGraphics )
		return;

	_pGraphics->SetCamera( &_camera );
	_pGraphics->ClearColor( _clearColor );

	uint size = _renderItemList.size();
	RenderItem *item;
	for ( uint i = 0; i < size; ++i )
	{
		item = _renderItemList[i];
		item->Update();

		_pGraphics->Draw( item->GetSurface() );
	}

	_pGraphics->EndFrame();
}

void Renderer::Terminate()
{
	_pGraphics->Terminate();
}

void Renderer::SetClearColor( const Vector4f &color )
{
	_clearColor = color;
}

Surface* Renderer::CreateSurface( uint numVertex, uint vertexSize, uint numIndex, Material *pMaterial )
{
	return new Surface( numVertex, vertexSize, numIndex, pMaterial );	
}

Material* Renderer::CreateMaterial()
{
	return new Material();
}

void Renderer::CreateBuffer( const float* vertexData, const uint16* indexData, Surface* pSurface )
{
	_pGraphics->CreateBuffer( vertexData, indexData, pSurface );
}

Cube* Renderer::CreateCube()
{
	Cube *cube = new Cube();

	return cube;
}

void Renderer::AddRenderItem( RenderItem *pItem )
{
	_renderItemList.push_back( pItem );
}

Program Renderer::CreateProgram( const std::string& vertexShader, const std::string& fragmentShader )
{
	return _pGraphics->CreateProgram( vertexShader, fragmentShader );
}

Camera* Renderer::GetCamera()
{
	return &_camera;
}

}