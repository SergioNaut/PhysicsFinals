#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <math.h>

#include <graphics/graphics.h>
#include <input/input.h>
#include <graphics/cCamera.h>
#include <graphics/c3rdPersonCamera.h>
#include <graphics/cGraphicsComponent.h>
#include <cParticleWorld.h>
#include <particle_contact_generators.h>
#include <globalSetup.h>

//Create a file for all objects
#include <cBoxObject.h>
#include <cBridgeObject.h>
#include <cBallonObject.h>

void mainLoop();

int main()
{
	//A million things were moved to globalSetup
	
	if (!StartGraphics())
	{
	return -1;
	}

	if (!StartPhysics())
	{
		return -1;
	}

	//Calls the main loop
	mainLoop();

	// Clean up
	EndPhysics();
	EndGraphics();

	return 0;
}

#pragma region RotationBits
glm::mat3 yawMatrix(float yaw)
{
	return glm::mat3(cos(yaw), sin(yaw), 0, -sin(yaw), cos(yaw), 0, 0, 0, 1);
}

glm::mat3 pitchMatrix(float pitch)
{
	return glm::mat3(cos(pitch), 0, -sin(pitch), 0, 1, 0, sin(pitch), 0, cos(pitch));
}

glm::mat3 rotationMatrix(float yaw, float pitch)
{
	return yawMatrix(yaw) * pitchMatrix(pitch);
}
#pragma endregion

