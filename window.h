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

	GLfloat lastX, lastY;	//mouse
	GLfloat Xchange = 0.0f, Ychange = 0.0f;
	bool mouseFirstMove;

	bool keys[1024]; //ASCII 
	
	void createCallback();
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);

public:
	window();

	window(GLint windowWidth, GLint windowheight);

	GLfloat getbufferWidth() { return bufferWidth; }
	GLfloat getbufferHeighth() { return bufferHeight; }

	int initialise();

	bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }
	bool* getsKeys() { return keys; }
	GLfloat getxChange();
	GLfloat getychange();
	void swapBuffers(){ glfwSwapBuffers(mainWindow); }

	~window();
};

