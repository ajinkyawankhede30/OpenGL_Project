#pragma once
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <sstream>
#include <unordered_map>

#include "GL/glew.h"
#include "glfw3.h"

struct ShaderProgramSource {

	std::string vertexsource;
	std::string fragmentsource;
};

class Shaders
{
private:
	unsigned int m_rendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	Shaders(const char* filepath);
	~Shaders();
	void Bind();
	void UnBind();
	int GetUniformLocation(const std::string& name);
	void SetUniform4f(const std::string& name, float f1, float f2, float f3, float f4);
	void SetUniform1i(const std::string& name, int value);
	
private:
	ShaderProgramSource ParseShader(const char* filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexsource, const std::string& fragmentsource);
};

