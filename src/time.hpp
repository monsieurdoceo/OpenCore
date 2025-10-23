#ifndef TIME_HPP
#define TIME_HPP

#include <GLFW/glfw3.h>
#include <iostream>

class Time
{
private:
	float _deltaTime;
	float _lastFrame;

	double _previousTime = glfwGetTime();
	int _frameCount = 0;

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

	void getFramerate()
	{
		double currentTime = glfwGetTime();
		_frameCount++;
		if (currentTime - _previousTime >= 1.0)
		{
			std::cout << "FPS: " << _frameCount << std::endl;
			_frameCount = 0;
			_previousTime = currentTime;
		}
	}
};

#endif
