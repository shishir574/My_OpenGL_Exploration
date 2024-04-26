#include "window.h"

window::window()
{
	bufferWidth = 1200;
	bufferHeight = 720;

    for (size_t i = 0; i < 1024; i++)
    {
        keys[i] = false;
    }
}

window::window(GLint windowWidth, GLint windowHeight)
{
	bufferWidth = windowWidth;
	bufferHeight = windowHeight;

    for (size_t i = 0; i < 1024; i++)
    {
        keys[i] = false;
    }
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

     //handle key + mouse input
     createCallback();
     glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

    glfwSetWindowUserPointer(mainWindow, this);
}

void window::createCallback()
{
    glfwSetKeyCallback(mainWindow, handleKeys);
    glfwSetCursorPosCallback(mainWindow, handleMouse);
}

GLfloat window:: getxChange()
{
    GLfloat theChange = Xchange;
    Xchange = 0.0f;
    return theChange;
}
GLfloat window:: getychange()
{
    GLfloat theChange = Ychange;
    Ychange = 0.0f;
    return theChange;
}

void window::handleKeys(GLFWwindow* Window, int key, int code, int action, int mode)
{
    window* theWindow = static_cast<window*>(glfwGetWindowUserPointer(Window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(Window, GL_TRUE);
    }
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            theWindow->keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            theWindow->keys[key] = false;
        }
    }
}

void window::handleMouse(GLFWwindow* Window, double xPos, double yPos)
{
    window* theWindow = static_cast<window*>(glfwGetWindowUserPointer(Window));

    if (theWindow->mouseFirstMove)
    {
        theWindow->lastX = xPos;
        theWindow->lastY = yPos;
        theWindow->mouseFirstMove = false;
    }
    theWindow->Xchange = xPos - theWindow->lastX;
    theWindow->Ychange = theWindow->lastY - yPos;
    
    theWindow->lastX = xPos;
    theWindow->lastY = yPos;
}


window::~window()
{
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}
