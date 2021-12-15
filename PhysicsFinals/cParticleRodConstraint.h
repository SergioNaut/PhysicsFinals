#pragma once
#include <cParticleConstraint.h>

//Class for Rod Constraints
//May put Cables here as well
namespace nPhysics
{
	class cParticleRodConstraint : public cParticleConstraint
	{
	public:
#pragma region DeleteConstructors
		cParticleRodConstraint() = delete;
		cParticleRodConstraint(const cParticleRodConstraint& other) = delete;
		cParticleRodConstraint& operator=(const cParticleRodConstraint& other) = delete;
#pragma endregion

		cParticleRodConstraint(cParticle* particleA, cParticle* particleB);
		virtual size_t AddContact(cParticleContact* contact, size_t limit, std::vector<cParticle*>& particles) const;

		float mLength;
	};

	//Cable Constraints

	class cParticleCableConstraint : public cParticleConstraint
	{
	public:
#pragma region DeleteConstructors
		cParticleCableConstraint() = delete;
		cParticleCableConstraint(const cParticleCableConstraint& other) = delete;
		cParticleCableConstraint& operator=(const cParticleCableConstraint& other) = delete;
#pragma endregion

		cParticleCableConstraint(cParticle* particleA, cParticle* particleB);
		virtual size_t AddContact(cParticleContact* contact, size_t limit, std::vector<cParticle*>& particles) const;

		//Instead of a simple length
		float mMaxLength;
	};
}
