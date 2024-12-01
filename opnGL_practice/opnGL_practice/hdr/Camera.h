#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include "Renderer.h"
#include "glm/glm.hpp"

#endif // !CAMERA_H


namespace camera
{
	enum class Camera_Movement
	{
		FORWARD = GLFW_KEY_W,
		BACKWARD = GLFW_KEY_S,
		RIGHT = GLFW_KEY_D,
		LEFT = GLFW_KEY_A
	};

	//global const values
	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float ZOOM = 45.0f;
	const float SENSITIVITY = 0.1f;
	const float SPEED = 2.5f;

	class Camera
	{
	public:
		//camera vectors
		glm::vec3 Position;  //camera's position vector
		glm::vec3 Up;		//up vector (y axis)
		glm::vec3 Right;    // right vector (x axis)
		glm::vec3 Front;	// view

		//world
		glm::vec3 WorldUp;

		//eulers angle
		float yaw;
		float pitch;

		//camera options
		float MovementSpeed;
		float MouseSensitivity;
		float Zoom;

	public:
		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
		Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
		//~Camera();

		glm::mat4 GetViewMatrix();
		glm::mat4 GetViewMatrix(glm::vec3 Position, glm::vec3 target, glm::vec3 WorldUp);
		void ProcessKeyboard(Camera_Movement movement, float deltatime);
		void ProcessMouseMovement(float xoffset, float yoffset, GLboolean contrainPitch = true);
		void ProcessMouseScroll(float yoffset);

	private:
		void UpdateCameraVector();
	};
}