#pragma once
//Base Class for creating objects with the particles

class cObject
{
public:
	virtual void Begin() {};
	virtual void Update(float deltaTime) {};
	virtual void Render() {};
	virtual void End() {};
};