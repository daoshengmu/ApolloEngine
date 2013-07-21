#pragma once

#include "TransformNode.h"
#include "RenderItem.h"

namespace Apollo
{
class Square : public RenderItem
{
public:
	Square();
	TransformNode* GetTransformNode();
	virtual void Update();

private:
	static bool bInit;
	static float* _vertexData;
	static unsigned short* _indexData;

	TransformNode* _transformNode;

};
}