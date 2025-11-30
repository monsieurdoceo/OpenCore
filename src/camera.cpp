#include "camera.hpp"

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(front);
	
	m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
{
	m_position = position;
	m_worldUp = up;
	m_yaw = yaw;
	m_pitch = pitch;

	updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
{
	m_position = glm::vec3(posX, posY, posZ);
	m_worldUp = glm::vec3(upX, upY, upZ);
	m_yaw = yaw;
	m_pitch = pitch;

	updateCameraVectors();
}

void Camera::processMouseMovement(float xoffSet, float yoffSet, GLboolean containPitch)
{
	xoffSet *= m_mouseSensitivity;
	yoffSet *= m_mouseSensitivity;

	m_yaw += xoffSet;
	m_pitch += yoffSet;

	if (containPitch)
	{
		if (m_pitch > 89.0f)
		{
			m_pitch = 89.0f;
		}
		if (m_pitch < -89.0f)
		{
			m_pitch = -89.0f;
		}
	}

	updateCameraVectors();
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = m_movementSpeed * deltaTime;
	if (direction == FORWARD) m_position += m_front * velocity;
	if (direction == BACKWARD) m_position -= m_front * velocity;
	if (direction == LEFT) m_position -= m_right * velocity;
	if (direction == RIGHT) m_position += m_right * velocity;
}

