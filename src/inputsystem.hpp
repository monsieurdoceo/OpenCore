#ifndef INPUTSYSTEM_HPP
#define INPUTSYSTEM_HPP

#include "camera.hpp"
#include "time.hpp"

class InputSystem
{
private:
	Camera _camera;

	bool _firstMouse = true;
	float _lastX = 1920.0f / 2.0f;
	float _lastY = 1080.0f / 2.0f;	

public:
	InputSystem(Camera camera);
	void processInput(GLFWwindow* window, Time time);
	void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
};

#endif
