#include <cBridgeObject.h>
#include <globalSetup.h>

cBridgeObject::cBridgeObject()
{
#pragma region ParticleSetup
	//First Base
	mParticleA = new nPhysics::cParticle(0.0f, glm::vec3(-10.0f, 20.0f, -5.0f));
	mParticleA->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));

	mParticleB = new nPhysics::cParticle(0.0f, glm::vec3(-10.0f, 20.0f, -10.0f));
	mParticleB->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));

	mParticleC = new nPhysics::cParticle(0.0f, glm::vec3(-15.0f, 20.0f, -10.0f));
	mParticleC->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));

	mParticleD = new nPhysics::cParticle(0.0f, glm::vec3(-15.0f, 20.0f, -5.0f));
	mParticleD->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));

	mParticleE = new nPhysics::cParticle(0.0f, glm::vec3(-10.0f, 2.0f, -5.0f));
	mParticleE->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));

	mParticleF = new nPhysics::cParticle(0.0f, glm::vec3(-10.0f, 2.0f, -10.0f));
	mParticleF->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));

	mParticleG = new nPhysics::cParticle(0.0f, glm::vec3(-15.0f, 2.0f, -10.0f));
	mParticleG->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));

	mParticleH = new nPhysics::cParticle(0.0f, glm::vec3(-15.0f, 2.0f, -5.0f));
	mParticleH->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));

	//MiddleBits

	mParticleI = new nPhysics::cParticle(2.0f, glm::vec3(0.0f, 12.0f, -5.0f));
	mParticleI->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));

	mParticleJ = new nPhysics::cParticle(2.0f, glm::vec3(0.0f, 12.0f, -10.0f));
	mParticleJ->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));

	mParticleK = new nPhysics::cParticle(2.0f, glm::vec3(5.0f, 12.0f, -10.0f));
	mParticleK->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));

	mParticleL = new nPhysics::cParticle(2.0f, glm::vec3(5.0f, 12.0f, -5.0f));
	mParticleL->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));

	//Second Base
	mParticleM = new nPhysics::cParticle(0.0f, glm::vec3(25.0f, 20.0f, -5.0f));
	mParticleM->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));

	mParticleN = new nPhysics::cParticle(0.0f, glm::vec3(25.0f, 20.0f, -10.0f));
	mParticleN->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));

	mParticleO = new nPhysics::cParticle(0.0f, glm::vec3(30.0f, 20.0f, -10.0f));
	mParticleO->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));

	mParticleP = new nPhysics::cParticle(0.0f, glm::vec3(30.0f, 20.0f, -5.0f));
	mParticleP->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));

	mParticleQ = new nPhysics::cParticle(0.0f, glm::vec3(25.0f, 2.0f , -5.0f));
	mParticleQ->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));

	mParticleR = new nPhysics::cParticle(0.0f, glm::vec3(25.0f, 2.0f, -10.0f));
	mParticleR->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));

	mParticleS = new nPhysics::cParticle(0.0f, glm::vec3(30.0f, 2.1f, -10.0f));
	mParticleS->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));

	mParticleT = new nPhysics::cParticle(0.0f, glm::vec3(30.0f, 2.1f, -5.0f));
	mParticleT->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));


#pragma endregion

