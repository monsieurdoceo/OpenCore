#include "inputsystem.hpp"

InputSystem* InputSystem::m_instance = nullptr;

void InputSystem::mousePosCallback(GLFWwindow* window, double xPos, double yPos)
{
	getInstance()->m_lastX = getInstance()->m_posX;
	getInstance()->m_lastY = getInstance()->m_posY;
	getInstance()->m_posX = xPos;
	getInstance()->m_posY = yPos;	
	getInstance()->m_isDragging = getInstance()->m_mouseButtonPressed[0] || getInstance()->m_mouseButtonPressed[1] || getInstance()->m_mouseButtonPressed[2];
}

void InputSystem::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (button < sizeof(getInstance()->m_mouseButtonPressed)) getInstance()->m_mouseButtonPressed[button] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		if (button < sizeof(getInstance()->m_mouseButtonPressed))
		{
			getInstance()->m_mouseButtonPressed[button] = false;
			getInstance()->m_isDragging = false;
		}
	}
}

void InputSystem::mouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	getInstance()->m_scrollX = xOffset;
	getInstance()->m_scrollY = yOffset;
}

void InputSystem::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		getInstance()->m_keyPressed[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		getInstance()->m_keyPressed[key] = false;
	}
}

void InputSystem::endFrame()
{
	m_scrollX = 0;
	m_scrollY = 0;
	m_lastX = m_posX;
	m_lastY = m_posY;
}
