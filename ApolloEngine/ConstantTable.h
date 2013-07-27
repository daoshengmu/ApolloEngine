
#pragma once

#include <map>

namespace Apollo
{

static const char *g_worldViewProjMatrix = "g_worldViewProjMatrix";
static const char *g_worldMatrix = "g_worldMatrix";
static const char *g_worldViewMatrix = "g_worldViewMatrix";
static const char *g_eyePosition = "g_eyePosition";
static const char *g_sunlightDir = "g_sunlightDir";
static const char *g_sunlightColor = "g_sunlightColor";
static const char *g_sunlightAmbient = "g_sunlightAmbient";
static const char *g_materialColor = "g_materialColor";


class ConstantTable
{
public:
	static void InsertToConstantMap( const char *name, int index)
	{
		_value.insert(  std::pair<const char*,int>(name, index) );
	}

	static int FindConstantIndex( const char *name )
	{
		return _value.find( name )->second;
	}

private:
	static std::map< const char*, int> _value;
};

}