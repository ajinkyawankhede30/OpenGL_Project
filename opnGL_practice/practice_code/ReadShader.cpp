#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <glew.h>
#include <glfw3.h>
#include "ReadShader.h"


static ShaderProgram ParseShader(const char* filepath)
{
	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	std::fstream read(filepath);
	std::stringstream ss[2];
	std::string line;
	ShaderType shdr_type = ShaderType::NONE;

	while (std::getline(read,line))
	{
		if (line.find("#Shader") != std::string::npos)
		{
			if (line.find("Vertex") != std::string::npos)
				shdr_type = ShaderType::VERTEX;
			else
				shdr_type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)shdr_type] << line.c_str() << "\n";
		}
	}

	return { ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	const char* src = source.c_str();
	
	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	//error check
	int result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int messageLen;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &messageLen);
		char* message = (char*)alloca(messageLen * sizeof(char));
		glGetShaderInfoLog(shader, messageLen, &messageLen, message);
		std::cout << "Failed to compile: " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

static unsigned int CreateShader(const std::string& vertex, const std::string& fragment)
{
	unsigned int id = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertex);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragment);
	
	glAttachShader(id, vs);
	glAttachShader(id, fs);

	glLinkProgram(id);
	glValidateProgram(id);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return id;
}

static unsigned int Compiler(unsigned int type, const std::string& shaderprogram)
{
	const char* shaderprg = shaderprogram.c_str();

	unsigned int shdr = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shdr, 1, &shaderprg, NULL);
	glCompileShader(shdr);

	int result;
	glGetShaderiv(shdr, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int messageLen;
		glGetShaderiv(shdr, GL_INFO_LOG_LENGTH, &messageLen);
		char* message = (char*)alloca(messageLen * sizeof(char));
		glGetShaderInfoLog(shdr, messageLen, &messageLen, message);
		std::cout << "Failed to Compile: " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << std::endl;
		std::cout << message << "\n";
		glDeleteShader(shdr);
		return 0;
	}
	return shdr;
}

static unsigned int Create(const std::string& vertex,const std::string& fragment)
{
	unsigned int prgm = glCreateProgram();

	unsigned int vs = Compiler(GL_VERTEX_SHADER, vertex);
	unsigned int fs = Compiler(GL_FRAGMENT_SHADER, fragment);

	glAttachShader(prgm, vs);
	glAttachShader(prgm, fs);

	glLinkProgram(prgm);
	glValidateProgram(prgm);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return prgm;
}
