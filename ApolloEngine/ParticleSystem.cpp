#include "stdafx.h"
#include "ParticleSystem.h"
#include "Renderer.h"
#include "DefaultShader.h"

namespace Apollo
{

const uint MAX_LIFE_TIME = 200;

ParticleSystem::ParticleSystem()
{
	_numVertics = _emitter._numVertics;
	_vertexSize = _emitter._vertexSize;
	_numIndices = _emitter._numIndices;

	Material* pMaterial = Renderer::Instance().CreateMaterial();
	DefaultShader shader;
	pMaterial->CreateProgram( *shader.GetVertexShader(), *shader.GetFragmentShader() );
	pMaterial->SetVertexDeclaration( VD_POS_COLOR_NORMAL );

	_surface = Renderer::Instance().CreateSurface( _numVertics, _vertexSize, _numIndices, pMaterial );
	Renderer::Instance().CreateBuffer( _emitter.GetVertexData(), _emitter.GetIndexData(), _surface );

	_transformNode = new TransformNode();

	_surface->SetWorldMatrixRef( _transformNode->GetWorldMatrix() );
}

TransformNode* ParticleSystem::GetTransformNode()
{
	return _transformNode;
}

void ParticleSystem::Update()
{
	_transformNode->UpdateMatrix();
	_emitter.Update();

	Surface *surface = this->GetSurface();

	const float* vertexData = _emitter.GetVertexData(); 
	surface->UploadVertexBuffer( vertexData, _numVertics, _vertexSize );
	const uint16 *indexData = _emitter.GetIndexData();
	surface->UploadIndexBuffer( indexData, _numIndices );
}

const uint ParticleEmitter::_maxNumParticles = 30;
unsigned short* ParticleEmitter::_indexData = NULL; 

void ParticleEmitter::Update()
{
	Particle *particle;
	ParticleQuad::ParticleVertice *vertice;	
	static const uint quadSize = 4; 

	for ( uint i = 0; i < _maxNumParticles; i++ )
	{	
		for ( uint j = 0; j < quadSize; ++j )
		{
			vertice = &((ParticleQuad *)_particlesData)->vertex[j];			
			vertice->pos[0] -= 0.2f;
		}

		particle = &((Particle *)_particles)[i];
	 	particle->lifeTime++;

		if ( particle->lifeTime > MAX_LIFE_TIME )
		{
			ParticleQuad::ParticleVertice particleVertex;

			memcpy( vertice, &particleVertex, sizeof(ParticleQuad::ParticleVertice) );

			particle->lifeTime = 0;
		}

	}
	
}

const uint ParticleEmitter::_numVertics = _maxNumParticles * 4;
const uint ParticleEmitter::_vertexSize = 48;
const uint ParticleEmitter::_numIndices = _maxNumParticles  * 6;

ParticleEmitter::ParticleEmitter()
	:_count(0)
{
	if ( !_indexData )
	{
		_indexData = (uint16 *)malloc( _numIndices * sizeof(uint16) );
	}

	for ( uint i = 0; i < _maxNumParticles; i++ )
	{
		_indexData[ 6 * i ] = 0 + (i*6);
		_indexData[ 6 * i + 1] = 1 + (i*6);
		_indexData[ 6 * i + 2] = 3 + (i*6);
		_indexData[ 6 * i + 3] = 0 + (i*6);
		_indexData[ 6 * i + 4] = 3 + (i*6);
		_indexData[ 6 * i + 5] = 2 + (i*6);
	}
	
	_particlesData = (float*)malloc( sizeof( ParticleQuad::ParticleVertice) * _numVertics );

	uint offset = 0;
	for ( uint i = 0; i < _maxNumParticles; i++ )
	{
		ParticleQuad particleQuad;	

		memcpy( ((char*)_particlesData + offset), &particleQuad, sizeof( ParticleQuad) );
		offset += sizeof(ParticleQuad);
	}

	_particles = (Particle*)malloc( sizeof( Particle) * _maxNumParticles );

	offset = 0;
	for ( uint i = 0; i < _maxNumParticles; i++ )
	{
		Particle particle;	

		memcpy( ((char*)_particles + offset), &particle, sizeof( Particle ) );
		offset += sizeof(Particle);
	}
}

const float* ParticleEmitter::GetVertexData()
{
	return _particlesData;
}

const uint16* ParticleEmitter::GetIndexData()
{
	return _indexData;
}

}