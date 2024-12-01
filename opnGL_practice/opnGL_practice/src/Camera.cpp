#include "Camera.h"

using namespace camera;

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw , float pitch)
	:Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = position;
	WorldUp = up;
	Camera::yaw = yaw;
	Camera::pitch = pitch;
	UpdateCameraVector();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw = YAW, float pitch = PITCH)
	:Front(glm::vec3(0.0f,0.0f,-1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Front = glm::vec3(posX, posY, posZ);
	WorldUp = glm::vec3(upX, upY, upZ);
	Camera::yaw = yaw;
	Camera::pitch = pitch;
	UpdateCameraVector();
}

void Camera::UpdateCameraVector()
{
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	Front = glm::normalize(front);

	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, (Position + Front), Up);
}

glm::mat4 Camera::GetViewMatrix(glm::vec3 Position, glm::vec3 target, glm::vec3 WorldUp)
{
	
	//glm::mat4 trans_matr = glm::mat4(glm::vec4(1.0f, 0.0f, 0.0f,-Position.x), glm::vec4(0.0f, 1.0f, 0.0f, -Position.y), glm::vec4(0.0f, 0.0f, 1.0f, -Position.z), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	
	glm::vec3 z_axis = glm::normalize(Position + target);
	glm::vec3 x_axis = glm::normalize(glm::cross(WorldUp, z_axis));
	glm::vec3 y_axis = (glm::cross(z_axis, x_axis));
	
	glm::mat4 trans_matr(1.0f);
	trans_matr[3][0] = -Position.x;
	trans_matr[3][1] = -Position.y;
	trans_matr[3][2] = -Position.z;
	
	glm::mat4 rot_matr = glm::mat4(1.0f);
	rot_matr[0][0] = x_axis.x; // First column, first row
	rot_matr[1][0] = x_axis.y;
	rot_matr[2][0] = x_axis.z;
	rot_matr[0][1] = y_axis.x; // First column, second row
	rot_matr[1][1] = y_axis.y;
	rot_matr[2][1] = y_axis.z;
	rot_matr[0][2] = z_axis.x; // First column, third row
	rot_matr[1][2] = z_axis.y;
	rot_matr[2][2] = z_axis.z;
/*	glm::mat4 rot_matr = glm::mat4(	glm::vec4(x_axis.x, x_axis.y, x_axis.z,0.0f), 
									glm::vec4(y_axis.x, y_axis.y, y_axis.z,0.0f), 
									glm::vec4(z_axis.x, z_axis.y, z_axis.z,0.0f), 
									glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));*/	

	glm::mat4 result = (rot_matr * trans_matr);
	return  result;
}

void camera::Camera::ProcessKeyboard(Camera_Movement movement, float deltatime)
{
	float velocity = MovementSpeed * deltatime;
	if (movement == Camera_Movement::FORWARD)
		Position += Front * velocity;
	if (movement == Camera_Movement::BACKWARD)
		Position -= Front * velocity;
	if (movement == Camera_Movement::RIGHT)
		Position += Right * velocity;
	if (movement == Camera_Movement::LEFT)
		Position -= Right * velocity;

}

void camera::Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean contrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (contrainPitch)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	// update Front, Right and Up Vectors using the updated Euler angles
	UpdateCameraVector();
}

void camera::Camera::ProcessMouseScroll(float yoffset)
{
	Zoom -= (float)yoffset;
	if (Zoom < 1.0f)
		Zoom = 1.0f;
	if (Zoom > 45.0f)
		Zoom = 45.0f;
}
