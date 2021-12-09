#pragma once
#include <graphics/cameras/c3rdPersonCamera.h>
#include <graphics/cGraphicsComponent.h>
#include <physics/cParticleWorld.h>
#include <cEntity.h>
//Not sure if needed
#include <cGameTimer.h>
#include <vector>


extern cTimeStepInfo<float> gTimeStepInfo; // TODO: shift to use this for entity update calls!
extern nGraphics::sPerFrameVars gPerFrameVars;
extern nGraphics::c3rdPersonCamera* gCamera;
extern nGraphics::cGraphicsComponent* gSkyboxGraphics;
extern nGraphics::cGraphicsComponent* gPlaneGraphics;
extern nGraphics::cGraphicsComponent* gSphereGraphics;

extern nPhysics::cParticleWorld* gParticleWorld;
extern std::vector<cEntity*> gEntities;

bool InitPhysics();
void DestroyPhysics();

bool InitGraphics();
void DestroyGraphics();