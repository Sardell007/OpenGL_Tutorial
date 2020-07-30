#include "DisplayManager.h"
#include <iostream>
#include <chrono>

int key = 0;
int width, height;
int mkey = 0;
double cxpos = 0;
double cypos = 0;
double pxpos = 0;
double pypos = 0;
double wxoffset = 0;
double wyoffset = 0;
double wx = 0;
double wy = 0;

long  DisplayManager::lastFrameTime;
float DisplayManager::delta;

DisplayManager::DisplayManager() {

}

DisplayManager::DisplayManager(int widthi, int heighti) {
    width = widthi;
    height = heighti;
}

DisplayManager::~DisplayManager() {

}

int DisplayManager::getHeight() {
    return height;
}

int DisplayManager::getWidth() {
    return width;
}

int DisplayManager::createDisplay() {

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glewInit();
    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);

    glfwSetKeyCallback(window, keyboardCallback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
    glfwSetMouseButtonCallback(window, mouseKeyCallback);
    glfwSetCursorPosCallback(window, cursorPCallback);
    glfwSetScrollCallback(window, scrollCallback);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Not OK" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    lastFrameTime = getCurrentTime();
}

void DisplayManager::keyboardCallback(GLFWwindow* window, int keyi, int scancode, int action, int mods){
    if (action == GLFW_PRESS) key = keyi;
    else if (action == GLFW_REPEAT) key = keyi;
    else if (action == GLFW_RELEASE) key = 0;
}

int DisplayManager::getKey() {
    return key;
}

void DisplayManager::mouseKeyCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        mkey = 1;
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        mkey = -1;
    }
    else {
        mkey = 0;
    }
}

int DisplayManager::getMKey() {
    return mkey;
}

void DisplayManager::cursorPCallback(GLFWwindow* window, double xpos, double ypos)
{
    cxpos = xpos - pxpos;
    cypos = ypos - pypos;
    pxpos = xpos;
    pypos = ypos;
}

std::pair<double, double> DisplayManager::getCPos() {
    return { cxpos,cypos };
}

void DisplayManager::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    wxoffset = xoffset;
    wyoffset = yoffset;
}

std::pair<double, double> DisplayManager::getScroll() {
    return { wxoffset,wyoffset };
}

int DisplayManager::closeDisplay() {
    glfwTerminate();
    return 0;
}

void DisplayManager::updateDisplay() {
    wxoffset = 0;
    wyoffset = 0;
    glfwSwapBuffers(window);
    glfwPollEvents();
    long currentFrameTime = getCurrentTime();
    delta = (currentFrameTime - lastFrameTime)/1000.0f;
    lastFrameTime = currentFrameTime;
}

bool DisplayManager::isCloseRequested() {
    return !glfwWindowShouldClose(window);
}

long DisplayManager::getCurrentTime() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
