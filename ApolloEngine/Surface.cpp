
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

Material * Surface::GetMaterial() const
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

void Surface::UploadVertexBuffer( const void*data, uint count, uint vertexSize )
{
	glBindBuffer( GL_ARRAY_BUFFER, _vertexBuffer );
	glBufferData( GL_ARRAY_BUFFER, count * vertexSize, data, GL_DYNAMIC_DRAW );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void Surface::UploadIndexBuffer( const void*data, uint count )
{
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _indexBuffer );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, count * sizeof( uint16 ), data, GL_DYNAMIC_DRAW );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

}