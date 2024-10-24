#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "GL/glew.h"
#include "glfw3.h"
#include "Shaders.h"


#define ASSERT(x) if(!x) __debugbreak();
#define CallLog(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
	if (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] ( " << error << " )" << ": " << function << ": " << file << ": " << line << std::endl;
		return false;
	}
	return true;
}

static int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, NULL); //Replaces the source code in a shader object
	glCompileShader(id);

	//error handling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vetex" : "fragment") << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}


int main()
{
	GLFWwindow* window;

	if (!glfwInit())
	{
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(960, 540, "My_Game", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "Error initializing glew...\n";

	std::cout << glGetString(GL_VERSION) << "\n";

	float positions[] =
	{	//position	
		-0.5f, -0.5f, 1.0f, 0.0f, 0.0f,//0th index
		 0.5,  -0.5f, 0.0f, 1.0f, 0.0f,//1 
		 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,//2
		 -0.5f, 0.5f, 0.0f, 1.0f, 0.0f//3rd index
	};

	unsigned int indices[] =
	{
		0,1,2,
		2,3,0
	};

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 4 * 5 * sizeof(float), positions, GL_STATIC_DRAW);

	//enable vertex/position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

	//enable color attributes
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(GL_FLOAT)));

	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	Shaders myshader("D:\\openGL\\My_Projects\\opnGL_practice\\opnGL_practice\\src\\Shader_main.txt");
	myshader.Bind();
	/*
	std::string vertex_shader =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec4 positions;\n"
		"layout(location = 1) in vec3 vertex_colors;\n"
		"out vec3 out_colors;\n"
		"void main()\n"
		"{\n"
			"gl_Position = positions;\n"
			"out_colors = vertex_colors;\n"
		"}\n";

	std::string fragment_shader =
		"#version 330 core\n"
		"\n"
		"out vec4 color;\n"
		"in vec3 out_colors;\n"
		"void main()\n"
		"{\n"
			"color = vec4(out_colors,1.0f);\n"
		"}\n";

	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	const char* vrtx_src = vertex_shader.c_str();
	glShaderSource(vs, 1, &vrtx_src, NULL); //Replaces the source code in a shader object
	glCompileShader(vs);

	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	const char* frg_src = fragment_shader.c_str();
	glShaderSource(fs, 1, &frg_src, NULL);
	glCompileShader(fs);

	unsigned int program = glCreateProgram();

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	glUseProgram(program);
	*/

	glBindVertexArray(0);
	//glUseProgram(0);
	myshader.UnBind();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		myshader.Bind();
		//glUseProgram(program);

		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &buffer);
	//glDeleteProgram(program);

	glfwTerminate();
	return 0;
}