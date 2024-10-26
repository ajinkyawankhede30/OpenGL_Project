#include "Shaders.h"

Shaders::Shaders(const char* filepath)
	:m_rendererID(0)
{
	ShaderProgramSource source = ParseShader(filepath);
	m_rendererID = CreateShader(source.vertexsource, source.fragmentsource);

}

Shaders::~Shaders()
{
	glDeleteShader(m_rendererID);
}

void Shaders::Bind()
{
	glUseProgram(m_rendererID);
}

void Shaders::UnBind()
{
	glUseProgram(0);
}

void Shaders::SetUniform4f(const std::string& name, float f1, float f2, float f3, float f4)
{
	unsigned int location = GetUniformLocation(name);

	glUseProgram(m_rendererID);
	glUniform4f(location, f1, f2, f3, f4);
}

void Shaders::SetUniform1i(const std::string& name, int value)
{
	int location = GetUniformLocation(name);

	glUseProgram(m_rendererID);
	glUniform1i(location, value);
}

ShaderProgramSource Shaders::ParseShader(const char* filepath)
{
	enum class ShaderType
	{
		INVALID = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	std::fstream read(filepath);
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::INVALID;
	while (std::getline(read, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << "\n";
		}
	}
	return { ss[0].str(), ss[1].str() };
}

unsigned int Shaders::CreateShader(const std::string& vertexsource, const std::string& fragmentsource)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexsource);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentsource);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteProgram(vs);
	glDeleteProgram(fs);

	return program;
}

unsigned int Shaders::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	//error handling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* errorMessage = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, errorMessage);
		std::cout << "Failed to compile: " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " Shader" << "\n";
		std::cout << errorMessage << "\n";
		glDeleteShader(id);
		return 0;
	}
	return id;
}


int Shaders::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	int location = glGetUniformLocation(m_rendererID, name.c_str());
	if (location == -1)
		std::cout << "WARNING: Uniform " << name << " does not exist.\n";

	m_UniformLocationCache[name] = location;

	return location;
}