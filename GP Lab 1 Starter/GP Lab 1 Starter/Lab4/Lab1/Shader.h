#pragma once
#include <string>
#include <GL\glew.h>
#include "transform.h"
#include "Camera.h"
#include <iostream>

class Shader
{
public:
	Shader();

	void BindShader(); //Set gpu to use our shaders
	void UpdateShader(const Transform& transform, const Camera& camera);
	void InitialiseShader(const std::string vertexShader, const std::string fragShader);
	void InitialiseShader(const std::string vertexShader, const std::string fragShader, const std::string geometryShader);
	std::string Shader::Load(const std::string& fileName);
	void Shader::CheckError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint Shader::Create(const std::string& text, unsigned int type);

    ~Shader();

	// uniform functions
	// ------------------------------------------------------------------------
	void SetBoolean(const std::string &name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ShaderProgram, name.c_str()), (int)value);

		if ((glGetUniformLocation(ShaderProgram, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void SetInteger(const std::string &name, int value) const
	{
		glUniform1i(glGetUniformLocation(ShaderProgram, name.c_str()), value);

		if ((glGetUniformLocation(ShaderProgram, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void SetFloat(const std::string &name, float value) const
	{
		glUniform1f(glGetUniformLocation(ShaderProgram, name.c_str()), value);

		if ((glGetUniformLocation(ShaderProgram, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void SetVector2(const std::string &name, const glm::vec2 &value) const
	{
		glUniform2fv(glGetUniformLocation
			(ShaderProgram, name.c_str()), 1, &value[0]);

		if ((glGetUniformLocation(ShaderProgram, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	void SetVector2(const std::string &name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(ShaderProgram, name.c_str()), x, y);

		if ((glGetUniformLocation(ShaderProgram, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void SetVector3(const std::string &name, const glm::vec3 &value) const
	{
		glUniform3fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1, &value[0]);

		if ((glGetUniformLocation(ShaderProgram, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	void SetVector3(const std::string &name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(ShaderProgram, name.c_str()), x, y, z);

		if ((glGetUniformLocation(ShaderProgram, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void SetVector4(const std::string &name, const glm::vec4 &value) const
	{
		glUniform4fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1, &value[0]);

		if ((glGetUniformLocation(ShaderProgram, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	void SetVector4(const std::string &name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(ShaderProgram, name.c_str()), x, y, z, w);

		if ((glGetUniformLocation(ShaderProgram, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void SetMatrix2(const std::string &name, const glm::mat2 &mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);

		if ((glGetUniformLocation(ShaderProgram, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void SetMatrix3(const std::string &name, const glm::mat3 &mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);

		if ((glGetUniformLocation(ShaderProgram, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void SetMatrix4(const std::string &name, const glm::mat4 &mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);

		if ((glGetUniformLocation(ShaderProgram, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
protected:
private:
	static const unsigned int NUM_SHADERS = 3; // number of shaders

	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	GLuint ShaderProgram; // Track the shader program
	GLuint shaders[NUM_SHADERS]; //array of shaders
	GLuint uniforms[NUM_UNIFORMS]; //no of uniform variables
};
