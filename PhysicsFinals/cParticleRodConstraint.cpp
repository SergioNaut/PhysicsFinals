#include <cParticleRodConstraint.h>
//May put rope constraint here as well

namespace nPhysics
{
	cParticleRodConstraint::cParticleRodConstraint(cParticle* particleA, cParticle* particleB) : cParticleConstraint(particleA, particleB)
	{
		mLength = ParticleSeparation();
	}

	size_t cParticleRodConstraint::AddContact(cParticleContact* contact, size_t limit, std::vector<cParticle*>&particles) const
	{
		//Find the current length of the rod
		float currentLength = ParticleSeparation();
		
		//Check for over-extension 
		if (currentLength == mLength)
		{
			return 0;
		}
		//If it's not over-extended, return the rod contact
		contact->mParticle0 = mParticleA;
		contact->mParticle1 = mParticleB;

		//Calculate the normal
		glm::vec3 rodNormal = glm::normalize(mParticleB->GetPosition() - mParticleA->GetPosition());

		//Check if it's extending or compressing
		if (currentLength > mLength)
		{
			//Normal functions differently for each case
			contact->mContactNormal = rodNormal;
			contact->mPenetration = currentLength - mLength;
		}
		else
		{
			contact->mContactNormal = rodNormal * -1.0f;
			contact->mPenetration = mLength - currentLength;
		}

		//No restitution since we want the particles to stay in the same place
		contact->mRestitution = 0.0f;

		return 1;
	}

}