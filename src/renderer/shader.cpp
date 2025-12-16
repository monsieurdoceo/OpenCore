#include "shader.hpp"

std::string Shader::readShaderFile(const char* shaderPath)
{
	std::string shaderCode;
	std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	
	try
	{
		shaderFile.open(shaderPath);

		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		
		shaderFile.close();
		
		shaderCode = shaderStream.str();
	}
	catch(std::ifstream::failure& e) { std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl; }
	
	return shaderCode;
}

void Shader::checkError(unsigned int id, std::string type)
{
	int success;
	char infoLog[1024];
	if (type == "PROGRAM")
	{
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(id, 1024, NULL, infoLog);
			std::cout << "ERROR::" << type << "::LINKING_FAILED\n" << infoLog << std::endl;
		}		
	}
	else
	{
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(id, 1024, NULL, infoLog);
			std::cout << "ERROR::" << type << "::COMPILATION_FAILED\n" << infoLog << std::endl;
		}		
	}
}

unsigned int Shader::createShader(GLenum shaderType, const char* shaderCode)
{
	unsigned int shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &shaderCode, NULL);
	glCompileShader(shaderID);
	
	checkError(shaderID, "SHADER");

	return shaderID;
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{	
	std::string vertexShader = readShaderFile(vertexPath);
	std::string fragmentShader = readShaderFile(fragmentPath);

	m_vertexID = createShader(GL_VERTEX_SHADER, vertexShader.c_str());
	m_fragmentID = createShader(GL_FRAGMENT_SHADER, fragmentShader.c_str());

	m_programID = glCreateProgram();
	glAttachShader(m_programID, m_vertexID);
	glAttachShader(m_programID, m_fragmentID);
	
	glLinkProgram(m_programID);
	checkError(m_programID, "PROGRAM");

	glDeleteShader(m_vertexID);
	glDeleteShader(m_fragmentID);
}

void Shader::use() { glUseProgram(m_programID); }
void Shader::remove() { glDeleteProgram(m_programID); }

void Shader::setBool(const std::string& name, bool value) const { glUniform1i(glGetUniformLocation(m_programID, name.c_str()), (int) value); }
void Shader::setInt(const std::string& name, int value) const { glUniform1i(glGetUniformLocation(m_programID, name.c_str()), value); }
void Shader::setFloat(const std::string& name, float value) const { glUniform1f(glGetUniformLocation(m_programID, name.c_str()), value); }

void Shader::setVec2(const std::string& name, const glm::vec2& value) const { glUniform2fv(glGetUniformLocation(m_programID, name.c_str()), 1, &value[0]); }
void Shader::setVec3(const std::string& name, const glm::vec3& value) const { glUniform3fv(glGetUniformLocation(m_programID, name.c_str()), 1, &value[0]); }
void Shader::setVec4(const std::string& name, const glm::vec4& value) const { glUniform4fv(glGetUniformLocation(m_programID, name.c_str()), 1, &value[0]); }

void Shader::setMat2(const std::string& name, const glm::mat2& value) const { glUniformMatrix2fv(glGetUniformLocation(m_programID, name.c_str()), 1, GL_FALSE, &value[0][0]); }
void Shader::setMat3(const std::string& name, const glm::mat3& value) const { glUniformMatrix3fv(glGetUniformLocation(m_programID, name.c_str()), 1, GL_FALSE, &value[0][0]); }
void Shader::setMat4(const std::string& name, const glm::mat4& value) const { glUniformMatrix4fv(glGetUniformLocation(m_programID, name.c_str()), 1, GL_FALSE, &value[0][0]); }
