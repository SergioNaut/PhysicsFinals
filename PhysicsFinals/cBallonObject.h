#pragma once
#include <cParticle.h>
#include <cParticleRodConstraint.h>
#include <graphics/cGraphicsComponent.h>
#include <cParticleWorld.h>
#include <cObject.h>


//Will work as a ballon?
class cBallonObject : public cObject
{
public:
	//Keeping the unions because they are really practical
	union
	{
		struct
		{
			nPhysics::cParticle* mParticleA;
			nPhysics::cParticle* mParticleB;
			nPhysics::cParticle* mParticleC;
			nPhysics::cParticle* mParticleD;
			nPhysics::cParticle* mParticleE;
		};
		nPhysics::cParticle* mParticles[5];
	};

	union
	{
		struct
		{
			
			nPhysics::cParticleCableConstraint* mConstraintAB;

			nPhysics::cParticleCableConstraint* mConstraintBD;
			nPhysics::cParticleCableConstraint* mConstraintBC;
			nPhysics::cParticleCableConstraint* mConstraintBE;

		};
		nPhysics::cParticleRodConstraint* mConstraints[4];
	};
	nGraphics::cGraphicsComponent* mSphereGraphics;
	nGraphics::cGraphicsComponent* mRodGraphics;

	cBallonObject();
	virtual ~cBallonObject();

	virtual void Begin();
	virtual void Render();
	virtual void End();
};
