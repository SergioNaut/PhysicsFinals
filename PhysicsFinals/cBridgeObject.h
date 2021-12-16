#pragma once
#include <cParticle.h>
#include <cParticleRodConstraint.h>
#include <graphics/cGraphicsComponent.h>
#include <cParticleWorld.h>
#include <cObject.h>

class cBridgeObject : public cObject
{
public:
	//Keeping the unions because they are really practical
	union
	{
		struct
		{	
			//First Support
			nPhysics::cParticle* mParticleA;
			nPhysics::cParticle* mParticleB;
			nPhysics::cParticle* mParticleC;
			nPhysics::cParticle* mParticleD;
			nPhysics::cParticle* mParticleE;
			nPhysics::cParticle* mParticleF;
			nPhysics::cParticle* mParticleG;
			nPhysics::cParticle* mParticleH;

			//Middle bit
			nPhysics::cParticle* mParticleI;
			nPhysics::cParticle* mParticleJ;
			nPhysics::cParticle* mParticleK;
			nPhysics::cParticle* mParticleL;
			
			//Second Support
			nPhysics::cParticle* mParticleM;
			nPhysics::cParticle* mParticleN;
			nPhysics::cParticle* mParticleO;
			nPhysics::cParticle* mParticleP;
			nPhysics::cParticle* mParticleQ;
			nPhysics::cParticle* mParticleR;
			nPhysics::cParticle* mParticleS;
			nPhysics::cParticle* mParticleT;

		};
		nPhysics::cParticle* mParticles[20];
	};

	union
	{
		struct
		{
			//First Support
			nPhysics::cParticleRodConstraint* mConstraintAB;
			nPhysics::cParticleRodConstraint* mConstraintAD;
			nPhysics::cParticleRodConstraint* mConstraintAE;

			nPhysics::cParticleRodConstraint* mConstraintBC;
			nPhysics::cParticleRodConstraint* mConstraintBF;

			nPhysics::cParticleRodConstraint* mConstraintCD;
			nPhysics::cParticleRodConstraint* mConstraintCG;

			nPhysics::cParticleRodConstraint* mConstraintDH;

			nPhysics::cParticleRodConstraint* mConstraintEF;
			nPhysics::cParticleRodConstraint* mConstraintEH;
			nPhysics::cParticleRodConstraint* mConstraintFG;
			nPhysics::cParticleRodConstraint* mConstraintGH;

			//Middle bit
			nPhysics::cParticleCableConstraint* mConstraintAI;
			nPhysics::cParticleCableConstraint* mConstraintDJ;
			nPhysics::cParticleCableConstraint* mConstraintLM;
			nPhysics::cParticleCableConstraint* mConstraintKP;

			nPhysics::cParticleRodConstraint* mConstraintIJ;
			nPhysics::cParticleRodConstraint* mConstraintJK;
			nPhysics::cParticleRodConstraint* mConstraintKL;
			nPhysics::cParticleRodConstraint* mConstraintLI;

			nPhysics::cParticleRodConstraint* mConstraintIK;
			nPhysics::cParticleRodConstraint* mConstraintJL;


			//Second Support
			nPhysics::cParticleRodConstraint* mConstraintMN;
			nPhysics::cParticleRodConstraint* mConstraintMP;
			nPhysics::cParticleRodConstraint* mConstraintMQ;

			nPhysics::cParticleRodConstraint* mConstraintNO;
			nPhysics::cParticleRodConstraint* mConstraintNR;

			nPhysics::cParticleRodConstraint* mConstraintOP;
			nPhysics::cParticleRodConstraint* mConstraintOS;

			nPhysics::cParticleRodConstraint* mConstraintPT;

			nPhysics::cParticleRodConstraint* mConstraintQR;
			nPhysics::cParticleRodConstraint* mConstraintRS;
			nPhysics::cParticleRodConstraint* mConstraintST;
			nPhysics::cParticleRodConstraint* mConstraintTQ;


		};
		nPhysics::cParticleRodConstraint* mConstraints[34];
	};
	nGraphics::cGraphicsComponent* mSphereGraphics;
	nGraphics::cGraphicsComponent* mRodGraphics;

	cBridgeObject();
	virtual ~cBridgeObject();

	virtual void Begin();
	virtual void Render();
	virtual void End();
};