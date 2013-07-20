
#include "stdafx.h"
#include "Surface.h"

namespace Apollo
{

Surface::Surface( uint numVertices, uint vertexSize, uint numIndices, Material *pMaterial )
	: _numVertices( numVertices ), _vertexSize( vertexSize ), _numIndices( numIndices ), _material( pMaterial )
{

}

Apollo::uint Surface::GetNumVertices() const
{
	return _numVertices;
}

Apollo::uint Surface::GetVertexSize()
{
	return _vertexSize;
}

Apollo::uint Surface::GetNumIndices() const
{
	return _numIndices;
}

void Surface::SetIndexBuffer( IndexBuffer buffer )
{
	_indexBuffer = buffer;
}

void Surface::SetVertexBuffer( VertexBuffer buffer )
{
	_vertexBuffer = buffer;
}

void Surface::SetWorldMatrixRef( Matrix4x4f *pMatrix )
{
	_worldMatrix = pMatrix;
}

const Material * Surface::GetMaterial() const
{
	return _material;
}

const Matrix4x4f * Surface::GetWorldMatrix() const
{
	return _worldMatrix;
}

IndexBuffer Surface::GetIndexBuffer() const 
{
	return _indexBuffer;
}

VertexBuffer Surface::GetVertexBuffer() const
{
	return _vertexBuffer;
}

}