#include "window.hpp"

int main()
{
    Window window;

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

	while (!glfwWindowShouldClose(window.getWindow()))
	{
        float currentFrame = (float) glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        window.update();
        window.fixedUpdate(deltaTime);
        window.render();
	}
    
    window.erase();
	return 0;
}

