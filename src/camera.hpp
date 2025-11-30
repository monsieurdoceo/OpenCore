#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement 
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
private:
	glm::vec3 m_position;
	glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_worldUp;

	float m_yaw;
	float m_pitch;
	float m_movementSpeed = 2.5f;
	float m_mouseSensitivity = 0.25f;
	float m_zoom = 45.0f;

	void updateCameraVectors();

public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
	
	void processMouseMovement(float xoffSet, float yoffSet, GLboolean containPitch = true);
	void processKeyboard(Camera_Movement direction, float deltaTime);

	glm::mat4 getViewMatrix() { return glm::lookAt(m_position, m_position + m_front, m_up); }

	glm::vec3 getPosition() { return m_position; }

	glm::vec3 getFront() { return m_front; }
	glm::vec3 getUp() { return m_up; }
	glm::vec3 getRight() { return m_right; }
	
	glm::vec3 getWorldUp() { return m_worldUp; }

	float getYaw() { return m_yaw; }
	float getPitch() { return m_pitch; }

	float getMovementSpeed() { return m_movementSpeed; }
	float getMouseSenitivity() { return m_mouseSensitivity; }

	float getZoom() { return m_zoom; }
};

#endif 
