
#pragma once

#include "core/core.h"

/**
*
* @file     LightManager.h
* @author   Daosheng Mu
* @version  1.0
*
* @section  LICENSE
*
* (C) All rights reserved.
*
* @section	Description
*
* Light manager to manage global lighting
*
*/

namespace Apollo
{
class LightManager  // Now, only support one directional light
{
public:
	//--------------------------------------------------------------------------------------
	/// @brief Light manager instance
	///
	/// @return instance
	//--------------------------------------------------------------------------------------
	static LightManager& Instance()
	{
		static LightManager manager;

		return manager;
	}

	//--------------------------------------------------------------------------------------
	/// @brief Set ambient color
	/// 
	/// @param [in] color Ambient color
	//--------------------------------------------------------------------------------------
	void SetAmbientColor( const Vector4f& color )
	{
		_ambientColor = color;
	}

	//--------------------------------------------------------------------------------------
	/// @brief Get ambient color
	/// 
	/// @return Ambient color
	//--------------------------------------------------------------------------------------
	const Vector4f* GetAmbientColor()
	{
		return &_ambientColor;
	}

	//--------------------------------------------------------------------------------------
	/// @brief Set light direction
	/// 
	/// @param [in] dir light direction
	/// 
	/// @return Self
	//--------------------------------------------------------------------------------------
	void SetDirection( const Vector3f& dir )
	{
		_lightDir = dir;
	}

	//--------------------------------------------------------------------------------------
	/// @brief Get light direction
	/// 
	/// @return Light direction
	//--------------------------------------------------------------------------------------
	const Vector3f* GetDirection()
	{
		return &_lightDir;
	}

	//--------------------------------------------------------------------------------------
	/// @brief Set directional color
	/// 
	/// @param [in] color directional light color
	//--------------------------------------------------------------------------------------
	void SetDirectionalColor( const Vector4f& color )
	{
		_lightColor = color;
	}

	//--------------------------------------------------------------------------------------
	/// @brief Get directional light color
	/// 
	/// @return light color
	//--------------------------------------------------------------------------------------
	const Vector4f* GetDirectionalColor()
	{
		return &_lightColor;
	}

private:
	LightManager() {};
	LightManager( const LightManager& manager ){ *this = manager; };


private:
	Vector4f _ambientColor;
	Vector4f _lightColor;
	Vector3f _lightDir;
};
}