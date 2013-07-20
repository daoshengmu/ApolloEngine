#pragma once

#include "RenderItem.h"
#include "TransformNode.h"

namespace Apollo
{
class Cube : public RenderItem
{
public:
	Cube();
	TransformNode* GetTransformNode();
	virtual void Update();

private:
	static bool bInit;
	static float* _vertexData;
	static unsigned short* _indexData;

	TransformNode* _transformNode;

};
}