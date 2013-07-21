#pragma once

#include "RenderItem.h"
#include <list>
#include "TransformNode.h"

/**
*
* @file     ParticleSystem.h
* @author   Daosheng Mu
* @version  1.0
*
* @section  LICENSE
*
* (C) All rights reserved.
*
* @section	Description
*
* Particle system class
*
*/

namespace Apollo
{

//--------------------------------------------------------------------------------------
/// @brief Particle emitter, emit particles.
//--------------------------------------------------------------------------------------
class ParticleEmitter
{
public:
	ParticleEmitter();
	void Update();
	const uint16* GetIndexData();
	const float*  GetVertexData();

	static const  uint _numVertics;
	static const  uint _vertexSize;
	static const  uint _numIndices;

private:
	struct ParticleQuad
	{		
		struct ParticleVertice
		{
			float pos[3];
			float color[4];
			float uv[2];
			float normal[3];
		};

		ParticleVertice vertex[4];				

		ParticleQuad()
		{
			static uint SCALE = 20;

			vertex[0].pos[0] =-0.5f*SCALE, vertex[0].pos[1] = 0.0,
				vertex[0].pos[2] = -0.5f*SCALE;

			vertex[1].pos[0] = 0.5f*SCALE, vertex[1].pos[1] = 0.0,
				vertex[1].pos[2] = -0.5f*SCALE;

			vertex[2].pos[0] =-0.5f*SCALE, vertex[2].pos[1] = 0.0,
				vertex[2].pos[2] = 0.5f*SCALE;

			vertex[3].pos[0] =0.5f*SCALE, vertex[3].pos[1] = 0.0,
				vertex[3].pos[2] = 0.5f*SCALE;

			for ( uint i = 0; i < 4; ++i )
			{
				vertex[i].color[0] = vertex[i].color[1] = vertex[i].color[2] = vertex[i].color[3] = 1.0f;
				vertex[i].uv[0] = vertex[i].uv[1] = 0.0f;
				vertex[i].normal[0] = vertex[i].normal[2] = 0.0f;
				vertex[i].normal[1] = -1.0f;
			}

			
		}
	};

	struct Particle
	{		
		uint lifeTime;

		Particle()
		{		
			lifeTime = 0;
		}
	};

	void * _particles;
	float * _particlesData;
	static const uint _maxNumParticles;
	uint _count;
	static uint16* _indexData;	
};

class ParticleSystem: public RenderItem
{

public:
	ParticleSystem();
	TransformNode* GetTransformNode();
	virtual void Update();

private:	
	TransformNode* _transformNode;
	ParticleEmitter _emitter;
	
};

}
