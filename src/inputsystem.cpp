#include "inputsystem.hpp"

InputSystem* InputSystem::m_instance = nullptr;

void InputSystem::mousePosCallback(GLFWwindow* window, double xPos, double yPos)
{
	getInstance()->m_lastX = getInstance()->m_posX;
	getInstance()->m_lastY = getInstance()->m_posY;
	getInstance()->m_posX = xPos;
	getInstance()->m_posY = yPos;	
}
