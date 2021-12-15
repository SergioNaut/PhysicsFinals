#include <cBoxObject.h>
#include <globalSetup.h>

cBoxObject::cBoxObject()
{
#pragma region ParticleSetup
	mParticleA = new nPhysics::cParticle(2.0f, glm::vec3(-10.0f, 10.0f, 0.0f));
	mParticleA->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));
	

	mParticleB = new nPhysics::cParticle(2.0f, glm::vec3(-10.0f, 10.0f, -5.0f));
	mParticleB->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));

	mParticleC = new nPhysics::cParticle(2.0f, glm::vec3(-5.0f, 10.0f, -5.0f));
	mParticleC->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));

	mParticleD = new nPhysics::cParticle(2.0f, glm::vec3(-5.0f, 10.0f, 0.0f));
	mParticleD->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));

	mParticleE = new nPhysics::cParticle(2.0f, glm::vec3(-10.0f, 5.0f, 0.0f));
	mParticleE->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));

	mParticleF = new nPhysics::cParticle(2.0f, glm::vec3(-10.0f, 5.0f, -5.0f));
	mParticleF->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));

	mParticleG = new nPhysics::cParticle(2.0f, glm::vec3(-5.0f, 5.0f, -5.0f));
	mParticleG->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));

	mParticleH = new nPhysics::cParticle(2.0f, glm::vec3(-5.0f, 5.0f, 0.0f));
	mParticleH->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));

#pragma endregion

#pragma region RodSetup
	//Top Rods
	mConstraintAB = new nPhysics::cParticleRodConstraint(mParticleA, mParticleB);
	mConstraintAD = new nPhysics::cParticleRodConstraint(mParticleA, mParticleD);
	mConstraintAE = new nPhysics::cParticleRodConstraint(mParticleA, mParticleE);
	
	mConstraintBC = new nPhysics::cParticleRodConstraint(mParticleB, mParticleC);
	mConstraintBF = new nPhysics::cParticleRodConstraint(mParticleB, mParticleF);

	mConstraintCD = new nPhysics::cParticleRodConstraint(mParticleC, mParticleD);
	mConstraintCG = new nPhysics::cParticleRodConstraint(mParticleC, mParticleG);

	mConstraintDH = new nPhysics::cParticleRodConstraint(mParticleD, mParticleH);

	//Bottom Rods
	mConstraintEF = new nPhysics::cParticleRodConstraint(mParticleE, mParticleF);
	mConstraintEH = new nPhysics::cParticleRodConstraint(mParticleE, mParticleH);
	mConstraintFG = new nPhysics::cParticleRodConstraint(mParticleF, mParticleG);
	mConstraintGH = new nPhysics::cParticleRodConstraint(mParticleG, mParticleH);
#pragma endregion

	{
		nGraphics::sGraphicsComponentDef graphicsDef;
		graphicsDef.Mesh = "sphere";
		graphicsDef.TexDiffuse = "metal";
		glm::set(graphicsDef.ModelColor, 1.0f, 1.0f, 1.0f, 1.0f);
		glm::set(graphicsDef.Position, 0.0f, 1.0f, 0.0f);
		glm::set(graphicsDef.Scale, 1.0f, 1.0f, 1.0f);
		sphereGraphics = new nGraphics::cGraphicsComponent(graphicsDef);
	}
	{
		nGraphics::sGraphicsComponentDef graphicsDef;
		graphicsDef.Mesh = "cylinder";
		graphicsDef.TexDiffuse = "metal";
		glm::set(graphicsDef.ModelColor, 1.0f, 1.0f, 1.0f, 1.0f);
		glm::set(graphicsDef.Position, 0.0f, 1.0f, 0.0f);
		glm::set(graphicsDef.Scale, 1.0f, 1.0f, 1.0f);
		tubeGraphics = new nGraphics::cGraphicsComponent(graphicsDef);
	}
}

cBoxObject::~cBoxObject()
{
	//Destroys all particles
	for (size_t i = 0; i < 8; i++)
	{
		delete mParticles[i];
	}
	//Destroys all rods
	for (size_t i = 0; i < 12; i++)
	{
		delete mConstraints[i];
	}
}

void cBoxObject::Begin()
{
	//Adds all particles
	for (size_t i = 0; i < 8; i++)
	{
		particleWorld->AddParticle(mParticles[i]);
	}
	//Adds all rods
	for (size_t i = 0; i < 12; i++)
	{
		particleWorld->AddContactContactGenerator(mConstraints[i]);
	}
}

void cBoxObject::Render()
{
	//Render all particles
	for (size_t i = 0; i < 8; i++)
	{
		sphereGraphics->GetVars()->ModelMatrix = glm::translate(glm::mat4(1.0f), mParticles[i]->GetPosition());
		sphereGraphics->GetVars()->ModelColor = glm::vec4(1.0f, 1.0f, 1.0f,1.0f);
		sphereGraphics->Render();
	}
	//Super dumb way but I hope it works
	tubeGraphics->RenderCylinder(mParticleA->GetPosition(), mParticleB->GetPosition(), 0.3f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	tubeGraphics->RenderCylinder(mParticleA->GetPosition(), mParticleD->GetPosition(), 0.3f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	tubeGraphics->RenderCylinder(mParticleA->GetPosition(), mParticleE->GetPosition(), 0.3f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	tubeGraphics->RenderCylinder(mParticleB->GetPosition(), mParticleC->GetPosition(), 0.3f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	tubeGraphics->RenderCylinder(mParticleB->GetPosition(), mParticleF->GetPosition(), 0.3f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	tubeGraphics->RenderCylinder(mParticleC->GetPosition(), mParticleD->GetPosition(), 0.3f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	tubeGraphics->RenderCylinder(mParticleC->GetPosition(), mParticleG->GetPosition(), 0.3f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	tubeGraphics->RenderCylinder(mParticleD->GetPosition(), mParticleH->GetPosition(), 0.3f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	tubeGraphics->RenderCylinder(mParticleE->GetPosition(), mParticleF->GetPosition(), 0.3f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	tubeGraphics->RenderCylinder(mParticleE->GetPosition(), mParticleH->GetPosition(), 0.3f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	tubeGraphics->RenderCylinder(mParticleF->GetPosition(), mParticleG->GetPosition(), 0.3f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	tubeGraphics->RenderCylinder(mParticleG->GetPosition(), mParticleH->GetPosition(), 0.3f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));

}

void cBoxObject::End()
{
	//Remove all particles
	for (size_t i = 0; i < 8; i++)
	{
		particleWorld->RemoveParticle(mParticles[i]);
	}
	//Remove all rods
	for (size_t i = 0; i < 12; i++)
	{
		particleWorld->RemoveContactContactGenerator(mConstraints[i]);
	}
}