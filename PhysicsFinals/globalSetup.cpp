#include <globalSetup.h>
#include <input/input.h>
#include<graphics/graphics.h>
#include <graphics/cMeshManager.h>
#include <iostream>


#pragma region CameraSetup
nGraphics::sPerFrameVars PerFrameVars;
nGraphics::c3rdPersonCamera* camera = 0;
#pragma endregion

#pragma region GraphicsStuff
//Add sphere and tube
nGraphics::cGraphicsComponent* skyboxGraphics = 0;
nGraphics::cGraphicsComponent* planeGraphics = 0;
nGraphics::cGraphicsComponent* rockGraphics = 0;

nGraphics::cGraphicsComponent* wallGraphics1 = 0;
nGraphics::cGraphicsComponent* wallGraphics2 = 0;
nGraphics::cGraphicsComponent* wallGraphics3 = 0;
nGraphics::cGraphicsComponent* wallGraphics4 = 0;
#pragma endregion

nPhysics::cParticleWorld* particleWorld = 0;
std::vector<cObject*> objects;

#pragma region SetupFunctions

bool StartPhysics()
{
	//Checks if there's a World already
	if (particleWorld)
	{
		//There's already a world
		return false;
	}
	particleWorld = new nPhysics::cParticleWorld(100);
	return true;
}

