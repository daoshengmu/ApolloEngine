#pragma once

#include "Graphics.h"
#include "Surface.h"
#include "Cube.h"
#include "Square.h"
#include "Material.h"
#include "Camera.h"
#include <vector>
#include "ParticleSystem.h"

/**
*
* @file     Renderer.h
* @author   Daosheng Mu
* @version  1.0
*
* @section  LICENSE
*
* (C) All rights reserved.
*
* @section	Description
*
* Renderer module 
*
*/

namespace Apollo
{
class Renderer
{
public:
	//--------------------------------------------------------------------------------------
	/// @brief Renderer instance
	///  
	/// @return Instance
	//--------------------------------------------------------------------------------------
	static Renderer& Instance()
	{
		static Renderer renderer;

		return renderer;
	}

	//--------------------------------------------------------------------------------------
	/// @brief Assign operator
	/// 
	/// @param [in] rhs Assign matrix4x4 from rhs
	/// 
	/// @return Self
	//---------------------------------------------------------------------------------------
	void Initialize( HWND handle, UINT width, UINT height );

	//--------------------------------------------------------------------------------------
	/// @brief Add item to render module
	/// 
	/// @param [in] pItem render item
	//--------------------------------------------------------------------------------------
	void AddRenderItem( RenderItem *pItem );

	//--------------------------------------------------------------------------------------
	/// @brief Update renderer, surface item, and draw
	//--------------------------------------------------------------------------------------
	void Update();

	//--------------------------------------------------------------------------------------
	/// @brief Terminate renderer
	//--------------------------------------------------------------------------------------
	void Terminate();

	//--------------------------------------------------------------------------------------
	/// @brief Set clear color
	/// 
	/// @param [in] color Assign clear color
	//--------------------------------------------------------------------------------------
	void SetClearColor( const Vector4f &color );

	//--------------------------------------------------------------------------------------
	/// @brief Create surface
	/// 
	/// @param [in] numVertex num. of vertex
	///
	/// @param [in] vertexSize size of vertex
	///
	/// @param [in] numIndex num. of index
	///
	/// @param [in] pMaterial material
	/// 
	/// @return Self
	//--------------------------------------------------------------------------------------
	Surface* CreateSurface( uint numVertex, uint vertexSize, uint numIndex, Material *pMaterial );

	//--------------------------------------------------------------------------------------
	/// @brief Create material
	//--------------------------------------------------------------------------------------
	Material* CreateMaterial();

	//--------------------------------------------------------------------------------------
	/// @brief Create program
	/// 
	/// @param [in] vertexShader shader text
	///
	/// @param [in] fragmentShader shader text
	/// 
	/// @return Program
	//--------------------------------------------------------------------------------------
	Program CreateProgram( const std::string& vertexShader, const std::string& fragmentShader );

	//--------------------------------------------------------------------------------------
	/// @brief Assign operator
	/// 
	/// @param [in] rhs Assign matrix4x4 from rhs
	/// 
	/// @return Self
	//--------------------------------------------------------------------------------------
	void CreateBuffer( const float* vertexData, const uint16* indexData, Surface* pSurface );

	//--------------------------------------------------------------------------------------
	/// @brief Create cube
	/// 
	/// @return Cube
	//--------------------------------------------------------------------------------------
	Cube* CreateCube();

	//--------------------------------------------------------------------------------------
	/// @brief Create square
	/// 
	/// @return Square
	//--------------------------------------------------------------------------------------
	Square* CreateSquare(); 

	//--------------------------------------------------------------------------------------
	/// @brief Get camera
	/// 
	/// @return Camera
	//--------------------------------------------------------------------------------------
	Camera* GetCamera();

	//--------------------------------------------------------------------------------------
	/// @brief Create particle system
	/// 
	/// @return ParticleSystem
	//--------------------------------------------------------------------------------------
	ParticleSystem* CreateParticleSystem();

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
