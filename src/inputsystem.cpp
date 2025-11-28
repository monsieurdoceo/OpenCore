#include "inputsystem.hpp"

InputSystem::InputSystem(Camera camera)
{
	_camera = camera;
}

void InputSystem::processInput(GLFWwindow* window, Time time)
{
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		_camera.processKeyboard(FORWARD, time.getDeltaTime());
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		_camera.processKeyboard(BACKWARD, time.getDeltaTime());
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		_camera.processKeyboard(LEFT, time.getDeltaTime());
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		_camera.processKeyboard(RIGHT, time.getDeltaTime());
	}
}

void InputSystem::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (_firstMouse)
	{
		_lastX = xpos;
		_lastY = ypos;
		_firstMouse = false;
	}

	float xoffSet = xpos - _lastX;
	float yoffSet = _lastY - ypos;
	_lastX = xpos;
	_lastY = ypos;

	const float sensitivity = 0.1f;
	xoffSet *= sensitivity;
	yoffSet *= sensitivity;

	_camera.processMouseMovement(xoffSet, yoffSet);
}

