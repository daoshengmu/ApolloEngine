#pragma once

#include "Graphics.h"
#include "Surface.h"
#include "Cube.h"
#include "Material.h"
#include "Camera.h"
#include <vector>

namespace Apollo
{
class Renderer
{
public:
	static Renderer& Instance()
	{
		static Renderer renderer;

		return renderer;
	}

	void Initialize( HWND handle, UINT width, UINT height );
	void AddRenderItem( RenderItem *pItem );
	void Update();
	void Terminate();
	void SetClearColor( const Vector4f &color );
	Surface* CreateSurface( uint numVertex, uint vertexSize, uint numIndex, Material *pMaterial );
	Material* CreateMaterial();
	Program CreateProgram( const std::string& vertexShader, const std::string& fragmentShader );
	void CreateBuffer( const float* vertexData, const uint16* indexData, Surface* pSurface );
	Cube* Renderer::CreateCube();
	Camera* GetCamera();

protected:
private:
	Renderer() :_pGraphics(NULL), _clearColor( 1, 0, 0, 1 ) {};
	Renderer( const Renderer& rhs );

private:
	Graphics *_pGraphics;
	Vector4f _clearColor;
	std::vector<RenderItem*> _renderItemList;
	Camera _camera;


};

}
