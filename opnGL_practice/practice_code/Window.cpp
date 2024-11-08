#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include </openGL/My_Projects/opnGL_practice/Dependencies/includes/GL/glew.h>
#include </openGL/My_Projects/opnGL_practice/Dependencies/includes/glfw3.h>

#pragma region Practice_CreateShader_Program
static int CompileShad(unsigned int type, const std::string& shader)
{
	unsigned int id = glCreateShader(type);
	const char* source = shader.c_str();
	glShaderSource(id, 1, &source, NULL);
	glCompileShader(id);

	//error handling
	int success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (success != GL_TRUE)
	{
		int msg_length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &msg_length);
		char* log_message = (char*)alloca(msg_length * sizeof(char));
		glGetShaderInfoLog(id, msg_length, &msg_length, log_message);
		std::cout << "Compilation Error: " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "\n" << log_message << "\n";
		glDeleteShader(id);
	}
	return id;
}

static int CreateShad(const std::string& vertexShad, const std::string& fragmentShad)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShad(GL_VERTEX_SHADER, vertexShad);
	unsigned int fs = CompileShad(GL_FRAGMENT_SHADER, fragmentShad);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}
#pragma endregion

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

struct ShaderProgramSource
{
	std::string VertexShader;
	std::string FragmentShader;
};

static ShaderProgramSource ParseShader(const std::string& filePath)
{
	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1,
	};

	std::fstream read(filePath);
	std::string line;
	ShaderType type = ShaderType::NONE;
	std::stringstream ss[2];
	while (std::getline(read, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << "\n";
		}
	}

	return { ss[0].str(), ss[1].str() };
}

int main()
{
	GLFWwindow* window;

	//Initialize the library
	if (!glfwInit())
	{
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE); //user for vertex arrays
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); //default 

	//Create window
	window = glfwCreateWindow(650, 450, "My_Window", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	//Make window context current
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	//initialize glew lib
	if (glewInit() != GLEW_OK)
		std::cout << "Error initializing glew..." << std::endl;

	//print version og 
	std::cout << glGetString(GL_VERSION) << std::endl;

	float positions[] = {
		-0.5f, -0.5f, //0th index
		 0.5,  -0.5f, //1 
		 0.5f, 0.5f,  //2
		 -0.5f, 0.5f  //3rd index
	};

	unsigned int indicies[] = {
	0,1,2,
	2,3,0
	};
	
	//Create vertex array
	unsigned int vao;
	CallLog(glGenVertexArrays(1, &vao));
	CallLog(glBindVertexArray(vao));

	//Generate buffer (a bunch of memory)
	unsigned int buffer;  //create vertex buffer object
	glGenBuffers(1, &buffer);

	//select buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	//assign data to buffer
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

	//enable vertex attribute
	glEnableVertexAttribArray(0);

	//assign attributes
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	//Create index buffer object - ibo
	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indicies, GL_STATIC_DRAW);


#pragma region shader_String
	std::string vertexShader =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec4 position;\n"
		"void main()\n"
		"{\n"
		"	gl_position = position;\n"
		"}\n";

	std::string fragmentShader =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) out vec4 color;\n"
		"void main()\n"
		"{\n"
		"	color = vec4(1.0,0.0,0.0,1.0);\n"
		"}\n";
#pragma endregion

#pragma region ShaderSrcProgram
	std::string vertexShad =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec4 position;\n"
		"void main()\n"
		"{\n"
		"	gl_position = position;\n"
		"}\n";

	std::string fragmentShad =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) out vec4 color;\n"
		"void main()\n"
		"{\n"
		"	color = vec4(1.0,0.5f,0.25f,0.0);\n"
		"}\n";
#pragma endregion


	ShaderProgramSource source = ParseShader("src/Basic_uniform.shader");
	std::cout << "VERTEX " << std::endl;
	std::cout << source.VertexShader << std::endl;
	std::cout << "FRAGMENT " << std::endl;
	std::cout << source.FragmentShader << std::endl;

	unsigned int shader = CreateShader(source.VertexShader, source.FragmentShader);
	//unsigned int shader = CreateShader(vertexShader, fragmentShader);
	//unsigned int shader = CreateShad(vertexShad, fragmentShad);
	glUseProgram(shader);

	CallLog(int location = glGetUniformLocation(shader, "u_color"));
	ASSERT(location != 1);
	//CallLog(glUniform4f(location, 0.8f, 0.3f, 0.8f, 1.0f));

	//unbind buffer
	glBindVertexArray(0);
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	float r = 0.1f;
	float increment = 0.05f;

	//loop till window is closed by user
	while (!glfwWindowShouldClose(window))
	{
		//Render
		glClear(GL_COLOR_BUFFER_BIT);

		//bind shader
		glUseProgram(shader);
		CallLog(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));

		/*Note: After vertex array is created, there is no need to bind vertex buffer & assign vertex attribute
		Just need to bind the vertex array */
		 
		//glBindBuffer(GL_ARRAY_BUFFER, buffer);
		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

		//bind vertex array
		glBindVertexArray(vao);

		//bind index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		//CallLog(glDrawElements(GL_TRIANGLES, 6, GL_INT, nullptr));


		CallLog(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

		if (r > 1.0f)
		{
			increment = -0.05f;
		}
		else if (r < 0.0f)
		{
			increment = 0.05f;
		}

		r += increment;
		//Swap front and back buffer
		glfwSwapBuffers(window);

		//Poll for and process events
		glfwPollEvents();

	}

	glfwTerminate();
	return 0;
}