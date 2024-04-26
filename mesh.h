#pragma once
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>
#include<glew.h>
#include <GLFW/glfw3.h>

class mesh
{
private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;

public:
	mesh();
	void createMesh(GLfloat *vertices,unsigned int *indices, unsigned int numofindices, unsigned int numofVertices);
	void renderMesh();
	void clearMesh();
	~mesh();
};

