#include <iostream>
#include <string.h>
#include <cmath>
#include <vector>


#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <glew.h>
#include <GLFW/glfw3.h>

#include "mesh.h"
#include "shader.h"
#include "window.h"
#include "camera.h"
#include "texture.h"
#include "Light.h"

#define STB_IMAGE_IMPLEMENTATION 
#include "stb_image.h"

using namespace std;

window mainWindow;
vector<mesh*> meshList;
vector<shader>shaderList;
camera Camera;
texture brickTex;
texture grassTex;

//git

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

Light mainlight;

//vertex shader
static const char* vShader = "Shaders/shader.vert.txt";

//fragment shader
static const char* fShader = "Shaders/shader.frag.txt";

void createObjects()
{
    unsigned int indices[] = { 
        0,3,1,
        1,3,2,
        2,3,0,
        0,1,2
    };

    GLfloat vertices[] = 
    {   //x,y,z,u,v
        -1.0f,  -1.0f,  0.0f,   0.0f,   0.0f,
         0.0f,  -1.0f,  1.0f,   0.5f,   0.0f,
         1.0f,  -1.0f,  0.0f,   1.0f,   0.0f,
         0.0f,  1.0f,   0.0f,   0.5f,   1.0f
    };

    mesh* obj1 = new mesh();
    obj1->createMesh(vertices, indices, 20, 12);
    meshList.push_back(obj1);

    mesh* obj2 = new mesh();
    obj2->createMesh(vertices, indices, 20, 12);
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
    
    //-90 to face towards origin from front of it
    Camera = camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 1.0f/*keys*/, 1.0f/*mouse*/);

    brickTex = texture((char*)("Textures/wall.png"));
    brickTex.LoadTexture();
    grassTex = texture((char*)("Textures/grass.png"));
    grassTex.LoadTexture();

    //ambient lighting r,g,b,i
    mainlight = Light(1.0f,1.0f,1.0f, 1.0f);

    GLuint uniformProjection = 0;
    GLuint uniformModel = 0;
    GLuint uniformView = 0;
    GLuint uniformAmbientIntensity = 0;
    GLuint uniformAmbientColor = 0;

    glm::mat4 projection = glm::perspective(45.0f,mainWindow.getbufferWidth()/mainWindow.getbufferHeighth(), 0.1f, 100.0f);

    //loop for window
    while (!mainWindow.getShouldClose())
    {
        GLfloat currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // get and handle user input events
        glfwPollEvents();

        //delta time
        Camera.keyControl(mainWindow.getsKeys(),deltaTime);
        Camera.mouseControl(mainWindow.getxChange(), mainWindow.getychange());

        //clear window
        glClearColor(1.0f,0.5f,0.5f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderList[0].useShader();
        uniformModel = shaderList[0].getModelLOC();
        uniformProjection = shaderList[0].getProjectionLOC();
        uniformView = shaderList[0].getViewLocation();
        uniformAmbientColor = shaderList[0].getAmbientColorLoc();
        uniformAmbientIntensity = shaderList[0].getAmbientIntensityLoc();

        mainlight.useLight(uniformAmbientIntensity, uniformAmbientColor);

        glm::mat4 model(1.0f);

        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        //model = glm::rotate(model, glm::radians(50), glm::vec3(0, 1, 0));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(Camera.calculateViewMatrix()));
        brickTex.UseTexture();
        meshList[0]->renderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        grassTex.UseTexture();
        meshList[1]->renderMesh();

        glUseProgram(0);

        mainWindow.swapBuffers();  
    }
    return 0;
}