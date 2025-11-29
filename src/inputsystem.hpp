#ifndef INPUTSYSTEM_HPP
#define INPUTSYSTEM_HPP

#include <glm/glm.hpp>

#include "camera.hpp"
#include "time.hpp"

class InputSystem
{
private:
	static InputSystem* m_instance;

	double m_scrollX, m_scrollY;
	double m_lastX, m_lastY;
	double m_posX, m_posY;
	bool m_mouseButtonPressed[3];
	bool m_isDragging;

	InputSystem() {}
	InputSystem(const InputSystem&) = delete;
	InputSystem& operator=(const InputSystem&) = delete;

public:
	static InputSystem* getInstance() 
	{
		return (m_instance == nullptr) ? new InputSystem() : m_instance;
	}

	static void mousePosCallback(GLFWwindow* window, double xPos, double yPos);
};

#endif
