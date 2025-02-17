#pragma once
#include <iParticleContactGenerator.h>

namespace nPhysics
{
	//Simple Contact
	//Based on the ground plane one
	class cPlaneParticleContactGenerator : public iParticleContactGenerator
	{
		//original had a float mGroundHeight
		//5 Instances, 1 for each plane
		glm::vec3 mNormal;
		//distance from origin
		float distance;
		float sphereRadius;
	public:
		
		cPlaneParticleContactGenerator(glm::vec3 nNormal,float dDistance, float sSphereRadius);
		//cPlaneParticleContactGenerator() = delete;
		cPlaneParticleContactGenerator(const cPlaneParticleContactGenerator& other) = delete;
		cPlaneParticleContactGenerator& operator=(const cPlaneParticleContactGenerator& other) = delete;

		virtual ~cPlaneParticleContactGenerator();
		//Adds a Contact to the given contact structure

		virtual size_t AddContact(cParticleContact* contact, size_t limit, std::vector<cParticle*>& particles) const;
	};

	//TODO: Particle/Particle contact generator
	class cSphereSphereContactGenerator : public iParticleContactGenerator
	{
	public:
		cSphereSphereContactGenerator();
		cSphereSphereContactGenerator(const cSphereSphereContactGenerator& other) = delete;
		cSphereSphereContactGenerator& operator=(const cSphereSphereContactGenerator& other) = delete;

		virtual ~cSphereSphereContactGenerator();
		virtual size_t AddContact(cParticleContact* contact, size_t limit, std::vector<cParticle*>& particles) const;
	};
}