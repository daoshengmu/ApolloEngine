#pragma once

#include "TransformNode.h"
#include "RenderItem.h"

namespace Apollo
{
class Square : public RenderItem
{
public:
	Square();

	//--------------------------------------------------------------------------------------
	/// @brief Get square's transform node, including SRT transformation
	/// 
	/// @return TransformNode
	//--------------------------------------------------------------------------------------
	TransformNode* GetTransformNode();
	
	//--------------------------------------------------------------------------------------
	/// @brief Update square
	//--------------------------------------------------------------------------------------
	virtual void Update();

private:
	static bool bInit;
	static float* _vertexData;
	static unsigned short* _indexData;

	TransformNode* _transformNode;

};
}