void mainLoop()
{
	nInput::gInputManager->ClearState();

	nGraphics::Focus();

	bool continueMainLoop = true;

	float previousTime = static_cast<float>(glfwGetTime());

	float fpsFrameCount = 0.f;
	float fpsTimeElapsed = 0.f;

	//Setup cannon
#pragma region CannonStuff
	float cannonYaw = 0.3f;
	float cannonPitch = 10.0f;
	float* pCannonYaw = &cannonYaw;
	float* pCannonPitch = &cannonPitch;
	float minYaw = -2.0f;
	float maxYaw = 2.0f;
	float minPitch = 0.5f;
	float maxPitch = 26.0f;
#pragma endregion

	// BEGIN PROJECT 3 SETUP
	std::vector<nPhysics::cParticle*> particles;
	//OLD WORLD
	//nPhysics::cParticleWorld* world = new nPhysics::cParticleWorld(100, 0);
	//Particle variables
	glm::vec4 particleColor(1.0f, 1.0f, 1.0f, 1.0f);
	float particleRadius(1.0f);
#pragma region SphereSphereContacts!
	nPhysics::cSphereSphereContactGenerator sphereCollider;
	particleWorld->AddContactContactGenerator(&sphereCollider);
#pragma endregion

#pragma region Planes
	//Planes have some values commented because I'm using this project to test things for the finals so it has some things from the finals

	//Ground Plane
	nPhysics::cPlaneParticleContactGenerator particleContactGeneratorGround(glm::vec3(0.0f,/*0.2f*/ 1.0f, 0.0f), 1.0f, 1.0f);
	particleWorld->AddContactContactGenerator(&particleContactGeneratorGround);

	//Left Wall
	nPhysics::cPlaneParticleContactGenerator particleContactGeneratorLeft(glm::vec3(1.0f, 0.f, 0.0f),-40.0f, 1.0f);
	particleWorld->AddContactContactGenerator(&particleContactGeneratorLeft);

	//Right Wall
	nPhysics::cPlaneParticleContactGenerator particleContactGeneratorRight(glm::vec3(-1.0f, 0.f, 0.0f),-40.0f, 1.0f);
	particleWorld->AddContactContactGenerator(&particleContactGeneratorRight);

	//Back Wall
	nPhysics::cPlaneParticleContactGenerator particleContactGeneratorBack(glm::vec3(0.0f, 0.f, -2.0f),-40.0f, 1.0f);
	particleWorld->AddContactContactGenerator(&particleContactGeneratorBack);

	//Front Wall
	nPhysics::cPlaneParticleContactGenerator particleContactGeneratorFront(glm::vec3(0.0f, 0.f, 1.0f),-40.0f, 1.0f);
	particleWorld->AddContactContactGenerator(&particleContactGeneratorFront);
#pragma endregion

#pragma region Objects
	cBoxObject* box1 = new cBoxObject();
	objects.push_back(box1);

	cBridgeObject* bridge1 = new cBridgeObject();
	objects.push_back(bridge1);

	cBallonObject* ballons = new cBallonObject();
	objects.push_back(ballons);

	for (cObject* object : objects)
	{
		object->Begin();
	}
#pragma endregion


#pragma region KeySetup
	nInput::cKey* wKey = nInput::cInputManager::GetInstance()->ListenToKey(nInput::KeyCode::KEY_W);
	nInput::cKey* aKey = nInput::cInputManager::GetInstance()->ListenToKey(nInput::KeyCode::KEY_A);
	nInput::cKey* sKey = nInput::cInputManager::GetInstance()->ListenToKey(nInput::KeyCode::KEY_S);
	nInput::cKey* dKey = nInput::cInputManager::GetInstance()->ListenToKey(nInput::KeyCode::KEY_D);
	
	nInput::cKey* key1 = nInput::cInputManager::GetInstance()->ListenToKey(nInput::KeyCode::KEY_1);
	nInput::cKey* key2 = nInput::cInputManager::GetInstance()->ListenToKey(nInput::KeyCode::KEY_2);
	nInput::cKey* key3 = nInput::cInputManager::GetInstance()->ListenToKey(nInput::KeyCode::KEY_3);
#pragma endregion

	while (continueMainLoop)
	{
		float currentTime = static_cast<float>(glfwGetTime());
		float deltaTime = currentTime - previousTime;
		previousTime = currentTime;

		// FPS TITLE STUFF
		// Kept from the class code because I like knowing the framerate since my pc lags ocasionally while testing
		{
			fpsTimeElapsed += deltaTime;
			fpsFrameCount += 1.0f;
			if (fpsTimeElapsed >= 0.03f)
			{
				std::string fps = std::to_string(fpsFrameCount / fpsTimeElapsed);
				std::string ms = std::to_string(1000.f * fpsTimeElapsed / fpsFrameCount);
				std::string newTitle = "FPS: " + fps + "   MS: " + ms;
				nGraphics::SetWindowTitle(newTitle);
				// reset times and counts
				fpsTimeElapsed = 0.f;
				fpsFrameCount = 0.f;
			}
		}

		if (key1->IsJustPressed())
		{
			glm::mat3 rotMat = rotationMatrix(cannonYaw, cannonPitch);
			nPhysics::cParticle* particleP = new nPhysics::cParticle(projectileConfig.projectiles.mass1, glm::vec3(0.f, /*1.5f*/5.0f, 0.f));
			particleP->SetMass(projectileConfig.projectiles.mass1);
			particleP->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));
			//Change velocity with rotMat
			glm::vec3 randomVelocity((rotMat[0] * 3.0f) + (rotMat[1] * 10.0f) + (rotMat[2] * 3.0f));
			particleP->SetVelocity(randomVelocity);
			particleWorld->AddParticle(particleP);
			particles.push_back(particleP);
		}
		if (key2->IsJustPressed())
		{
			glm::mat3 rotMat = rotationMatrix(cannonYaw, cannonPitch);
			nPhysics::cParticle* particleP = new nPhysics::cParticle(projectileConfig.projectiles.mass2, glm::vec3(0.f, /*1.5f*/5.0f, 0.f));
			particleP->SetMass(projectileConfig.projectiles.mass2);
			particleP->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));
			//Change velocity with rotMat
			glm::vec3 randomVelocity((rotMat[0] * 3.0f) + (rotMat[1] * 10.0f) + (rotMat[2] * -3.0f));
			particleP->SetVelocity(randomVelocity);
			particleWorld->AddParticle(particleP);
			particles.push_back(particleP);
		}
		if (key3->IsJustPressed())
		{
			glm::mat3 rotMat = rotationMatrix(cannonYaw, cannonPitch);
			nPhysics::cParticle* particleP = new nPhysics::cParticle(projectileConfig.projectiles.mass3, glm::vec3(0.f, /*1.5f*/5.0f, 0.f));
			particleP->SetMass(projectileConfig.projectiles.mass3);
			particleP->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));
			//Change velocity with rotMat
			glm::vec3 randomVelocity((rotMat[0] * -10.0f) + (rotMat[1] * 20.0f) + (rotMat[2] * 3.0f));
			particleP->SetVelocity(randomVelocity);
			particleWorld->AddParticle(particleP);
			particles.push_back(particleP);
		}

		else if (aKey->IsJustPressed())
		{
			if (cannonPitch < maxPitch)
			{
				cannonPitch += 1.0f;
			}
			if (cannonPitch > maxPitch)
			{
				cannonPitch = maxPitch;
			}
			std::cout << cannonPitch << std::endl;
		}
		else if (sKey->IsJustPressed())
		{
			if (cannonYaw > minYaw)
			{
				cannonYaw -= 0.3f;
			}
			if (cannonYaw < minYaw)
			{
				cannonYaw = minYaw;
			}
			std::cout << cannonYaw << std::endl;
		}
		else if (dKey->IsJustPressed())
		{
			if (cannonPitch > minPitch)
			{
				cannonPitch -= 1.0f;
			}
			if (cannonPitch < minPitch)
			{
				cannonPitch = minPitch;
			}
			std::cout << cannonPitch << std::endl;
		}
		else if (wKey->IsJustPressed())
		{
			if (cannonYaw < maxYaw)
			{
				cannonYaw += 0.3f;
			}
			if (cannonYaw > maxYaw)
			{
				cannonYaw = maxYaw;
			}
			std::cout << cannonYaw << std::endl;
		}


		particleWorld->TimeStep(deltaTime);

		// Safety, mostly for first frame
		if (deltaTime == 0.f)
		{
			deltaTime = 0.03f;
		}

		// update the camera
		camera->Update(deltaTime);

		// Clear inputs
		nInput::gInputManager->ClearState();

		// begin setting per-frame vars
		camera->GetEyePosition(PerFrameVars.EyePosition);
		camera->GetViewMatrix(PerFrameVars.ViewMatrix);
		camera->GetProjectionMatrix(PerFrameVars.ProjectionMatrix);
		// end setting per-frame vars

		nGraphics::BeginFrame(PerFrameVars);

		//Render objects
		for (cObject* object : objects)
		{
			object->Render();
		}

		// Graphical Item rendering
		skyboxGraphics->Render();
		planeGraphics->Render();
		wallGraphics1->Render();
		wallGraphics2->Render();
		wallGraphics3->Render();
		wallGraphics4->Render();

		// render the particles
		//Using the projectileMatrix from midterms
		for (nPhysics::cParticle* p : particles )
		{
				glm::mat4 projectileMatrix(1.0f);
				projectileMatrix = glm::translate(projectileMatrix, p->GetPosition());
				//projectileMatrix = glm::scale(projectileMatrix, glm::vec3(p->GetRadius()));
				
				//This is soooo gross
				if (projectileConfig.projectiles.mass1 - p->GetTrueMass() <= 0.01 && projectileConfig.projectiles.mass1 - p->GetTrueMass() >= 0)
				{
					projectileMatrix = glm::scale(projectileMatrix, glm::vec3(projectileConfig.projectiles.radius1));
					projectileGraphics1->GetVars()->ModelMatrix = projectileMatrix;
					projectileGraphics1->GetVars()->ModelColor = glm::vec4(0.5f, 0.9f, 1.0f, 1.0f);
					projectileGraphics1->Render();
				}

				if (projectileConfig.projectiles.mass2 - p->GetTrueMass() <= 0.01 && projectileConfig.projectiles.mass2 - p->GetTrueMass() >=0)
				{
					projectileMatrix = glm::scale(projectileMatrix, glm::vec3(projectileConfig.projectiles.radius2));
					projectileGraphics2->GetVars()->ModelMatrix = projectileMatrix;
					projectileGraphics2->GetVars()->ModelColor = glm::vec4(1.0f, 0.2f, 0.7f, 1.0f);
					projectileGraphics2->Render();
				}

				if ( projectileConfig.projectiles.mass3 - p->GetTrueMass() <= 0.01 && projectileConfig.projectiles.mass3 - p->GetTrueMass() >= 0)
				{
					projectileMatrix = glm::scale(projectileMatrix, glm::vec3(projectileConfig.projectiles.radius3));
					projectileGraphics3->GetVars()->ModelMatrix = projectileMatrix;
					projectileGraphics3->GetVars()->ModelColor = glm::vec4(1.0f,0.0f,0.0f,1.0f);
					projectileGraphics3->Render();
				}
		}
		// end Graphical Item rendering

		nGraphics::EndFrame();
		//No need to delete the particles

		// Exit conditions: press escape or close the window by the 'x' button
		if (!(nInput::IsKeyUp::Escape() && !nGraphics::WindowShouldClose()))
		{
			continueMainLoop = false;
		}
	}
	for (cObject* object : objects)
	{
		object->End();
	}
	for (cObject* object : objects)
	{
		delete object;
	}
}
