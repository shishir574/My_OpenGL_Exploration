#pragma once
#include<stdio.h>
#include<string>
#include<iostream>
#include<fstream>

#include<glew.h>
using namespace std;
class shader
{
private:
	GLuint shaderID,uniformProjection,uniformModel,uniformView,uniformAmbientIntensity, uniformAmbientColor;
	void compileShader(const char* vertexCode, const char* fragmenetCode);
	void addShader(GLuint theprogram, const char* shaderCode, GLenum shaderType);

public:
	shader();
	void createfromString(const char* vertexCode, const char* fragmenetCode);
	void createfromFile(const char* vertexLOC, const char* fragmenetLOC);

	string readFile(const char* fileLocation);

	GLuint getProjectionLOC();
	GLuint getModelLOC();
	GLuint getViewLocation();
	GLuint getAmbientIntensityLoc();
	GLuint getAmbientColorLoc();
	void useShader();
	void clearShader();
	~shader();
};

