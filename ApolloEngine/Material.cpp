#include "stdafx.h"
#include "Material.h"
#include "Renderer.h"


namespace Apollo
{


Program Material::GetProgram()
{
	return _program;
}

Program Material::GetProgram() const
{
	return _program;
}

void Material::CreateProgram( const std::string& vertexShader, const std::string& fragmentShader )
{
	_program = Renderer::Instance().CreateProgram( vertexShader, fragmentShader );
}

void Material::SetVertexDeclaration( EVertexDecl type )
{
	_vertexDecl = type;
}

EVertexDecl Material::GetVertexDeclaration() const
{
	return _vertexDecl;
}

}