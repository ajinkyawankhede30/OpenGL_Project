#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "GL/glew.h"
#include "glfw3.h"
#include "VertexBuffClass.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffClass.h"
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
//#define CAMERA_ROTATION
#define WASD_INPUT

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

//global variables
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;
float lastframe = 0.0f;

void processInputs(GLFWwindow* window);

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

	window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Graphics_Window", NULL, NULL);
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

	CallLog(glEnable(GL_DEPTH_TEST));

	//float positions[] =
	//{	//position	  color			     texture co-ord
	//	-0.5f, -0.5f, 1.0f, 0.0f, 0.0f,	 0.0f, 0.0f, 	//0th index
	//	 0.5,  -0.5f, 0.0f, 1.0f, 0.0f,  1.0f, 0.0f,		//1 
	//	 0.5f,  0.5f, 0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,		//2
	//	-0.5f,  0.5f, 0.0f, 1.0f, 0.0f,  0.0f, 1.0f,//3rd index
	//};

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


	CallLog(glEnable(GL_BLEND));
	CallLog(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	//Vertex Array object
	VertexArray vao;


	//Vertex buffer object
	VertexBuffer vbo(positions, sizeof(positions));


	VertexBufferLayout bff_layout;
	bff_layout.Push<float>(3); //vertex position attribute
	bff_layout.Push<float>(3); //colors attribute
	bff_layout.Push<float>(2); //texture coord attribute

	vao.AddBuffer(vbo, bff_layout);
	vao.Bind();

	//Index buffer object
	IndexBuffer ibo(indices, 36);


	Shaders myshader("src\\Shader_main.txt");
	myshader.Bind();

	Textures my_texture("resources\\wall2.jfif");
	my_texture.Bind();
	myshader.SetUniform1i("ourTexture", 0);

	vao.Unbind();
	myshader.UnBind();
	vbo.Unbind();
	ibo.Unbind();


	glm::vec3 cubePositions[] =
	{
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -5.5f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -5.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -4.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	//apply perspective
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 100.0f);


	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		my_texture.Bind();

#ifdef WASD_INPUT
		{

			float currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastframe;
			lastframe = currentFrame;

			processInputs(window);

			glm::mat4 view = glm::lookAt(cameraPos, (cameraPos + cameraFront), cameraUp);
			myshader.SetUniformMat4f("view", view);
			myshader.SetUniformMat4f("projection", projection);

			vao.Bind();
			int len = sizeof(cubePositions) / sizeof(glm::vec3);

			for (unsigned int i = 0; i < len; i++)
			{
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, cubePositions[i]);
				model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
				myshader.SetUniformMat4f("model", model);
				myshader.Bind();
				ibo.Bind();
				glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
			}
		}
#endif // WASD_INPUT

#ifdef CAMERA_ROTATION

		{
			glm::mat4 model = glm::mat4(1.0f);
			glm::mat4 view = glm::mat4(1.0f);
			//glm::mat4 projection = glm::mat4(1.0f);

			float radius = 10.0f;
			float camX = static_cast<float> (glm::sin(glfwGetTime()) * radius);
			float camZ = static_cast<float> (glm::cos(glfwGetTime()) * radius);

			//camera position		//model position (origin)		//up-direction vector
			view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

			//apply perspective
			//projection = glm::perspective(glm::radians(45.0f), (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 100.0f);

			//set uniform value in shader
			//myshader.SetUniformMat4f("model", model);
			myshader.SetUniformMat4f("view", view);
			myshader.SetUniformMat4f("projection", projection);

			//myshader.Bind();
			//glUseProgram(program);

			vao.Bind();
			int arry_len = sizeof(cubePositions) / sizeof(glm::vec3);
			for (unsigned int i = 0; i < arry_len; i++)
			{
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, cubePositions[i]);
				//float angle = 20.0f * i;
				//model = glm::rotate(model, glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
				model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f)); // z-axis
				myshader.SetUniformMat4f("model", model);
				myshader.Bind();
				ibo.Bind();
				glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

			}
		}

		//ibo.Bind();
		//glBindVertexArray(vao);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
#endif // CAMERA_ROTATION

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

#ifdef WASD_INPUT
void processInputs(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	float cameraSpeed = static_cast<float>(2.5f * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

}

#endif // WASD_INPUT
