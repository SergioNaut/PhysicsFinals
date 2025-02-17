#include <input/input.h>
#include <graphics/graphics.h>

namespace nInput
{
	cInputManager* gInputManager = 0;

	bool Init()
	{
		if (gInputManager) return true;
		gInputManager = cInputManager::GetInstance();
		//So no button press states are missed
		glfwSetInputMode(nGraphics::gWindow, GLFW_STICKY_MOUSE_BUTTONS, 1);
		glfwSetInputMode(nGraphics::gWindow, GLFW_STICKY_KEYS, 1);

		glfwPollEvents();
		return true;
	}
}