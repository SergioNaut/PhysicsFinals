#pragma once
#include <cParticle.h>
#include <cParticleRodConstraint.h>
#include <graphics/cGraphicsComponent.h>
#include <cParticleWorld.h>
#include <cObject.h>

class cBoxObject : public cObject
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
			nPhysics::cParticle* mParticleF;
			nPhysics::cParticle* mParticleG;
			nPhysics::cParticle* mParticleH;
		};
		nPhysics::cParticle* mParticles[8];
	};

	union
	{
		struct
		{
			//Top Rods
			nPhysics::cParticleRodConstraint* mConstraintAB;
			nPhysics::cParticleRodConstraint* mConstraintAD;
			nPhysics::cParticleRodConstraint* mConstraintAE;

			nPhysics::cParticleRodConstraint* mConstraintBC;
			nPhysics::cParticleRodConstraint* mConstraintBF;

			nPhysics::cParticleRodConstraint* mConstraintCD;
			nPhysics::cParticleRodConstraint* mConstraintCG;

			nPhysics::cParticleRodConstraint* mConstraintDH;

			//Bottom Rods

			nPhysics::cParticleRodConstraint* mConstraintEF;
			nPhysics::cParticleRodConstraint* mConstraintEH;
			nPhysics::cParticleRodConstraint* mConstraintFG;
			nPhysics::cParticleRodConstraint* mConstraintGH;
		};
		nPhysics::cParticleRodConstraint* mConstraints[12];
	};
	nGraphics::cGraphicsComponent* mSphereGraphics;
	nGraphics::cGraphicsComponent* mRodGraphics;

	cBoxObject();
	virtual ~cBoxObject();

	virtual void Begin();
	//TODO: Remove Update?
	//virtual void Update(float deltaTime);
	virtual void Render();
	virtual void End();
};