#include "renderer/window.hpp"
#include "scenes/editorscene.hpp"

int main()
{
    try 
    {
        Window& window = Window::get();

        window.addScene<EditorScene>();
        window.changeScene(0);

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
    } 
    catch (const std::exception& e) 
    {   
        std::cerr << "Fatal error during application startup: " << e.what() << std::endl;
        return -1;
    }

	return 0;
}