bool StartGraphics()
{
	//Check if there's a camera already
	if (camera)
	{
		return false;
	}
	else
	{
		camera = new nGraphics::c3rdPersonCamera();
		nGraphics::SetCamera(camera);
		glm::mat4 identity(1.f);
		camera->SetTargetTransform(identity);
	}

	//Init Graphics and input
	if (!nGraphics::Init())
	{
		std::cout << "Error Setting up Graphics" << std::endl;
		system("pause");
		return -1;
	}
	if (!nInput::Init())
	{
		std::cout << "Error Setting up Inputs" << std::endl;
		system("pause");
		return -1;
	}

#pragma region Textures
	// Loading textures to use with our meshes
	// TODO: Add more stuff (metal texture)
	nGraphics::gTextureManager->Load("../Assets/WhiteSquare.bmp", "whiteSquare", false);
	nGraphics::gTextureManager->Load("../Assets/stone_wall.bmp", "stone", false);
	nGraphics::gTextureManager->Load("../Assets/grafitti.bmp", "grafitti", false);
	nGraphics::gTextureManager->Load("../Assets/white.bmp", "white", false);
	nGraphics::gTextureManager->Load("../Assets/brickwall.bmp", "bricks", false);
	nGraphics::gTextureManager->Load("../Assets/roald.bmp", "roald", false);
#pragma endregion

#pragma region LoadingMeshes
	//TODO:Add more stuff
	// Loading meshes
	std::vector<nGraphics::sMeshLoadingInfo> infos;
	nGraphics::sMeshLoadingInfo loadingInfo;

	// Skybox sphere mesh
	loadingInfo.File = "../Assets/Isoshphere_xyz_InvertedNormals.ply";
	loadingInfo.DoResize = false;
	loadingInfo.AddSubMesh("skybox");
	infos.push_back(loadingInfo);
	// Lower poly Reck mesh for Projectiles
	loadingInfo.File = "../Assets/rock.obj";
	loadingInfo.DoResize = true;
	loadingInfo.Extents = glm::vec3(1.f, 1.f, 1.f);
	loadingInfo.SubMeshes[0].Name = "rock";
	infos.push_back(loadingInfo);
	// Box mesh for planes and boxes
	loadingInfo.File = "../Assets/box.obj";
	loadingInfo.DoResize = true;
	loadingInfo.Extents = glm::vec3(2.f, 2.f, 2.f);  // cube 2x2x2
	loadingInfo.SubMeshes[0].Name = "box";
	infos.push_back(loadingInfo);

	if (!nGraphics::gMeshManager->Load(infos))
	{
		std::cout << "Error loading meshes" << std::endl;
		return -1;
	}

#pragma endregion

#pragma region Graphics Components

	{
		// Skybox Graphics Component
		nGraphics::sGraphicsComponentDef graphicsDef;
		skyboxGraphics = new nGraphics::cGraphicsComponent(graphicsDef);
	}
	{
		// Rock Graphics Component
		nGraphics::sGraphicsComponentDef graphicsDef;
		graphicsDef.Mesh = "rock";
		glm::set(graphicsDef.ModelColor, 0.0f, 0.0f, 0.0f, 0.0f);
		glm::set(graphicsDef.Position, 0.0f, 1.0f, 0.0f);
		glm::set(graphicsDef.Scale, 1.0f, 1.0f, 1.0f);
		rockGraphics = new nGraphics::cGraphicsComponent(graphicsDef);
	}
	{
		// Plane Graphics Component
		nGraphics::sGraphicsComponentDef graphicsDef;
		graphicsDef.Mesh = "box";
		graphicsDef.TexDiffuse = "roald";
		glm::set(graphicsDef.ModelColor, 1.0f, 1.0f, 1.0f, 1.0f);
		glm::set(graphicsDef.Position, 0.0f, -0.2f, 0.0f);
		glm::set(graphicsDef.Scale, 100.0f, 1.0f, 100.0f);
		planeGraphics = new nGraphics::cGraphicsComponent(graphicsDef);
	}
	{
		//Wall Graphics Component
		nGraphics::sGraphicsComponentDef graphicsDef;
		graphicsDef.Mesh = "box";
		graphicsDef.TexDiffuse = "bricks";
		glm::set(graphicsDef.ModelColor, 1.0f, 1.0f, 1.0f, 1.0f);
		//glm::set(graphicsDef.Position, 10.0f, 1.0f, -10.0f);
		glm::set(graphicsDef.Position, 0.0f, 1.0f, -40.0f);
		glm::set(graphicsDef.Scale, 40.0f, 20.0f, 1.0f);
		//glm::set(graphicsDef.Scale, 20.0f, 8.0f, 0.1f);
		wallGraphics1 = new nGraphics::cGraphicsComponent(graphicsDef);
	}
	{
		//Wall Graphics Component
		nGraphics::sGraphicsComponentDef graphicsDef;
		graphicsDef.Mesh = "box";
		graphicsDef.TexDiffuse = "bricks";
		glm::set(graphicsDef.ModelColor, 1.0f, 1.0f, 1.0f, 1.0f);
		//glm::set(graphicsDef.Position, -10.0f, 1.0f, 10.0f);
		glm::set(graphicsDef.Position, -35.0f, 1.0f, 40.0f);
		glm::set(graphicsDef.Scale, 80.0f, 8.0f, 1.0f);
		//glm::set(graphicsDef.Scale, 20.0f, 8.0f, 0.1f);
		wallGraphics2 = new nGraphics::cGraphicsComponent(graphicsDef);
	}
	{
		//Wall Graphics Component
		nGraphics::sGraphicsComponentDef graphicsDef;
		graphicsDef.Mesh = "box";
		graphicsDef.TexDiffuse = "bricks";
		glm::set(graphicsDef.ModelColor, 1.0f, 1.0f, 1.0f, 1.0f);
		//glm::set(graphicsDef.Position, -10.0f, 1.0f, 10.0f);
		glm::set(graphicsDef.Position, -40.0f, 1.0f, 40.0f);
		glm::set(graphicsDef.Scale, 1.0f, 8.0f, 80.0f);
		//glm::set(graphicsDef.Scale, 0.1f, 8.0f, 20.0f);
		wallGraphics3 = new nGraphics::cGraphicsComponent(graphicsDef);
	}
	{
		//Wall Graphics Component
		nGraphics::sGraphicsComponentDef graphicsDef;
		graphicsDef.Mesh = "box";
		graphicsDef.TexDiffuse = "bricks";
		glm::set(graphicsDef.ModelColor, 1.0f, 1.0f, 1.0f, 1.0f);
		//glm::set(graphicsDef.Position, 10.0f, 1.0f, -10.0f);
		glm::set(graphicsDef.Position, 40.0f, 1.0f, -40.0f);
		glm::set(graphicsDef.Scale, 1.0f, 8.0f, 80.0f);
		//glm::set(graphicsDef.Scale, 0.1f, 8.0f, 20.0f);
		wallGraphics4 = new nGraphics::cGraphicsComponent(graphicsDef);
	}
#pragma endregion
	return true;
}
#pragma endregion

#pragma region Destructors
void EndPhysics()
{
	if (particleWorld)
	{
		delete particleWorld;
		particleWorld = 0;
	}
}

void EndGraphics()
{
	//TODO: Add some safety
	delete planeGraphics;
	delete rockGraphics;
	delete skyboxGraphics;
	delete wallGraphics1;
	delete wallGraphics2;
	delete wallGraphics3;
	delete wallGraphics4;

	delete camera;

	nGraphics::Shutdown();
}
#pragma endregion

