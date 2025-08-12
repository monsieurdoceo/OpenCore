#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
private:
	unsigned int m_ID;

	std::string readShaderFile(const char* shaderPath);	

public:
	Shader(const char* vertexPath, const char* fragmetPath);

	void use();
	void remove();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
};

#endif
