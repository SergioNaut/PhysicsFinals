#include <cBallonObject.h>
#include <globalSetup.h>

cBallonObject::cBallonObject()
{
#pragma region ParticleSetup
	//TODO: Set Mass for particle A?
	mParticleA = new nPhysics::cParticle(0.0f, glm::vec3(10.0f, 1.0f, 20.0f));
	mParticleA->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));

	//Floaty bits
	mParticleB = new nPhysics::cParticle(2.0f, glm::vec3(10.0f, 12.0f, 20.0f));
	mParticleB->SetAcceleration(glm::vec3(0.0f, 5.0f, 0.0f));

	mParticleC = new nPhysics::cParticle(2.0f, glm::vec3(10.0f, 12.0f, 24.0f));
	mParticleC->SetAcceleration(glm::vec3(0.0f, 3.0f, 0.0f));

	mParticleD = new nPhysics::cParticle(2.0f, glm::vec3(8.0f, 12.0f, 18.0f));
	mParticleD->SetAcceleration(glm::vec3(0.0f, 6.0f, 0.0f));

	mParticleE = new nPhysics::cParticle(2.0f, glm::vec3(13.0f, 7.0f, 15.0f));
	mParticleE->SetAcceleration(glm::vec3(0.0f, 11.0f, 0.0f));

#pragma endregion

#pragma region CableSetup

	mConstraintAB = new nPhysics::cParticleCableConstraint(mParticleA, mParticleB);
	mConstraintBC = new nPhysics::cParticleCableConstraint(mParticleB, mParticleC);
	mConstraintBD = new nPhysics::cParticleCableConstraint(mParticleB, mParticleD);
	mConstraintBE = new nPhysics::cParticleCableConstraint(mParticleB, mParticleE);
	
#pragma endregion

	{
		nGraphics::sGraphicsComponentDef graphicsDef;
		graphicsDef.Mesh = "sphere";
		graphicsDef.TexDiffuse = "roald";
		glm::set(graphicsDef.ModelColor, 1.0f, 1.0f, 1.0f, 1.0f);
		glm::set(graphicsDef.Position, 0.0f, 1.0f, 0.0f);
		glm::set(graphicsDef.Scale, 2.0f, 2.0f, 2.0f);
		mSphereGraphics = new nGraphics::cGraphicsComponent(graphicsDef);
	}
}

cBallonObject::~cBallonObject()
{
	//Destroys all particles
	for (size_t i = 0; i < 5; i++)
	{
		delete mParticles[i];
	}
	//Destroys all rods
	for (size_t i = 0; i < 4; i++)
	{
		delete mConstraints[i];
	}
}

void cBallonObject::Begin()
{
	//Adds all particles
	for (size_t i = 0; i < 5; i++)
	{
		particleWorld->AddParticle(mParticles[i]);
	}
	//Adds all rods
	for (size_t i = 0; i < 4; i++)
	{
		particleWorld->AddContactContactGenerator(mConstraints[i]);
	}
}

void cBallonObject::Render()
{
	//Render all particles
	for (size_t i = 0; i < 5; i++)
	{
		mSphereGraphics->GetVars()->ModelMatrix = glm::translate(glm::mat4(1.0f), mParticles[i]->GetPosition());
		mSphereGraphics->GetVars()->ModelColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		mSphereGraphics->Render();
	}
	//No rendering cables because this breaks everything

}

void cBallonObject::End()
{
	//Remove all particles
	for (size_t i = 0; i < 5; i++)
	{
		particleWorld->RemoveParticle(mParticles[i]);
	}
	//Remove all rods
	for (size_t i = 0; i < 4; i++)
	{
		particleWorld->RemoveContactContactGenerator(mConstraints[i]);
	}
}