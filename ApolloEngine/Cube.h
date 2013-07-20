#pragma once

#include "RenderItem.h"
#include "TransformNode.h"

namespace Apollo
{
class Cube : public RenderItem
{
public:

	Cube();

private:
	static bool bInit;
	static float* _vertexData;
	static unsigned short* _indexData;

	TransformNode* _transformNode;

};
}