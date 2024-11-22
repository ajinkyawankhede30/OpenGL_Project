#include <iostream>
#include <GL/glew.h>
#include <glfw3.h>
#include <string>
#include <fstream>

#define ASSERT(x) if(!x) __debugbreak
#define CallLog(x) GLClearError();\
	x;\
	GLCallLog(#x, __FILE__, __LINE__)

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLCallLog(const char* function, const char* file, int line)
{
	if (GLenum error = glGetError())
	{
		std::cout << "[OpenGL ERROR] ( " << error << " ) " << ": " << function << ": " << file << ": " << line << "\n";
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

	window = glfwCreateWindow(640, 440, "Rectangle", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	std::cout << glGetString(GL_VERSION) << "\n";
	std::cout << glGetString(GL_RENDERER) << "\n";

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error initializing glew...\n";
		return -1;
	}

	float positions[] = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f,
		- 0.5f, 0.5f
	};

	//int indices[] = {
	//	0,1,2,
	//	2,3,0
	//};
	
	int indices2[] = {
		0,1,2,
		0,3,2
	};

	unsigned int vao;
	CallLog(glGenVertexArrays(1, &vao));
	CallLog(glBindVertexArray(vao));

	unsigned int vbo;
	CallLog(glGenBuffers(1, &vbo));
	CallLog(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	CallLog(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));

	CallLog(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0));
	CallLog(glEnableVertexAttribArray(0));

	// index buffer
	unsigned int ibo2;
	glGenBuffers(1, &ibo2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices2, GL_STATIC_DRAW);

	//Index buffer object
	//unsigned int ibo;
	//CallLog(glGenBuffers(1, &ibo));
	//CallLog(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
	//CallLog(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

	const char* vertex_source =
		"#version 430 core\n"
		"\n"
		"layout (location = 0) in vec2 positions;\n"

		"void main()\n"
		"{\n"
			"gl_Position = vec4(positions, 0.0, 1.0);\n"
		"}\n";

	const char* fragment_source =
		"#version 430 core\n"
		"\n"
		"layout (location = 0) out vec4 color;\n"
		"void main()\n"
		"{\n"
			"color = vec4(1.0f, 1.25f, 0.25f, 1.0f);\n"
		"}\n";

	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	CallLog(glShaderSource(vertex_shader, 1, &vertex_source, NULL));
	CallLog(glCompileShader(vertex_shader));

	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	CallLog(glShaderSource(fragment_shader, 1, &fragment_source, NULL));
	CallLog(glCompileShader(fragment_shader));

	unsigned int program = glCreateProgram();
	CallLog(glAttachShader(program, vertex_shader));
	CallLog(glAttachShader(program, fragment_shader));

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	while (!glfwWindowShouldClose(window))
	{
		CallLog(glClear(GL_COLOR_BUFFER_BIT));
		CallLog(glUseProgram(program));
		CallLog(glBindVertexArray(vao));
		//CallLog(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		CallLog(glfwSwapBuffers(window));
		CallLog(glfwPollEvents());

		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window, 1);
		}
	}

	CallLog(glDeleteVertexArrays(1, &vao));
	CallLog(glDeleteBuffers(1, &vbo));
	//CallLog(glDeleteBuffers(1, &ibo));
	glDeleteBuffers(1, &ibo2);
	CallLog(glDeleteProgram(program));

	glfwTerminate();
}