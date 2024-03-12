#include<iostream>
#include<string.h>
#include<cmath>
#include<vector>

#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>
#include<glew.h>
#include <GLFW/glfw3.h>

#include "mesh.h"
#include "shader.h"
#include "window.h"

using namespace std;

window mainWindow;
vector<mesh*> meshList;
vector<shader>shaderList;

//glm::mat4 model(1.0f);

//vertex shader
static const char* vShader = "Shaders/shader.vert.txt";

//fragment shader
static const char* fShader = "Shaders/shader.frag.txt";

void createObjects()
{
    unsigned int indices[] = { 
        0,3,1,
        1,3,2,
        1,0,2,
        0,3,2
    };

    GLfloat vertices[] = 
    {
        -1.0f,-1.0f,0.0f,
         0.0f,0.0f,1.0f,
         1.0f,-1.0f,0.0f,
         0.0f, 1.0f,0.0f
    };

    mesh* obj1 = new mesh();
    obj1->createMesh(vertices, indices, 12, 12);
    meshList.push_back(obj1);

    mesh* obj2 = new mesh();
    obj2->createMesh(vertices, indices, 12, 12);
    meshList.push_back(obj2);
}

void createShader()
{
    shader* shader1 = new shader();
    shader1->createfromFile(vShader, fShader);
    shaderList.push_back(*shader1);
}

int main(void)
{
    mainWindow = window(1400, 840);
    mainWindow.initialise();

    createObjects();
    createShader();

    GLuint uniformProjection = 0;
    GLuint uniformModel = 0;

    glm::mat4 projection = glm::perspective(45.0f,mainWindow.getbufferWidth()/mainWindow.getbufferHeighth(), 0.1f, 100.0f);

    //loop for window
    while (!mainWindow.getShouldClose())
    {
        // get and handle user input events
        glfwPollEvents();

        //clear window
        glClearColor(1.0f,0.5f,0.5f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderList[0].useShader();
        uniformModel = shaderList[0].getModelLOC();
        uniformProjection = shaderList[0].getProjectionLOC();

        glm::mat4 model(1.0f);

        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[0]->renderMesh();

        model = glm::translate(model, glm::vec3(1.0f, 1.0f, -2.5f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[1]->renderMesh();

        glUseProgram(0);

        mainWindow.swapBuffers();
       
    }
    return 0;
}