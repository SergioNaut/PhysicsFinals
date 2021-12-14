#pragma once
//Base Class for creating objects with the particles

class cObject
{
public:
	virtual void Begin() {};
	virtual void Update(float deltaTime) {};
	virtual void Rander() {};
	virtual void End() {};
};