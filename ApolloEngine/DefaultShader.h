
#pragma once

#include <string>

namespace Apollo
{

class DefaultShader
{
public:
	DefaultShader()
	{
		_vertexShader = 
			"attribute vec3 g_vPositionOS; \n"
			"attribute vec4 g_vColorOS; \n"
			"attribute vec2 g_vTextCoordOS; \n"
			"attribute vec3 g_vNormalOS; \n"

			"uniform mat4 g_worldMatrix; \n"
			"uniform mat4 g_worldViewMatrix; \n"
			"uniform mat4 g_worldViewProjMatrix; \n"
			"uniform vec4 g_eyePosition; \n"
			"uniform vec4 g_sunlightDir; \n"

			"varying vec4 outEyeVec; \n"
			"varying vec3 outNormal; \n"
		//	"varying vec2 outTexcoord; \n"
			"\n"
			"void main(void) \n"
			"{ \n"
			" gl_Position = g_worldViewProjMatrix * vec4( g_vPositionOS, 1.0 ); \n"		
			" vec4 wPos = g_worldMatrix * vec4( g_vPositionOS, 1.0 ); \n"
			" outEyeVec = normalize( g_eyePosition - wPos ); \n"
			" outNormal = vec3( g_worldMatrix * vec4( g_vNormalOS, 0.0 ) ); \n"			
			"} \n";

		_fragmentShader = 
			"uniform vec4 g_sunlightColor; \n"
			"uniform vec4 g_sunlightAmbient; \n"
			"uniform vec4 g_sunlightDir; \n"		
			"varying vec4 outEyeVec; \n"
			"varying vec3 outNormal; \n"		
			"\n"
			"void main(void) \n"
			"{ \n"
			" vec3 color; \n"
			" vec3 normal = normalize( outNormal ); \n"
			" vec4 halfVector = normalize( g_sunlightDir + outEyeVec ); \n"
			" float diff = dot( normal, g_sunlightDir.xyz ); \n"
			" diff = min( max( 0.0, diff ), 1.0); \n"
 			" float spec = dot( normal, halfVector.xyz ); \n"
 			" spec = min( max( 0.0, spec ), 1.0 ); \n"
 			" spec = pow( spec, g_sunlightColor.w ); \n" 		
			" color = g_sunlightAmbient.xyz + ( g_sunlightColor.xyz * (diff+spec)  ); \n"
			" gl_FragColor = vec4( color.x, color.y, color.z, 1.0); \n"
			"} \n";
	}

	const std::string* GetVertexShader() { return &_vertexShader; }
	const std::string* GetFragmentShader() { return &_fragmentShader; }

private:
	std::string _vertexShader;
	std::string _fragmentShader;

};

}