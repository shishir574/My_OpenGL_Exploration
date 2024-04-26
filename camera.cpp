#include "camera.h"

camera::camera()
{

}

camera::camera(glm::vec3 startPosition, glm::vec3 startUP, GLfloat startYaw, GLfloat startPitch,GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	worldUP = startUP;
	pitch = startPitch;
	yaw = startYaw;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	movementSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	update();
}

void camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUP));
	up = glm::normalize(glm::cross(right, front));
}

void camera::keyControl(bool* keys,GLfloat delta)
{
	GLfloat velocity = movementSpeed * delta;
	if (keys[GLFW_KEY_W])
	{
		position += front * velocity;
	}
	if (keys[GLFW_KEY_S])
	{
		position -= front * velocity;
	}
	if (keys[GLFW_KEY_D])
	{
		position += right * velocity;
	}
	if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}
}

void camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;
	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	update();
}

glm::mat4 camera::calculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

camera::~camera()
{

}
