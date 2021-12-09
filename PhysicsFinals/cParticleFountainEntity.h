#pragma once

#include <cEntity.h>
#include <physics/cParticle.h>
#include <graphics/cGraphicsComponent.h>
#include <vector>


class cParticleFountainEntity : public cEntity
{
public:
	cParticleFountainEntity();
	virtual ~cParticleFountainEntity();
	virtual void BeginScene();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void EndScene();
protected:
	void CleanUpAllParticles();
	float mParticleRadius;
	glm::vec4 mParticleColor;
	std::vector<nPhysics::cParticle*> mParticles;
	nGraphics::cGraphicsComponent* mSphereGraphics;
};