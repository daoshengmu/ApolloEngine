#pragma once

#include "RenderItem.h"
#include "TransformNode.h"

/**
*
* @file     Cube.h
* @author   Daosheng Mu
* @version  1.0
*
* @section  LICENSE
*
* (C) All rights reserved.
*
* @section	Description
*
* Cube class
*
*/

namespace Apollo
{
class Cube : public RenderItem
{
public:
	//--------------------------------------------------------------------------------------
	/// @brief Constructor
	//--------------------------------------------------------------------------------------
	Cube();

	//--------------------------------------------------------------------------------------
	/// @brief Get transform node
	/// 
	/// @return Transform node
	//--------------------------------------------------------------------------------------
	TransformNode* GetTransformNode();
	
	//--------------------------------------------------------------------------------------
	/// @brief Update method
	//--------------------------------------------------------------------------------------
	virtual void Update();

private:
	static bool bInit;
	static float* _vertexData;
	static unsigned short* _indexData;

	TransformNode* _transformNode;

};
}