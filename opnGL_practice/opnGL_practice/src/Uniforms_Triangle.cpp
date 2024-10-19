#pragma once
#include <iostream>
#include <GL/glew.h>
#include <glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
//#include "Window.cpp"

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

	window = glfwCreateWindow(640, 440, "GAME", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}


	glfwMakeContextCurrent(window);

	glfwSwapInterval(2);

	std::cout << glGetString(GL_VERSION) << std::endl;
	std::cout << glGetString(GL_RENDERER) << std::endl;

	if (glewInit() != GLEW_OK)
		std::cout << "Error Initializing glew..." << std::endl;


	float positions[] = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.0f, 0.5f
	};

	//Create a vertex buffer
	unsigned int buffer;
	CallLog(glGenBuffers(1, &buffer));
	CallLog(glBindBuffer(GL_ARRAY_BUFFER, buffer));
	CallLog(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));
	

	//Create vertex array object
	unsigned int vao;
	CallLog(glGenVertexArrays(1, &vao));
	CallLog(glBindVertexArray(vao));
	CallLog(glEnableVertexAttribArray(0));
	CallLog(glBindBuffer(GL_ARRAY_BUFFER, buffer));
	CallLog(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), 0));

	const char* vertex_shader =
		"#version 400 core\n"
		"\n"
		"layout (location = 0) in vec2 positions;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = vec4(positions, 0.0, 1.0);\n"
		"}\n";

	const char* fragment_shader =
		"#version 400 core\n"
		"\n"
		"layout (location = 0) out vec4 color;\n"
		"uniform vec4 u_color;\n"
		"void main()\n"
		"{\n"
		"	color = u_color;\n"
		"}\n";

	unsigned int vx_shader = glCreateShader(GL_VERTEX_SHADER);
	CallLog(glShaderSource(vx_shader, 1, &vertex_shader, NULL));
	CallLog(glCompileShader(vx_shader));

	unsigned int fg_shader = glCreateShader(GL_FRAGMENT_SHADER);
	CallLog(glShaderSource(fg_shader, 1, &fragment_shader, NULL));
	CallLog(glCompileShader(fg_shader));

	unsigned int program = glCreateProgram();
	CallLog(glAttachShader(program, vx_shader));
	CallLog(glAttachShader(program, fg_shader));
	CallLog(glLinkProgram(program));
	CallLog(glValidateProgram(program));
	//CallLog(glUseProgram(program));
	
	//Uniforms are used to pass data from application on CPU to the shaders on the GPU.
	// 
	//Get uniform location
	CallLog(int location = glGetUniformLocation(program, "u_color"));
	ASSERT(location == -1);
	glUseProgram(program);

	//Assign color values
	CallLog(glUniform4f(location, 0.5f, 0.3f, 0.8f, 1.0f));

	glDeleteShader(vx_shader);
	glDeleteShader(fg_shader);

	float r = 0.0f;
	float increment = 0.05f;

	while (!glfwWindowShouldClose(window))
	{
		CallLog(glClear(GL_COLOR_BUFFER_BIT));

		CallLog(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));
		CallLog(glUseProgram(program));

		if (r > 1.0f)
			increment = -0.05f;
		else if (r < 0.0f)
			increment = 0.05f;
		
		r = r + increment;

		CallLog(glBindVertexArray(vao));
		CallLog(glDrawArrays(GL_TRIANGLES, 0, 3));
		CallLog(glfwSwapBuffers(window));
		CallLog(glfwPollEvents());
	}
}