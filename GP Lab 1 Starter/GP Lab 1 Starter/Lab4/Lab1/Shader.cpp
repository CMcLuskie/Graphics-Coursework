#include "Shader.h"
#include <iostream>
#include <fstream>

Shader::Shader()
{
	
}


Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(ShaderProgram, shaders[i]); //detach shader from program
		glDeleteShader(shaders[i]); //delete the sahders
	}
	glDeleteProgram(ShaderProgram); // delete the program
}

void Shader::InitialiseShader(const std::string vertexShader, const std::string fragShader)
{
	ShaderProgram = glCreateProgram(); // create shader program (openGL saves as ref number)
	shaders[0] = Create(Load(vertexShader), GL_VERTEX_SHADER); // create vertex shader
	shaders[1] = Create(Load(fragShader), GL_FRAGMENT_SHADER); // create fragment shader

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(ShaderProgram, shaders[i]); //add all our shaders to the shader program "shaders" 
	}

	glBindAttribLocation(ShaderProgram, 0, "position"); // associate attribute variable with our shader program attribute (in this case attribute vec3 position;)
	glBindAttribLocation(ShaderProgram, 1, "texCoord");
	glBindAttribLocation(ShaderProgram, 2, "normals");

	glLinkProgram(ShaderProgram); //create executables that will run on the GPU shaders
	CheckError(ShaderProgram, GL_LINK_STATUS, true, "Error: Shader program linking failed"); // cheack for error

	glValidateProgram(ShaderProgram); //check the entire program is valid
	CheckError(ShaderProgram, GL_VALIDATE_STATUS, true, "Error: Shader program not valid");

	uniforms[TRANSFORM_U] = glGetUniformLocation(ShaderProgram, "transform"); // associate with the location of uniform variable within a program
}

void Shader::InitialiseShader(const std::string vertexShader, const std::string fragShader, const std::string geometryShader)
{
	ShaderProgram = glCreateProgram();
	shaders[0] = Create(Load(vertexShader), GL_VERTEX_SHADER);
	shaders[1] = Create(Load(fragShader), GL_FRAGMENT_SHADER);
	shaders[2] = Create(Load(geometryShader), GL_GEOMETRY_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(ShaderProgram, shaders[i]);

	glBindAttribLocation(ShaderProgram, 0, "position");
	glBindAttribLocation(ShaderProgram, 1, "texCoord");
	glBindAttribLocation(ShaderProgram, 2, "normals");

	glLinkProgram(ShaderProgram);
	CheckError(ShaderProgram, GL_LINK_STATUS, true, "Error: Shader program Linking failed");

	glValidateProgram(ShaderProgram);
	CheckError(ShaderProgram, GL_VALIDATE_STATUS, true, "Error: Shader program not valid");

	uniforms[TRANSFORM_U] = glGetUniformLocation(ShaderProgram, "transform");
}

void Shader::BindShader()
{
	glUseProgram(ShaderProgram); //installs the program object specified by program as part of rendering state
}

void Shader::UpdateShader(const Transform& transform, const Camera& camera)
{
	glm::mat4 mvp = camera.GetViewProjection() * transform.GetModel();
	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GLU_FALSE, &mvp[0][0]);
}


GLuint Shader::Create(const std::string& text, unsigned int type)
{
	GLuint shader = glCreateShader(type); //create shader based on specified type

	if (shader == 0) //if == 0 shader no created
		std::cerr << "Error type creation failed " << type << std::endl;

	const GLchar* stringSource[1]; //convert strings into list of c-strings
	stringSource[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, stringSource, lengths); //send source code to opengl
	glCompileShader(shader); //get open gl to compile shader code

	CheckError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!"); //check for compile error

	return shader;
}

std::string Shader::Load(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void Shader::CheckError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

