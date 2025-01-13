#pragma once
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <sstream>
#include <unordered_map>

#include "GL/glew.h"
#include "glfw3.h"

#ifndef GLM_HEADERS
#define GLM_HEADERS

#include "glm/glm.hpp"
#include "glm/vec4.hpp"
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

#endif // !GLM_HEADERS

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
	void SetUniformVec3(const std::string& name, glm::vec3 val);
	void SetUniform1i(const std::string& name, int value);
	void SetUniformMat4f(const std::string& name, const glm::mat4& value);

private:
	ShaderProgramSource ParseShader(const char* filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexsource, const std::string& fragmentsource);
};

