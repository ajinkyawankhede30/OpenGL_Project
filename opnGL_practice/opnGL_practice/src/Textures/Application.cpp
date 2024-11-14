#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "GL/glew.h"
#include "glfw3.h"

#include "VertexBuffClass.h"
#include "VertexArray.h"
#include "IndexBuffClass.h"
#include "VertexBufferLayout.h"
#include "Shaders.h"
#include  "Textures.h"

#ifndef GLM_HEADERS
#define GLM_HEADERS 

//glm includes
#include "glm/glm.hpp"
#include "glm/vec4.hpp"
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

#endif // !GLM_HEADERS

//#define OBJECT_02

using namespace glm;

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

const unsigned int WIN_WIDTH = 960;
const unsigned int WIN_HEIGHT = 540;

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

	window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Graphic_Window", NULL, NULL);
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

	/*
	float positions[] =
	{	//position	  color			     texture co-ord
		-0.5f, -0.5f, 1.0f, 0.0f, 0.0f,	 0.0f, 0.0f, 	//0th index
		 0.5,  -0.5f, 0.0f, 1.0f, 0.0f,  1.0f, 0.0f,		//1 
		 0.5f,  0.5f, 0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,		//2
		-0.5f,  0.5f, 0.0f, 1.0f, 0.0f,  0.0f, 1.0f	   //3rd index
	};
	*/

	float positions[] =
	{	//vertices				//colors			//texture_coord
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,

		-0.5f, -0.5f, 0.5f,   1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
		 0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, 0.5f,   0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,
		-0.5f,  0.5f, 0.5f,   0.0f, 1.0f, 0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,

		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,

	};

	unsigned int indices[] =
	{
		0,1,2,
		2,3,0,

		4,5,6,
		6,7,4,

		7,3,0,
		0,4,7,

		6,2,1,
		1,5,6,

		0,1,5,
		5,4,0,

		3,2,6,
		6,7,3
	};
	
	/*
	unsigned int indices[] =
	{
		0,1,2,
		2,3,0
	};
	*/

	CallLog(glEnable(GL_DEPTH_TEST));
	CallLog(glEnable(GL_BLEND));
	CallLog(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	
	VertexArray vao;
	//unsigned int vao;
	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);

	VertexBuffer vbo(positions, sizeof(positions));
	//unsigned int buffer;
	//glGenBuffers(1, &buffer);
	//glBindBuffer(GL_ARRAY_BUFFER, buffer);
	//glBufferData(GL_ARRAY_BUFFER, 6 * 4 * 8 * sizeof(float), positions, GL_STATIC_DRAW);

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);

	vao.AddBuffer(vbo, layout);
	vao.Bind();

	//enable vertex/position attribute
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

	//enable color attributes
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(GL_FLOAT)));

	//glEnableVertexAttribArray(2);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(GL_FLOAT)));

	IndexBuffer ibo(indices, 36);
	//unsigned int ibo;
	//glGenBuffers(1, &ibo);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	
	Shaders myshader("src\\Shader_main.txt");
	myshader.Bind();

	Textures my_texture("resources\\wall2.jfif");
	my_texture.Bind();
	myshader.SetUniform1i("ourTexture", 0);

	vao.Unbind();
	myshader.UnBind();
	vbo.Unbind();
	ibo.Unbind();
	
	//glBindVertexArray(0);
	//glUseProgram(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glm::vec3 cameraPositions[] =
	{
		glm::vec3(1.0f, 0.5f, 0.0f),
		glm::vec3(3.0f, -0.5f, 0.0f),
		glm::vec3(-2.5f, -7.5f, -5.0f),
		glm::vec3(-3.0f, 0.5f, 0.0f),

	};

	// world space positions of our cubes
	glm::vec3 cubePositions[] = 
	{
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(5.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(6.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		my_texture.Bind();

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		//rotate along x-axis
		//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, (float)(glfwGetTime()), glm::vec3(0.5f, 1.0f, 0.0f));

		//translate/ zoom out in +ve z-direction OR zoom-in in -ve direction
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		//apply perspective
		projection = glm::perspective(glm::radians(45.0f), (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 100.0f);

		//set uniform value in shader
		//myshader.SetUniformMat4f("model", model);
		myshader.SetUniformMat4f("view", view);
		myshader.SetUniformMat4f("projection", projection);

		for (int  i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(-0.5f, 1.0f, 0.0f));
			myshader.SetUniformMat4f("model", model);
			myshader.Bind();
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
		}
		 
		//myshader.Bind();

		vao.Bind();
		ibo.Bind();
		//glBindVertexArray(vao);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

#ifdef OBJECT_02
		transform = glm::mat4(1.0f);
		float scale_amount = static_cast<float> (sin(glfwGetTime()));
		transform = glm::scale(transform, glm::vec3(scale_amount));
		transform = glm::translate(transform, glm::vec3(-1.5f, 0.5f, 0.0f));
		myshader.SetUniformMat4f("u_transform", transform);
		myshader.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

#endif // OBJECT_02

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//glDeleteVertexArrays(1, &vao);
	//glDeleteBuffers(1, &buffer);
	//glDeleteProgram(program);

	glfwTerminate();
	return 0;
}