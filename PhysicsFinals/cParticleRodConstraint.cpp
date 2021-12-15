#include <cParticleRodConstraint.h>
//May put cable constraint here as well

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
		
		//Check if particles are the correct distance apart
		if (currentLength == mLength)
		{
			return 0;
		}
		//If it's not the correct distance, return the rod contact
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

	//CABLE CONSTRAINT
	cParticleCableConstraint::cParticleCableConstraint(cParticle* particleA, cParticle* particleB) : cParticleConstraint(particleA, particleB)
	{
		//Basically same as Rod
		mMaxLength = ParticleSeparation();
	}

	size_t cParticleCableConstraint::AddContact(cParticleContact* contact, size_t limit, std::vector<cParticle*>& particles) const
	{
		//Find the current length of the rod
		float currentLength = ParticleSeparation();

		//Check if particles are over extended
		if (currentLength < mMaxLength)
		{
			return 0;
		}
		//If over-extended, return the rod contact
		contact->mParticle0 = mParticleA;
		contact->mParticle1 = mParticleB;

		//Calculate the normal
		glm::vec3 rodNormal = glm::normalize(mParticleB->GetPosition() - mParticleA->GetPosition());

		//Check if it's extending or compressing
		if (currentLength > mMaxLength)
		{
			//Normal functions differently for each case
			contact->mContactNormal = rodNormal;
			contact->mPenetration = currentLength - mMaxLength;
		}

		//No restitution since we want the particles to stay in the same place
		contact->mRestitution = 0.0f;

		return 1;
	}

}