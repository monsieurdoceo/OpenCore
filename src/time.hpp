#ifndef TIME_HPP
#define TIME_HPP

#include <GLFW/glfw3.h>

class Time
{
private:
	float _deltaTime;
	float _lastFrame;

public:
	void update()
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		_deltaTime = currentFrame - _lastFrame;
		_lastFrame = currentFrame;
	}

	float getDeltaTime() 
	{
		return _deltaTime;
	}
};

#endif
