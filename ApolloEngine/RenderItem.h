
#pragma once

#include <vector>
#include "core/core.h"
#include "GraphicsType.h"
#include "Surface.h"

namespace Apollo
{

class RenderItem
{

public:
	RenderItem() :_surface(NULL) {}
	//void Initialize( std::vector<float> vertices, std::vector<float> indices );
	Surface* GetSurface();
	virtual void Update() = 0;

protected:
	uint		 _numVertics;
	uint		 _vertexSize;
	uint		 _numIndices;
	Surface		 *_surface;	

private:
// 	VertexBuffer  _vertexBuffer;
// 	IndexBuffer   _indexBuffer;
	
	
};

}