#pragma once
#include<stdio.h>
#include<iostream>

#include<glew.h>
#include<GLFW/glfw3.h>

using namespace std;

class window
{
private:
	GLFWwindow* mainWindow;
	GLint bufferWidth, bufferHeight;

public:
	window();

	window(GLint windowWidth, GLint windowheight);

	GLfloat getbufferWidth() { return bufferWidth; }
	GLfloat getbufferHeighth() { return bufferHeight; }

	int initialise();

	bool getShouldClose() { return glfwWindowShouldClose(mainWindow); };
	void swapBuffers(){ glfwSwapBuffers(mainWindow); }

	~window();
};

