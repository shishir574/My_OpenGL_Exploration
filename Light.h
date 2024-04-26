#pragma once
#include<glew.h>
#include<glm.hpp>
class Light
{
private:
	glm::vec3 color;
	GLfloat ambientIntensity;

public:
	Light();

	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity);
	void useLight(GLfloat amientIntensityLoc, GLfloat ambientColorLoc);
	~Light();
};

