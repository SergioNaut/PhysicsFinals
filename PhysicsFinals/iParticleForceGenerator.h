#pragma once
#include <external_includes.h>
#include <cParticle.h>

namespace nPhysics
{
	class iParticleForceGenerator
	{
	public:
		//Overload and calculate an applied force for the particle, then apply the force to the particle
		virtual ~iParticleForceGenerator() {}
		virtual void Update(cParticle* particle, float deltaTime) = 0;
	};
}