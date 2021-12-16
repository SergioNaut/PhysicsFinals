#pragma once
#include <cParticleWorld.h>
#include <cObject.h>
#include <graphics/c3rdPersonCamera.h>
#include <graphics/cGraphicsComponent.h>
#include <vector>
#include <cConfigReader.h>

//Global functions for the program setup
//Mostly to clean up the main

#pragma region CameraSetup
extern nGraphics::sPerFrameVars PerFrameVars;
extern nGraphics::c3rdPersonCamera* camera;
#pragma endregion

#pragma region GraphicsStuff
extern nGraphics::cGraphicsComponent* skyboxGraphics;
extern nGraphics::cGraphicsComponent* planeGraphics;
extern nGraphics::cGraphicsComponent* rockGraphics;

extern nGraphics::cGraphicsComponent* wallGraphics1;
extern nGraphics::cGraphicsComponent* wallGraphics2;
extern nGraphics::cGraphicsComponent* wallGraphics3;
extern nGraphics::cGraphicsComponent* wallGraphics4;

extern nGraphics::cGraphicsComponent* sphereGraphics;
extern nGraphics::cGraphicsComponent* tubeGraphics;

extern nGraphics::cGraphicsComponent* projectileGraphics1;
extern nGraphics::cGraphicsComponent* projectileGraphics2;
extern nGraphics::cGraphicsComponent* projectileGraphics3;
#pragma endregion

extern std::vector<cObject*> objects;
extern nPhysics::cParticleWorld* particleWorld;

#pragma region ConfigReader

extern sConfiguration projectileConfig;
extern cConfigReader configReader;

#pragma endregion


#pragma region StartupFunctions

bool StartGraphics();
bool StartPhysics();

#pragma endregion

#pragma region EndFunctions

void EndGraphics();
void EndPhysics();

#pragma endregion

