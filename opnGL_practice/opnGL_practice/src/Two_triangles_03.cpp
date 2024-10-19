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

	//LEFT TRIANGLE
	float positions1[] = {
		-0.9f, -0.5f,  // left 
		-0.0f, -0.5f,  // right
		-0.45f, 0.5f  // top 
	};				 

	//RIGHT TRIANGLE
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

	//vertex_shaders
	const char* vertex_shader =
		"#version 430 core \n"
		"layout (location = 0) in vec2 positions1;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(positions1 ,0.0f, 1.0f);\n"
		"}\n";

	//fragment_shaders_Orange
	const char* fragment_shader1 =
		"#version 430 core \n"
		"out vec4 color1; \n"
		"void main()\n"
		"{\n"
		"color1 = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n";

	//fragment_shader_Magenta
	const char* fragment_shader2 =
		"#version 430 core \n"
		"out vec4 color1; \n"
		"void main()\n"
		"{\n"
		"color1 = vec4(0.25f, 0.25f, 0.75f, 1.0f);\n"
		"}\n";

	//compile vertex shader
	unsigned int vertex_source = glCreateShader(GL_VERTEX_SHADER);
	CallLog(glShaderSource(vertex_source, 1, &vertex_shader, NULL));
	CallLog(glCompileShader(vertex_source));

	//compile fragment shader_Orange
	unsigned int fragment_source1 = glCreateShader(GL_FRAGMENT_SHADER);
	CallLog(glShaderSource(fragment_source1, 1, &fragment_shader1, NULL));
	CallLog(glCompileShader(fragment_source1));

	//compile fragment shader_Magenta
	unsigned int fragment_source2 = glCreateShader(GL_FRAGMENT_SHADER);
	CallLog(glShaderSource(fragment_source2, 1, &fragment_shader2, NULL));
	CallLog(glCompileShader(fragment_source2));

	//Create program for Triagle1
	unsigned int program1 = glCreateProgram();
	CallLog(glAttachShader(program1, vertex_source)); //same vertex shader
	CallLog(glAttachShader(program1, fragment_source1));
	CallLog(glLinkProgram(program1));
	glValidateProgram(program1);

	//Create program for Triagle2
	unsigned int program2 = glCreateProgram();
	CallLog(glAttachShader(program2, vertex_source)); //same vertex shader
	CallLog(glAttachShader(program2, fragment_source2));
	CallLog(glLinkProgram(program2));
	glValidateProgram(program2);

	CallLog(glDeleteShader(vertex_source));
	CallLog(glDeleteShader(fragment_source1));
	CallLog(glDeleteShader(fragment_source2));

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		//Program for Triangle1
		CallLog(glUseProgram(program1));
		CallLog(glBindVertexArray(vao[0]));
		CallLog(glDrawArrays(GL_TRIANGLES, 0, 3));

		//Program for Triangle2
		CallLog(glUseProgram(program2));
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
	CallLog(glDeleteProgram(program1));
	CallLog(glDeleteProgram(program2));

	glfwTerminate();
	return 0;
}
