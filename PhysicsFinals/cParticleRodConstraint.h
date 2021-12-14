#pragma once
#include <cParticleConstraint.h>

//Class for Rod Constraints
//May put Ropes here as well
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
}
