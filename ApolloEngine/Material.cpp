#include "stdafx.h"
#include "Material.h"
#include "Renderer.h"


namespace Apollo
{
	
Material::Material() :_materialColor( 1,1,1,1)
{

}

Program Material::GetProgram()
{
	return _program;
}

Program Material::GetProgram() const
{
	return _program;
}

const Vector4f* Material::GetMaterialColor() const
{
	return &_materialColor;
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

void Material::SetMaterialColor( const Vector4f& color )
{
	_materialColor = color;
}

}