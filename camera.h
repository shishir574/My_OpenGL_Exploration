#pragma once
#include<glew.h>
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<GLFW/glfw3.h>

class camera
{

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUP;

	GLfloat yaw, pitch;

	GLfloat movementSpeed, turnSpeed;

	void update();

public:
	camera();
	camera(glm::vec3 startPosition, glm::vec3 startUP, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);
	void keyControl(bool* keys, GLfloat delta);
	void mouseControl(GLfloat xChange,GLfloat yChange);
	glm::mat4 calculateViewMatrix();
	~camera();
};

