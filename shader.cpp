#include "shader.h"

#include<iostream>  
#include<string>
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>
#include<glew.h>
#include <GLFW/glfw3.h>

#include<fstream>

using namespace std;

shader::shader()
{
	shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;
}

void shader::createfromString(const char* vertexCode, const char* fragmenetCode)
{
	compileShader(vertexCode, fragmenetCode);
}
void shader::createfromFile(const char* vertexLOC, const char* fragmenetLOC)
{
    string vertexString = readFile(vertexLOC);
    string fragmentString = readFile(fragmenetLOC);

    const char* vertexCode = vertexString.c_str();
    const char* fragmentCode = fragmentString.c_str();

    compileShader(vertexCode, fragmentCode);
}
string shader::readFile(const char* fileLocation)
{
    string content;
    ifstream fileStream(fileLocation, ios::in);

    if (!fileStream.is_open())
    {
        cout << "Failed to open";
        return " ";
    }
    string line = " ";
    while (!fileStream.eof())
    {
        getline(fileStream, line);
        content.append(line + "\n");
    }
    fileStream.close();
    return content;
}

void shader::compileShader(const char* vertexCode, const char* fragmentCode)
{
    shaderID = glCreateProgram();
    if (!shaderID)
    {
        cout << "ERROR CREATING SHADER\n";
        return;
    }

    addShader(shaderID, vertexCode, GL_VERTEX_SHADER);
    addShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
        cout << "\nERROR LINKING PROGRAM" << eLog;
        return;
    }

    glValidateProgram(shaderID);
    glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
        cout << "\nERROR VALIDATING PROGRAM" << eLog;
        return;
    }

    uniformModel = glGetUniformLocation(shaderID, "model");
    uniformProjection = glGetUniformLocation(shaderID, "projection");
    uniformView = glGetUniformLocation(shaderID, "view");
    uniformAmbientColor = glGetUniformLocation(shaderID, "directionalLight.color");
    uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.ambientIntensity");

}

void shader::addShader(GLuint theprogram, const char* shaderCode, GLenum shaderType)
{
    GLuint theShader = glCreateShader(shaderType);
    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    GLint codelength[1];
    codelength[0] = strlen(shaderCode);

    glShaderSource(theShader, 1, theCode, codelength);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
        cout << "\nERROR COMPILING " << shaderType << " ERROR " << eLog;
        return;
    }

    glAttachShader(theprogram, theShader);

}

void shader::useShader()
{
    glUseProgram(shaderID);
}

void shader::clearShader()
{
    if (shaderID != 0)
    {
        glDeleteProgram(shaderID);
        shaderID = 0;
    }
    uniformProjection = 0;
    uniformModel = 0;
}

GLuint shader::getModelLOC()
{
    return uniformModel;
}

GLuint shader::getProjectionLOC()
{
    return uniformProjection;
}

GLuint shader::getViewLocation()
{
    return uniformView;
}

GLuint shader::getAmbientIntensityLoc()
{
    return uniformAmbientIntensity;
}
GLuint shader::getAmbientColorLoc()
{
    return uniformAmbientColor;
}

shader::~shader()
{
    clearShader();
}