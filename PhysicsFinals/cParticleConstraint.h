#pragma once
#include <iParticleContactGenerator.h>

namespace nPhysics
{
	//Base class for any type of Constraint
	class cParticleConstraint : public iParticleContactGenerator
	{
	public:
		cParticle* mParticleA;
		cParticle* mParticleB;

#pragma region DeleteConstructors
		cParticleConstraint() = delete;
		cParticleConstraint(const cParticleConstraint& other) = delete;
		cParticleConstraint& operator = (const cParticleConstraint& other) = delete;
#pragma endregion
		//Constructor
		cParticleConstraint(cParticle* particleA, cParticle* particleB);
		
		//Virtual Destructor
		virtual ~cParticleConstraint();

		cParticle* GetParticleA();
		cParticle* GetParticleB();

		float ParticleSeparation() const;
	};
}