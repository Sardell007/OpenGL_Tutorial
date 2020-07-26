#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class DisplayManager {
private:
	GLFWwindow* window;
public:
	static int getKey();
	static void keyBoardInput(GLFWwindow* window, int keyi, int scancode, int action, int mods);
	DisplayManager(int widthi,int heighti);
	DisplayManager();
	~DisplayManager();
	static int getWidth();
	static int getHeight();
	int createDisplay();
	int closeDisplay();
	void updateDisplay();
	bool isCloseRequested();
};