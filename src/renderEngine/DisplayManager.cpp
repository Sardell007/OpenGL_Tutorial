#include "DisplayManager.h"
#include <iostream>
#include <chrono>

int key = 0;
int width, height;

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

    glfwSetKeyCallback(window, keyBoardInput);

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

void DisplayManager::keyBoardInput(GLFWwindow* window, int keyi, int scancode, int action, int mods){
    if (action == GLFW_PRESS) key = keyi;
    else if (action == GLFW_REPEAT) key = keyi;
    else if (action == GLFW_RELEASE) key = 0;
}

int DisplayManager::getKey() {
    return key;
}

int DisplayManager::closeDisplay() {
    glfwTerminate();
    return 0;
}

void DisplayManager::updateDisplay() {
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
