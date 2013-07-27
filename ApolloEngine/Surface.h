
#pragma once

#include "core/core.h"
#include "Material.h"
#include "GraphicsType.h"

namespace Apollo
{
class Surface
{

public:
	//--------------------------------------------------------------------------------------
	/// @brief Construct 
	/// 
	/// @param [in] numVertices Number of vertex
	///
	/// @param [in] vertexSize Size of vertex
	///
	/// @param [in] numIndices Number of index
	///
	/// @param [in] pMaterial material
	/// 
	/// @return Program
	//--------------------------------------------------------------------------------------
	Surface( uint numVertices, uint vertexSize, uint numIndices, Material *pMaterial );

	//--------------------------------------------------------------------------------------
	/// @brief Get number of vertex
	/// 
	/// @return Number of vertex
	//--------------------------------------------------------------------------------------
	uint GetNumVertices() const;

	//--------------------------------------------------------------------------------------
	/// @brief Get vertex size
	/// 
	/// @return Vertex size
	//--------------------------------------------------------------------------------------
	uint GetVertexSize();

	//--------------------------------------------------------------------------------------
	/// @brief Get number of index
	/// 
	/// @return Get number of index
	//--------------------------------------------------------------------------------------
	uint GetNumIndices() const;

	//--------------------------------------------------------------------------------------
	/// @brief Get material
	/// 
	/// @return Material
	//--------------------------------------------------------------------------------------
	Material *GetMaterial() const;
	
	//--------------------------------------------------------------------------------------
	/// @brief Create world matrix
	/// 
	/// @return Matrix
	//--------------------------------------------------------------------------------------
	const Matrix4x4f *GetWorldMatrix() const;

	//--------------------------------------------------------------------------------------
	/// @brief Set index buffer
	/// 
	/// @param [in] buffer Index buffer
	//--------------------------------------------------------------------------------------
	void SetIndexBuffer( IndexBuffer buffer );

	//--------------------------------------------------------------------------------------
	/// @brief Get index buffer
	/// 
	/// @return Index buffer
	//--------------------------------------------------------------------------------------
	IndexBuffer GetIndexBuffer() const;
	
	//--------------------------------------------------------------------------------------
	/// @brief Set vertex buffer
	/// 
	/// @param [in] buffer Vertex buffer
	//--------------------------------------------------------------------------------------
	void SetVertexBuffer( VertexBuffer buffer );
	
	//--------------------------------------------------------------------------------------
	/// @brief Get vertex buffer
	/// 
	/// @return Vertex buffer
	//--------------------------------------------------------------------------------------
	VertexBuffer GetVertexBuffer() const;
	
	//--------------------------------------------------------------------------------------
	/// @brief Set world matrix
	/// 
	/// @param [in] pMatrix World matrix
	//--------------------------------------------------------------------------------------
	void SetWorldMatrixRef( Matrix4x4f *pMatrix );
	
	//--------------------------------------------------------------------------------------
	/// @brief Upload vertex buffer
	/// 
	/// @param [in] data Vertex buffer data
	/// 
	/// @param [in] count Vertex count
	///
	/// @param [in] vertexSize Size of vertex
	//--------------------------------------------------------------------------------------
	void UploadVertexBuffer( const void*data, uint count, uint vertexSize );
	
	//--------------------------------------------------------------------------------------
	/// @brief Upload index buffer
	/// 
	/// @param [in] data Index buffer data
	/// 
	/// @param [in] count Index count
	//--------------------------------------------------------------------------------------
	void UploadIndexBuffer( const void*data, uint count );

private:
	//--------------------------------------------------------------------------------------
	/// @brief Constructor
	//--------------------------------------------------------------------------------------
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