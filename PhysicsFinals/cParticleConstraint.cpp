#include <cParticleConstraint.h>

namespace nPhysics
{
	cParticleConstraint::cParticleConstraint(cParticle* particleA, cParticle* particleB) : mParticleA(particleA), mParticleB(particleB){}

	cParticleConstraint::~cParticleConstraint(){}
	
	cParticle* cParticleConstraint::GetParticleA()
	{
		return mParticleA;
	}

	cParticle* cParticleConstraint::GetParticleB()
	{
		return mParticleB;
	}

	float cParticleConstraint::ParticleSeparation() const
	{
		return glm::distance(mParticleA->GetPosition(), mParticleB->GetPosition());
	}
}