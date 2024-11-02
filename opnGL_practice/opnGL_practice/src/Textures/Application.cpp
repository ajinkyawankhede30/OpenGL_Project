#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "GL/glew.h"
#include "glfw3.h"
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

#define OBJECT_02

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
/*
	float positions[] =
	{	//position	  color			     texture co-ord
		-0.5f, -0.5f, 1.0f, 0.0f, 0.0f,	 1.0f, 1.0f,	//0th index
		 0.5,  -0.5f, 0.0f, 1.0f, 0.0f,  1.0f, 0.0f,	//1 
		 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,	 0.0f, 0.0f,	//2
		 -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,  0.0f, 1.0f     //3rd index
	};
*/

	float positions[] =
	{	//position	  color			     texture co-ord
		-0.5f, -0.5f, 1.0f, 0.0f, 0.0f,	 0.0f, 0.0f, 	//0th index
		 0.5,  -0.5f, 0.0f, 1.0f, 0.0f,  1.0f, 0.0f,		//1 
		 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,		//2
		 -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,  0.0f, 1.0f	   //3rd index
	};

	unsigned int indices[] =
	{
		0,1,2,
		2,3,0
	};


	CallLog(glEnable(GL_BLEND));
	CallLog(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 4 * 7 * sizeof(float), positions, GL_STATIC_DRAW);

	//enable vertex/position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);

	//enable color attributes
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2 * sizeof(GL_FLOAT)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(GL_FLOAT)));

	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	
	Shaders myshader("src\\Shader_main.txt");
	myshader.Bind();

	Textures my_texture("resources\\download.png");
	my_texture.Bind();
	myshader.SetUniform1i("ourTexture", 0);
/*
	glm::vec4 vector(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans = glm::mat4(1.0f); //identity matrix
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));

	vector = trans * vector;
	std::cout << vector.x << vector.y << vector.z << "\n";
*/

	glBindVertexArray(0);
	//glUseProgram(0);
	myshader.UnBind();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	float move_x = 1.5f;
	float dx = 0.01f;

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		my_texture.Bind();

		glm::mat4 transform = glm::mat4(1.0f);
		//scale
		transform = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
		//translate
		transform = glm::translate(transform, glm::vec3(move_x, -0.5f, 0.0f));
		//rotate
		transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		
		if (move_x > 1.5f)
			dx = -0.01f;
		else if (move_x < -1.5f)
			dx = 0.01f;

		move_x += dx;

		//set uniform value in shader
		myshader.SetUniformMat4f("u_transform", transform);

		myshader.Bind();
		//glUseProgram(program);

		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

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

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &buffer);
	//glDeleteProgram(program);

	glfwTerminate();
	return 0;
}