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

	window = glfwCreateWindow(640, 440, "Two Triangles", NULL, NULL);

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
		-0.9f, -0.5f,  // left 
		-0.0f, -0.5f,  // right
		-0.45f, 0.5f  // top 
	};				 

	float positions2[] =
	{
		0.0f, -0.5f,  // left
		0.9f, -0.5f,  // right
		0.45f, 0.5f  // top 
	};

	//create buffer vbo1, vbo2
	unsigned int vbo[2], vao[2];

	CallLog(glGenVertexArrays(2, vao));
	CallLog(glGenBuffers(2, vbo));

	CallLog(glBindVertexArray(vao[0]));
	CallLog(glBindBuffer(GL_ARRAY_BUFFER, vbo[0]));
	CallLog(glBufferData(GL_ARRAY_BUFFER, sizeof(positions1), positions1, GL_STATIC_DRAW));
	CallLog(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (void*)0));
	CallLog(glEnableVertexAttribArray(0));

	CallLog(glBindVertexArray(vao[1]));
	CallLog(glBindBuffer(GL_ARRAY_BUFFER, vbo[1]));
	CallLog(glBufferData(GL_ARRAY_BUFFER, sizeof(positions2), positions2, GL_STATIC_DRAW));
	CallLog(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (void*)0));
	CallLog(glEnableVertexAttribArray(0));

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
		"out vec4 color1; \n"
		"void main()\n"
		"{\n"
		"color1 = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
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
		glClear(GL_COLOR_BUFFER_BIT);


		CallLog(glUseProgram(program));

		CallLog(glBindVertexArray(vao[0]));
		CallLog(glDrawArrays(GL_TRIANGLES, 0, 3));

		CallLog(glBindVertexArray(vao[1]));
		CallLog(glDrawArrays(GL_TRIANGLES, 0, 3));

		CallLog(glfwSwapBuffers(window));
		CallLog(glfwPollEvents());

		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window, 1);
		}
	}

	CallLog(glDeleteVertexArrays(2, vao));
	CallLog(glDeleteBuffers(2,vbo));
	CallLog(glDeleteProgram(program));

	glfwTerminate();
	return 0;
}
