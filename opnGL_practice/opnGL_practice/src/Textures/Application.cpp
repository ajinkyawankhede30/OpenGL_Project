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
#include "Textures.h"
#include "Camera.h"


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

//global variables
const unsigned int WIN_WIDTH = 960;
const unsigned int WIN_HEIGHT = 540;

camera::Camera fly_camera(glm::vec3(0.0f, 0.0f, 3.0f));
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


bool firstMouse = true;
//float yaw = -90.0f; // yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
//float pitch = 0.0f;
float lastX = static_cast<float>(WIN_WIDTH / 2.0f);
float lastY = static_cast<float>(WIN_HEIGHT / 2.0f);
//float fov = 45.0f;

float deltaTime = 0.0f;
float lastframe = 0.0f;

//declaration
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
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
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

	//float positions[] =
	//{	//vertices				//colors			//texture_coord
	//	-0.5f, -0.5f, -0.5f,  //1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
	//	 0.5f, -0.5f, -0.5f,  //0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
	//	 0.5f,  0.5f, -0.5f,  //0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,
	//	-0.5f,  0.5f, -0.5f,  //0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	//						  //
	//	-0.5f, -0.5f, 0.5f,   //1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
	//	 0.5f, -0.5f, 0.5f,   //0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
	//	 0.5f,  0.5f, 0.5f,   //0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,
	//	-0.5f,  0.5f, 0.5f,   //0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	//						  //
	//	-0.5f,  0.5f,  0.5f,  //1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
	//	-0.5f,  0.5f, -0.5f,  //0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
	//	-0.5f, -0.5f, -0.5f,  //0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,
	//	-0.5f, -0.5f,  0.5f,  //0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	//						  //
	//	 0.5f,  0.5f,  0.5f,  //1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
	//	 0.5f,  0.5f, -0.5f,  //0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
	//	 0.5f, -0.5f, -0.5f,  //0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,
	//	 0.5f, -0.5f,  0.5f,  //0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	//						  //
	//	-0.5f, -0.5f, -0.5f,  //1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
	//	 0.5f, -0.5f, -0.5f,  //0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
	//	 0.5f, -0.5f,  0.5f,  //0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,
	//	-0.5f, -0.5f,  0.5f,  //0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	//						  //
	//	-0.5f,  0.5f, -0.5f,  //1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
	//	 0.5f,  0.5f, -0.5f,  //0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
	//	 0.5f,  0.5f,  0.5f,  //0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,
	//	-0.5f,  0.5f,  0.5f,  //0.0f, 1.0f, 0.0f,  0.0f, 1.0f,

	//};
	
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	float light_vertices[] = {
		-0.5f, -0.5f, -0.5f, 
		 0.5f, -0.5f, -0.5f, 
		 0.5f,  0.5f, -0.5f, 
		 0.5f,  0.5f, -0.5f, 
		-0.5f,  0.5f, -0.5f, 
		-0.5f, -0.5f, -0.5f, 
		
		-0.5f, -0.5f,  0.5f, 
		 0.5f, -0.5f,  0.5f, 
		 0.5f,  0.5f,  0.5f, 
		 0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f,  0.5f, 
		-0.5f, -0.5f,  0.5f, 
		
		-0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f, -0.5f, 
		-0.5f, -0.5f, -0.5f, 
		-0.5f, -0.5f, -0.5f, 
		-0.5f, -0.5f,  0.5f, 
		-0.5f,  0.5f,  0.5f, 
		
		 0.5f,  0.5f,  0.5f, 
		 0.5f,  0.5f, -0.5f, 
		 0.5f, -0.5f, -0.5f, 
		 0.5f, -0.5f, -0.5f, 
		 0.5f, -0.5f,  0.5f, 
		 0.5f,  0.5f,  0.5f, 
		
		-0.5f, -0.5f, -0.5f, 
		 0.5f, -0.5f, -0.5f, 
		 0.5f, -0.5f,  0.5f, 
		 0.5f, -0.5f,  0.5f, 
		-0.5f, -0.5f,  0.5f, 
		-0.5f, -0.5f, -0.5f, 
		
		-0.5f,  0.5f, -0.5f, 
		 0.5f,  0.5f, -0.5f, 
		 0.5f,  0.5f,  0.5f, 
		 0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f, -0.5f 
	};

	//unsigned int indices[] =
	//{
	//	0,1,2,
	//	2,3,0,

	//	4,5,6,
	//	6,7,4,

	//	7,3,0,
	//	0,4,7,

	//	6,2,1,
	//	1,5,6,

	//	0,1,5,
	//	5,4,0,

	//	3,2,6,
	//	6,7,3
	//};


	CallLog(glEnable(GL_BLEND));
	CallLog(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	//Vertex Array objects
	VertexArray vao, light_vao;

	//Vertex buffer object
	VertexBuffer vbo(vertices, sizeof(vertices));

	VertexBufferLayout bff_layout, layout2;
	bff_layout.Push<float>(3); //vertex position attribute
	bff_layout.Push<float>(3); //normal vector attribute
	//bff_layout.Push<float>(3); //colors attribute
	//bff_layout.Push<float>(2); //texture coord attribute

	vao.AddBuffer(vbo, bff_layout);
	vao.Bind();

	VertexBuffer vbo2(light_vertices, sizeof(light_vertices));
	layout2.Push<float>(3);

	light_vao.AddBuffer(vbo2, layout2);
	light_vao.Bind();
	
	//Index buffer object
	//IndexBuffer ibo(indices, 36);

	Shaders myshader("src\\Shader_main.txt");
	Shaders light_shader("src\\Light_Source_Shader.txt");

	
	//Textures my_texture("resources\\wall2.jfif");
	//my_texture.Bind();
	//myshader.SetUniform1i("ourTexture", 0);

	//ibo.Unbind();
	vao.Unbind();
	light_vao.Unbind();

	glm::vec3 lightPos(2.0f, 0.0f, -1.0f);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//my_texture.Bind();
#ifdef WASD_INPUT
		{
			float currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastframe;
			lastframe = currentFrame;

			processInputs(window);

			myshader.Bind();

			glm::mat4 view = fly_camera.GetViewMatrix();
			glm::mat4 projection = glm::mat4(1.0f);
			projection = glm::perspective(glm::radians(fly_camera.Zoom), (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 100.0f);
			glm::mat4 model = glm::mat4(1.0f);

			
			myshader.SetUniformMat4f("view", view);
			myshader.SetUniformMat4f("projection", projection);
			myshader.SetUniformMat4f("model", model);
			//myshader.SetUniformVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
			myshader.SetUniformVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
			myshader.SetUniformVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
			myshader.SetUniformVec3("lightPos", lightPos);

			vao.Bind();
			glDrawArrays(GL_TRIANGLES, 0, 36);
			//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);

			light_shader.Bind();
			model = glm::translate(model, lightPos);
			model = glm::scale(model, glm::vec3(0.5f));

			light_shader.SetUniformMat4f("model", model);
			light_shader.SetUniformMat4f("view", view);
			light_shader.SetUniformMat4f("projection", projection);
			light_shader.SetUniformVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
			light_vao.Bind();
			glDrawArrays(GL_TRIANGLES, 0, 36);
			//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);

		}
#endif //WASD_INPUT

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

	//float cameraSpeed = static_cast<float>(2.5f * deltaTime);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		fly_camera.ProcessKeyboard(camera::Camera_Movement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		fly_camera.ProcessKeyboard(camera::Camera_Movement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		fly_camera.ProcessKeyboard(camera::Camera_Movement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		fly_camera.ProcessKeyboard(camera::Camera_Movement::RIGHT, deltaTime);

}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xPos = static_cast<float>(xposIn);
	float yPos = static_cast<float>(yposIn);


	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xoffset = xPos - lastX;
	float yoffset = lastY - yPos; // reversed since y-coordinates go from bottom to top
	lastX = xPos;
	lastY = yPos;
	
	fly_camera.ProcessMouseMovement(xoffset, yoffset);

	//float sensitivity = 0.1f;
	//xoffset *= sensitivity;
	//yoffset *= sensitivity;

	//yaw += xoffset;
	//pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	//if (pitch > 89.0f)
	//	pitch = 89.0f;
	//if (pitch < -89.0f)
	//	pitch = -89.0f;

	//glm::vec3 front;
	//front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	//front.y = sin(glm::radians(pitch));
	//front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	//cameraFront = glm::normalize(front);

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	fly_camera.ProcessMouseScroll(static_cast<float>(yoffset));

	//fov -= (float)(yoffset);
	//if (fov < 1.0f)
	//	fov = 1.0f;
	//if (fov > 45.0f)
	//	fov = 45.0f;

}
#endif // WASD_INPUT