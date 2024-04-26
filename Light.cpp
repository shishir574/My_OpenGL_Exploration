#include "Light.h"

Light::Light()
{
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity)
{
	color = glm::vec3(red, green, blue);
	this->ambientIntensity = ambientIntensity;
}
void Light::useLight(GLfloat amientIntensityLoc, GLfloat ambientColorLoc)
{
	glUniform3f(ambientColorLoc, color.x, color.y, color.z);
	glUniform1f(amientIntensityLoc, ambientIntensity);
}

Light::~Light()
{

}
