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
	std::cout << glGetString(GL_VERSION) << std::endl;
	std::cout << glGetString(GL_RENDERER) << std::endl;

	if (glewInit() != GLEW_OK)
		std::cout << "Error Initializing glew..." << std::endl;


	//float vertices[] = {
	//	-0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	//	0.5f, -0.5f,  0.0f, 1.0f,  0.0f,
	//	0.0f, 0.5f,   0.0f, 0.0f, 1.0f
	//};

	//Triangle upside down
	float vertices[] = {
	-0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f,  0.0f, 1.0f,  0.0f,
	0.0f, -0.5f,   0.0f, 0.0f, 1.0f
	};

	//Create a vertex buffer
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Create vertex array object
	unsigned int vao;
	CallLog(glGenVertexArrays(1, &vao));
	CallLog(glBindVertexArray(vao));
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(1);
	
	CallLog(glEnableVertexAttribArray(0));
	CallLog(glEnableVertexAttribArray(1));

	const char* vertex_shader =
		"#version 400 core\n"
		"\n"
		"layout (location = 0) in vec2 positions;\n"
		"layout (location = 1) in vec3 v_colors;\n"

		"out vec3 colours;\n"

		"void main()\n"
		"{\n"
		"    gl_Position = vec4(positions, 0.0, 1.0);\n"
		"    colours = v_colors;\n"	
		"}\n";

	const char* fragment_shader =
		"#version 400 core\n"
		"\n"
		"in vec3 colours;\n"
		"out vec4 frag_colour;\n"

		"void main()\n"
		"{\n"
			"frag_colour = vec4(colours, 1.0);"
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

	glBindAttribLocation(program, 0, "positions");
	glBindAttribLocation(program, 1, "v_colors");

	CallLog(glLinkProgram(program));
	CallLog(glValidateProgram(program));
	//CallLog(glUseProgram(program));
	

	glDeleteShader(vx_shader);
	glDeleteShader(fg_shader);

	while (!glfwWindowShouldClose(window))
	{
		CallLog(glClear(GL_COLOR_BUFFER_BIT));
		CallLog(glUseProgram(program));
		CallLog(glBindVertexArray(vao));
		CallLog(glDrawArrays(GL_TRIANGLES, 0, 3));
		CallLog(glfwSwapBuffers(window));
		CallLog(glfwPollEvents());

		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window,1);
		}
	}
}