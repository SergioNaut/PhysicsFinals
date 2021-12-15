#include <particle_contact_generators.h>

namespace nPhysics
{
	//TODO: add stuff for correct particle contact generator
	cPlaneParticleContactGenerator::cPlaneParticleContactGenerator(glm::vec3 nNormal,float dDistance, float sSphereRadius)
	{
		mNormal = nNormal;
		distance = dDistance;
		sphereRadius = sSphereRadius;
	}
	
	cPlaneParticleContactGenerator::~cPlaneParticleContactGenerator(){}

	size_t cPlaneParticleContactGenerator::AddContact(cParticleContact* contact, size_t limit, std::vector<cParticle*>& particles) const
	{
		size_t numContactsCreated = 0;
		for (std::vector<cParticle*>::iterator p = particles.begin(); p != particles.end(); p++)
		{
			//TODO: All this stuff
			//Only relevant to the cGround...generator
			//float y = (*p)->GetPosition().y;
			glm::vec3 particlePosition = (*p)->GetPosition();
			float newSphereRadius = (*p)->GetRadius();
			
			//distance = glm::dot(particlePosition,mNormal);
			float particleDistance = glm::dot(particlePosition, glm::normalize(mNormal))-distance;

			//I think that's correct
			//if (distance <= sphereRadius)
			if (particleDistance <= newSphereRadius)
			{
				//I think that's correct
				contact->mContactNormal = mNormal;
				contact->mParticle0 = *p;
				contact->mParticle1 = nullptr;
				//I think that's correct
				//contact->mPenetration = sphereRadius - distance /*particleDistance*/;
				contact->mPenetration = newSphereRadius - particleDistance;
				//Generic restitution for now
				contact->mRestitution = 0.5f;
				contact++;
				numContactsCreated++;
			}
			if (numContactsCreated >= limit)
			{
				return numContactsCreated;
			}
		}
		return numContactsCreated;
	}

	//SphereSphere stuff!

	cSphereSphereContactGenerator::cSphereSphereContactGenerator(){}
	cSphereSphereContactGenerator::~cSphereSphereContactGenerator(){}
	size_t cSphereSphereContactGenerator::AddContact(cParticleContact* contact, size_t limit, std::vector<cParticle*>& particles) const
	{
		size_t nContactsCreated = 0;
		for (size_t i = 0; i < particles.size() - 1; i++)
		{
			//TODO: Read particles' radius
			//float radiusA = 1.0f;
			float radiusA = particles[i]->GetRadius();
			for (size_t j = i + 1; j < particles.size(); j++)
			{
				//float radiusB = 1.0f;
				float radiusB = particles[j]->GetRadius();

				glm::vec3 separation = particles[i]->GetPosition() - particles[j]->GetPosition();

				//There's a better way of doing it?
				float distance = glm::length(separation);
				if (radiusA + radiusB > distance)
				{
					//This is a contact
					contact->mParticle0 = particles[i];
					contact->mParticle1 = particles[j];
					contact->mContactNormal = glm::normalize(separation);
					contact->mPenetration = radiusA + radiusB - distance;
					contact->mRestitution = 0.5f;
					nContactsCreated++;
					contact++;
				}

				if (nContactsCreated >= limit)
				{
					return nContactsCreated;
				}
			}
		}
		return nContactsCreated;
	}
}