#pragma region RodSetup
	//First Base
	mConstraintAB = new nPhysics::cParticleRodConstraint(mParticleA, mParticleB);
	mConstraintAD = new nPhysics::cParticleRodConstraint(mParticleA, mParticleD);
	mConstraintAE = new nPhysics::cParticleRodConstraint(mParticleA, mParticleE);

	mConstraintBC = new nPhysics::cParticleRodConstraint(mParticleB, mParticleC);
	mConstraintBF = new nPhysics::cParticleRodConstraint(mParticleB, mParticleF);

	mConstraintCD = new nPhysics::cParticleRodConstraint(mParticleC, mParticleD);
	mConstraintCG = new nPhysics::cParticleRodConstraint(mParticleC, mParticleG);

	mConstraintDH = new nPhysics::cParticleRodConstraint(mParticleD, mParticleH);

	mConstraintEF = new nPhysics::cParticleRodConstraint(mParticleE, mParticleF);
	mConstraintEH = new nPhysics::cParticleRodConstraint(mParticleE, mParticleH);
	mConstraintFG = new nPhysics::cParticleRodConstraint(mParticleF, mParticleG);
	mConstraintGH = new nPhysics::cParticleRodConstraint(mParticleG, mParticleH);

	//Middle Bits

	mConstraintAI = new nPhysics::cParticleCableConstraint(mParticleA, mParticleI);
	mConstraintDJ = new nPhysics::cParticleCableConstraint(mParticleD, mParticleJ);
	mConstraintLM = new nPhysics::cParticleCableConstraint(mParticleL, mParticleM);
	mConstraintKP = new nPhysics::cParticleCableConstraint(mParticleK, mParticleP);

	mConstraintIJ = new nPhysics::cParticleRodConstraint(mParticleI, mParticleJ);
	mConstraintJK = new nPhysics::cParticleRodConstraint(mParticleJ, mParticleK);
	mConstraintKL = new nPhysics::cParticleRodConstraint(mParticleK, mParticleL);
	mConstraintLI = new nPhysics::cParticleRodConstraint(mParticleL, mParticleI);

	//EXTRA SUPPORT FOR PLATFORM

	mConstraintIK = new nPhysics::cParticleRodConstraint(mParticleI, mParticleK);
	mConstraintJL = new nPhysics::cParticleRodConstraint(mParticleJ, mParticleL);


	//Second Base
	mConstraintMN = new nPhysics::cParticleRodConstraint(mParticleM, mParticleN);
	mConstraintMP = new nPhysics::cParticleRodConstraint(mParticleM, mParticleP);
	mConstraintMQ = new nPhysics::cParticleRodConstraint(mParticleM, mParticleQ);

	mConstraintNO = new nPhysics::cParticleRodConstraint(mParticleN, mParticleO);
	mConstraintNR = new nPhysics::cParticleRodConstraint(mParticleN, mParticleR);

	mConstraintOP = new nPhysics::cParticleRodConstraint(mParticleO, mParticleP);
	mConstraintOS = new nPhysics::cParticleRodConstraint(mParticleO, mParticleS);

	mConstraintPT = new nPhysics::cParticleRodConstraint(mParticleP, mParticleT);

	mConstraintQR = new nPhysics::cParticleRodConstraint(mParticleQ, mParticleR);
	mConstraintRS = new nPhysics::cParticleRodConstraint(mParticleR, mParticleS);
	mConstraintST = new nPhysics::cParticleRodConstraint(mParticleS, mParticleT);
	mConstraintTQ = new nPhysics::cParticleRodConstraint(mParticleT, mParticleQ);

#pragma endregion

	{
		nGraphics::sGraphicsComponentDef graphicsDef;
		graphicsDef.Mesh = "sphere";
		graphicsDef.TexDiffuse = "metal";
		glm::set(graphicsDef.ModelColor, 1.0f, 0.0f, 0.0f, 1.0f);
		glm::set(graphicsDef.Position, 0.0f, 1.0f, 0.0f);
		glm::set(graphicsDef.Scale, 1.0f, 1.0f, 1.0f);
		mSphereGraphics = new nGraphics::cGraphicsComponent(graphicsDef);
	}
	{
		nGraphics::sGraphicsComponentDef graphicsDef;
		graphicsDef.Mesh = "cylinder";
		graphicsDef.TexDiffuse = "metal";
		glm::set(graphicsDef.ModelColor, 1.0f, 0.0f, 0.0f, 1.0f);
		glm::set(graphicsDef.Position, 0.0f, 1.0f, 0.0f);
		glm::set(graphicsDef.Scale, 1.0f, 1.0f, 1.0f);
		mRodGraphics = new nGraphics::cGraphicsComponent(graphicsDef);
	}
}

cBridgeObject::~cBridgeObject()
{
	//Destroys all particles
	for (size_t i = 0; i < 20; i++)
	{
		delete mParticles[i];
	}
	//Destroys all rods
	for (size_t i = 0; i < 34; i++)
	{
		delete mConstraints[i];
	}
}

void cBridgeObject::Begin()
{
	//Adds all particles
	for (size_t i = 0; i < 20; i++)
	{
		particleWorld->AddParticle(mParticles[i]);
	}
	//Adds all rods
	for (size_t i = 0; i < 34; i++)
	{
		particleWorld->AddContactContactGenerator(mConstraints[i]);
	}
}

