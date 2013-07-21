
#pragma once

#include "core/core.h"
#include "GraphicsType.h"
#include <string>

/**
*
* @file     Material.h
* @author   Daosheng Mu
* @version  1.0
*
* @section  LICENSE
*
* (C) All rights reserved.
*
* @section	Description
*
* Material class
*
*/

namespace Apollo
{

class Material
{
public:

	//--------------------------------------------------------------------------------------
	/// @brief Constructor
	//--------------------------------------------------------------------------------------
	Material();

	//--------------------------------------------------------------------------------------
	/// @brief Create program
	/// 
	/// @param [in] vertexShader Vertex shader text
	///
	/// @param [in] fragmentShader fragment shader text
	//--------------------------------------------------------------------------------------
	void CreateProgram( const std::string& vertexShader, const std::string& fragmentShader );

	//--------------------------------------------------------------------------------------
	/// @brief Get program
	///  
	/// @return program
	//--------------------------------------------------------------------------------------
	Program GetProgram();
	Program GetProgram() const;

	//--------------------------------------------------------------------------------------
	/// @brief Set vertex declaration 
	/// 
	/// @param [in] type vertex declaration type
	//--------------------------------------------------------------------------------------
	void SetVertexDeclaration( EVertexDecl type );
	
	//--------------------------------------------------------------------------------------
	/// @brief Get vertex declaration
	/// 
	/// @return vertex declaration
	//--------------------------------------------------------------------------------------
	EVertexDecl GetVertexDeclaration() const;
	
	//--------------------------------------------------------------------------------------
	/// @brief Get material color
	/// 
	/// @return material color
	//--------------------------------------------------------------------------------------
	const Vector4f* GetMaterialColor() const;


	//--------------------------------------------------------------------------------------
	/// @brief Set material color
	/// 
	/// @param [in] color Material color
	//--------------------------------------------------------------------------------------
	void SetMaterialColor( const Vector4f& color );

private:
	Vector4f _materialColor;
	Program  _program;
	EVertexDecl _vertexDecl;

};

}