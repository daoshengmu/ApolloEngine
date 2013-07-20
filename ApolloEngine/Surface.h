
#pragma once

#include "core/core.h"
#include "Material.h"
#include "GraphicsType.h"

namespace Apollo
{
class Surface
{

public:
	Surface( uint numVertices, uint vertexSize, uint numIndices, Material *pMaterial );
	uint GetNumVertices() const;
	uint GetVertexSize();
	uint GetNumIndices() const;
	const Material *GetMaterial() const;
	const Matrix4x4f *GetWorldMatrix() const;
	void SetIndexBuffer( VertexBuffer buffer );
	IndexBuffer GetIndexBuffer() const;
	void SetVertexBuffer( IndexBuffer buffer );
	VertexBuffer GetVertexBuffer() const;
	void SetWorldMatrixRef( Matrix4x4f *pMatrix );

private:
	Surface();

private:
	uint _numVertices;
	uint _vertexSize;
	uint _numIndices;
	Material* _material;
	VertexBuffer _vertexBuffer;
	IndexBuffer _indexBuffer;
	Matrix4x4f *_worldMatrix;

};

}