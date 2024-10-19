#pragma once

struct ShaderProgram {
	std::string VertexShader;
	std::string FragmentShader;
};

static ShaderProgram ParseShader(const char* filepath);

static unsigned int CompileShader(unsigned int type, const std::string& source);

static unsigned int CreateShader(const std::string& vertex, const std::string& fragment);
