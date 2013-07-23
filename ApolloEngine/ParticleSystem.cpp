#include "stdafx.h"
#include "ParticleSystem.h"
#include "Renderer.h"
#include "DefaultShader.h"

namespace Apollo
{

ParticleSystem::ParticleSystem()
{
	_numVertics = _emitter.GetNumVertices();
	_vertexSize = _emitter.VertexSize;
	_numIndices = _emitter.GetNumIndices();

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

void ParticleSystem::SetEmitDeltaFrame( uint deltaFrame )
{
	_emitter.SetEmitDeltaFrame( deltaFrame );
}

void ParticleSystem::SetMaxParticleLifeFrame( uint lifeFrame )
{
	_emitter.SetMaxParticleLifeFrame( lifeFrame );
}

void ParticleSystem::SetMaxNumParticles( uint numParticles )
{
	_emitter.SetMaxNumParticles( numParticles );
	_numVertics = _emitter.GetNumVertices();
	_numIndices = _emitter.GetNumIndices();
}

void ParticleSystem::SetParticleSpeed( float particleSpeed )
{
	_emitter.SetParticleSpeed( particleSpeed );
}

void ParticleSystem::SetParticleDirection( const Vector2f& dir )
{
	_emitter.SetParticleDirection( dir );
}

unsigned short* ParticleEmitter::_indexData = NULL; 
const uint ParticleEmitter::QuadNumVertex = 4;

void ParticleEmitter::Update()
{
	Particle *particle;
	ParticleVertice *vertex;		
	
	if ( _count <= _maxNumParticles )
	{
		if ( (_frameTime % _deltaFrame) == 0 && (_count < _maxNumParticles) )
		{
			float degree = FRAND() * 15; // random in 30 degrees
			float offsetX = cos( DEGREE_TO_RADIAN(degree) ) * _particleSpeed
															* _particleDirection.x;
			float offsetZ = sin( DEGREE_TO_RADIAN(degree) ) * _particleSpeed 
															* _particleDirection.y;
					
			particle = &((Particle *)_particles)[_count];
			particle->movingX = offsetX;
			particle->movingZ = offsetZ;

			_count++;
		}
		
		uint size = _count;
		ParticleQuad* quad = ((ParticleQuad *)_particlesData);
		for ( uint i = 0; i < size; ++i )
		{
			particle = &((Particle *)_particles)[i];
			particle->lifeTime++;
			
			for ( uint j = 0; j < QuadNumVertex; ++j )
			{			
				vertex = &quad->vertex[j];
				vertex->pos[0] += particle->movingX;				
				vertex->pos[2] += particle->movingZ;
		 		vertex->color[3] = 1.0f;
			}		
					
			if ( particle->lifeTime > _maxLifeTime )
			{
				ParticleQuad particleQuad;
				memcpy( quad, &particleQuad, sizeof(ParticleQuad) );

				particle->lifeTime = 0;				
			}

			quad++;

		}
	}
	
	++_frameTime;	
}

const uint ParticleEmitter::VertexSize = 48;
const uint ParticleEmitter::_indexOffset = 4;

ParticleEmitter::ParticleEmitter()
	:_count(0), _frameTime(0), _deltaFrame( 20 ), _maxLifeTime( 500 ), _maxNumParticles(100), _particleDirection( 1, 0)
	, _particleSpeed(1.0f), _numVertics(_maxNumParticles*4), _numIndices(_maxNumParticles*6)
{
	if ( !_indexData )
	{
		_indexData = (uint16 *)malloc( _numIndices * sizeof(uint16) );
	}

	for ( uint i = 0; i < _maxNumParticles; i++ )
	{
		_indexData[ 6 * i ] = 0 + (i*_indexOffset);
		_indexData[ 6 * i + 1] = 1 + (i*_indexOffset);
		_indexData[ 6 * i + 2] = 3 + (i*_indexOffset);
		_indexData[ 6 * i + 3] = 0 + (i*_indexOffset);
		_indexData[ 6 * i + 4] = 3 + (i*_indexOffset);
		_indexData[ 6 * i + 5] = 2 + (i*_indexOffset);
	}

	_particlesData = (float*)malloc( sizeof( ParticleQuad ) * _maxNumParticles );
	memset( _particlesData, 0, sizeof( ParticleQuad ) * _maxNumParticles );

	uint offset = 0;
	for ( uint i = 0; i < _maxNumParticles; i++ )
	{
		ParticleQuad particleQuad;	

		memcpy( ((char*)_particlesData + offset), &particleQuad, sizeof( ParticleQuad ) );
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

Apollo::uint ParticleEmitter::GetNumVertices()
{
	return _numVertics;
}

Apollo::uint ParticleEmitter::GetNumIndices()
{
	return _numIndices;
}

void ParticleEmitter::SetEmitDeltaFrame( uint deltaFrame )
{
	_deltaFrame = deltaFrame;
}

void ParticleEmitter::SetMaxParticleLifeFrame( uint lifeFrame )
{
	_maxLifeTime = lifeFrame;
}

void ParticleEmitter::SetMaxNumParticles( uint numParticles )
{
	_maxNumParticles = numParticles;
	_numVertics = _maxNumParticles * 4;
	_numIndices = _maxNumParticles * 6;
}

void ParticleEmitter::SetParticleSpeed( float particleSpeed )
{
	_particleSpeed = particleSpeed;
}

void ParticleEmitter::SetParticleDirection( const Vector2f& dir )
{
	_particleDirection = dir;
}

}