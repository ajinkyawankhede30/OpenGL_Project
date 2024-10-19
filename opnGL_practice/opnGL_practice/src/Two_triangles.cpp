#include <iostream>
#include <GL/glew.h>
#include <glfw3.h>
#include <fstream>
#include <string>

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

	window = glfwCreateWindow(440, 440, "Two Triangles", NULL, NULL);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error initializing GLEW\n";
		return -1;
	}

	float positions1[] = {
		-1.0f, -0.5f,
		-0.75f,0.5f,
		-0.5f, -0.5f,

		0.5f, -0.5f,
		0.75f,0.5f,
		1.0f, -0.5f
	};

	//create buffer vbo1, vbo2
	unsigned int vbo1, vao;

	CallLog(glGenBuffers(1, &vbo1));
	CallLog(glBindBuffer(GL_ARRAY_BUFFER, vbo1));
	CallLog(glBufferData(GL_ARRAY_BUFFER, sizeof(positions1), positions1, GL_STATIC_DRAW));

	CallLog(glGenVertexArrays(1, &vao));
	CallLog(glBindVertexArray(vao));
	CallLog(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (void*)0));

	CallLog(glEnableVertexAttribArray(0));

	//unbind vbo
	CallLog(glBindBuffer(GL_ARRAY_BUFFER, 0));
	CallLog(glBindVertexArray(0));

	//shaders
	const char* vertex_shader =
		"#version 430 core \n"
		"layout (location = 0) in vec2 positions1;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(positions1 ,0.0f, 1.0f);\n"
		"}\n";

	const char* fragment_shader =
		"#version 430 core \n"
		"out vec4 colors; \n"
		"void main()\n"
		"{\n"
		"colors = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n";

	unsigned int vertex_source = glCreateShader(GL_VERTEX_SHADER);
	CallLog(glShaderSource(vertex_source, 1, &vertex_shader, NULL));
	CallLog(glCompileShader(vertex_source));

	unsigned int fragment_source = glCreateShader(GL_FRAGMENT_SHADER);
	CallLog(glShaderSource(fragment_source, 1, &fragment_shader, NULL));
	CallLog(glCompileShader(fragment_source));

	unsigned int program = glCreateProgram();
	CallLog(glAttachShader(program, vertex_source));
	CallLog(glAttachShader(program, fragment_source));
	CallLog(glLinkProgram(program));
	glValidateProgram(program);

	CallLog(glDeleteShader(vertex_source));
	CallLog(glDeleteShader(fragment_source));

	while (!glfwWindowShouldClose(window))
	{
		CallLog(glfwSwapBuffers(window));
		CallLog(glfwPollEvents());
		CallLog(glUseProgram(program));
		CallLog(glBindVertexArray(vao));
		CallLog(glDrawArrays(GL_TRIANGLES, 0, 6));

		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window, 1);
		}
	}

	CallLog(glDeleteVertexArrays(1, &vao));
	CallLog(glDeleteBuffers(1,&vbo1));
	CallLog(glDeleteProgram(program));

	glfwTerminate();
	return 0;
}
