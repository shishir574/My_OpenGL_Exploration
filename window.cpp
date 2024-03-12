#include "window.h"

window::window()
{
	bufferWidth = 1200;
	bufferHeight = 720;
}

window::window(GLint windowWidth, GLint windowHeight)
{
	bufferWidth = windowWidth;
	bufferHeight = windowHeight;
}

int window::initialise()
{
    glfwInit();
    if (!glfwInit())
    {
        cout << "GLFW INIT FAILED";
        glfwTerminate();
        return 1;
    }

    //setup GLFW Window properties
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    //no backwards compatible
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //enable forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    mainWindow = glfwCreateWindow(bufferWidth, bufferHeight, "Main WIndow", NULL, NULL);
    if (!mainWindow)
    {
        cout << "WINDOW CREATION FAILED";
        glfwTerminate();
        return 1;
    }

    //buffer size info
     glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    //set context for GLEW 
    glfwMakeContextCurrent(mainWindow);

    // allow modern extension features
    glewExperimental = GL_TRUE;

    /* Initialize the library */
    glewInit();
    if (glewInit() != GLEW_OK)
    {
        cout << "GLEW INIT FAILED";
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    glEnable(GL_DEPTH_TEST);

    //setup viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);
}

window::~window()
{
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}
