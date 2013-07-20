
#pragma once

#include "core/core.h"

namespace Apollo
{
class LightManager  // Now, only support one directional light
{
public:
	static LightManager& Instance()
	{
		static LightManager manager;

		return manager;
	}

	void SetAmbientColor( const Vector4f& color )
	{
		_ambientColor = color;
	}

	const Vector4f* GetAmbientColor()
	{
		return &_ambientColor;
	}

	void SetDirection( const Vector3f& dir )
	{
		_lightDir = dir;
	}

	const Vector3f* GetDirection()
	{
		return &_lightDir;
	}

	void SetDirectionalColor( const Vector4f& color )
	{
		_lightColor = color;
	}

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