void cBridgeObject::Render()
{
	//Render all particles
	for (size_t i = 0; i < 20; i++)
	{
		sphereGraphics->GetVars()->ModelMatrix = glm::translate(glm::mat4(1.0f), mParticles[i]->GetPosition());
		sphereGraphics->GetVars()->ModelColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		sphereGraphics->Render();
	}
#pragma region FirstBase

	tubeGraphics->RenderCylinder(mParticleA->GetPosition(), mParticleB->GetPosition(), 0.5f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	tubeGraphics->RenderCylinder(mParticleA->GetPosition(), mParticleD->GetPosition(), 0.5f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	tubeGraphics->RenderCylinder(mParticleA->GetPosition(), mParticleE->GetPosition(), 0.5f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	tubeGraphics->RenderCylinder(mParticleB->GetPosition(), mParticleC->GetPosition(), 0.5f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	tubeGraphics->RenderCylinder(mParticleB->GetPosition(), mParticleF->GetPosition(), 0.5f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	tubeGraphics->RenderCylinder(mParticleC->GetPosition(), mParticleD->GetPosition(), 0.5f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	tubeGraphics->RenderCylinder(mParticleC->GetPosition(), mParticleG->GetPosition(), 0.5f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	tubeGraphics->RenderCylinder(mParticleD->GetPosition(), mParticleH->GetPosition(), 0.5f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	tubeGraphics->RenderCylinder(mParticleE->GetPosition(), mParticleF->GetPosition(), 0.5f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	tubeGraphics->RenderCylinder(mParticleE->GetPosition(), mParticleH->GetPosition(), 0.5f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	tubeGraphics->RenderCylinder(mParticleF->GetPosition(), mParticleG->GetPosition(), 0.5f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	tubeGraphics->RenderCylinder(mParticleG->GetPosition(), mParticleH->GetPosition(), 0.5f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));

#pragma endregion

#pragma region MiddleBits

	//Cables don't work visually
	/*tubeGraphics->RenderCylinder(mParticleI->GetPosition(), mParticleA->GetPosition(), 0.3f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	tubeGraphics->RenderCylinder(mParticleJ->GetPosition(), mParticleB->GetPosition(), 0.3f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	tubeGraphics->RenderCylinder(mParticleL->GetPosition(), mParticleM->GetPosition(), 0.3f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	tubeGraphics->RenderCylinder(mParticleK->GetPosition(), mParticleP->GetPosition(), 0.3f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));*/

	//Rods
	tubeGraphics->RenderCylinder(mParticleI->GetPosition(), mParticleL->GetPosition(), 0.3f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	tubeGraphics->RenderCylinder(mParticleL->GetPosition(), mParticleK->GetPosition(), 0.3f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	tubeGraphics->RenderCylinder(mParticleK->GetPosition(), mParticleJ->GetPosition(), 0.3f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	tubeGraphics->RenderCylinder(mParticleJ->GetPosition(), mParticleI->GetPosition(), 0.3f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	//Looks like a little platform 
	tubeGraphics->RenderCylinder(mParticleI->GetPosition(), mParticleK->GetPosition(), 0.1f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.6f, 0.0f, 0.6f));


#pragma endregion

#pragma region SecondBase
	tubeGraphics->RenderCylinder(mParticleM->GetPosition(), mParticleN->GetPosition(), 0.8f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	tubeGraphics->RenderCylinder(mParticleM->GetPosition(), mParticleP->GetPosition(), 0.8f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	tubeGraphics->RenderCylinder(mParticleM->GetPosition(), mParticleQ->GetPosition(), 0.8f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	tubeGraphics->RenderCylinder(mParticleN->GetPosition(), mParticleO->GetPosition(), 0.8f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	tubeGraphics->RenderCylinder(mParticleN->GetPosition(), mParticleR->GetPosition(), 0.8f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	tubeGraphics->RenderCylinder(mParticleO->GetPosition(), mParticleP->GetPosition(), 0.8f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	tubeGraphics->RenderCylinder(mParticleO->GetPosition(), mParticleS->GetPosition(), 0.8f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	tubeGraphics->RenderCylinder(mParticleP->GetPosition(), mParticleT->GetPosition(), 0.8f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	//A couple cylinders here aren't showing up, for some reason
	tubeGraphics->RenderCylinder(mParticleQ->GetPosition(), mParticleR->GetPosition(), 0.8f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	tubeGraphics->RenderCylinder(mParticleR->GetPosition(), mParticleS->GetPosition(), 0.8f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//This 2 cylinders don't render when the particles don't have mass
	// One starts appearing if I rise the variable of the particles a little bit
	//TODO: Find out why
	tubeGraphics->RenderCylinder(mParticleS->GetPosition(), mParticleT->GetPosition(), 0.8f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	tubeGraphics->RenderCylinder(mParticleT->GetPosition(), mParticleQ->GetPosition(), 0.8f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
#pragma endregion
}

void cBridgeObject::End()
{
	//Remove all particles
	for (size_t i = 0; i < 20; i++)
	{
		particleWorld->RemoveParticle(mParticles[i]);
	}
	//Remove all rods
	for (size_t i = 0; i < 34; i++)
	{
		particleWorld->RemoveContactContactGenerator(mConstraints[i]);
	}
}