#pragma once
class cEntity
{
public:
	virtual ~cEntity() {}

	virtual void BeginScene() {};
	//virtual void BeginFrame() {};
	virtual void Update(float deltaTime) {}
	virtual void Render() {};
	//virtual void EndFrame() {};
	virtual void EndScene() {};
};