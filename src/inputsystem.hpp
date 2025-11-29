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

	bool m_keyPressed[350];

	InputSystem() {}
	InputSystem(const InputSystem&) = delete;
	InputSystem& operator=(const InputSystem&) = delete;

public:
	static InputSystem* getInstance() 
	{
		return (m_instance == nullptr) ? new InputSystem() : m_instance;
	}

	static void mousePosCallback(GLFWwindow* window, double xPos, double yPos);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void mouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	void endFrame();
	bool mouseButtonDown(int button) { return m_mouseButtonPressed[button]; }
	bool isKeyPressed(int keyCode) { return m_keyPressed[keyCode]; }

	float getMouseX() { return (float) m_posX; }
	float getMouseY() { return (float) m_posY; }
	float getMouseDirectionX() { return (float) (m_lastX - m_posX); }
	float getMouseDirectionY() { return (float) (m_lastY - m_posY); }
	float getMouseScrollX() { return (float) m_scrollX; }
	float getMouseScrollY() { return (float) m_scrollY; }
	bool isDragging() { return m_isDragging; }
};

#endif
