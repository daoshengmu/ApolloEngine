
#pragma once

#include "core/core.h"
#include "GraphicsType.h"
#include <string>

namespace Apollo
{

class Material
{
public:
	void CreateProgram( const std::string& vertexShader, const std::string& fragmentShader );
	Program GetProgram();
	Program GetProgram() const;
	void SetVertexDeclaration( EVertexDecl type );
	EVertexDecl GetVertexDeclaration() const;

private:
	Vector4f _materialColor;
	Program  _program;
	EVertexDecl _vertexDecl;

};

}