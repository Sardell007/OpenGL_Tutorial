#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <utility> 

class DisplayManager {
private:
	GLFWwindow* window;
	static long  lastFrameTime;
	static float delta;
	static long getCurrentTime();
public:
	static int getKey();
	static void mouseKeyCallback(GLFWwindow* window, int button, int action, int mods);
	static int getMKey();
	static void cursorPCallback(GLFWwindow* window, double xpos, double ypos);
	static std::pair<double, double> getCPos();
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static std::pair<double, double> getScroll();
	static void keyboardCallback(GLFWwindow* window, int keyi, int scancode, int action, int mods);
	DisplayManager(int widthi,int heighti);
	DisplayManager();
	~DisplayManager();
	static int getWidth();
	static int getHeight();
	int createDisplay();
	int closeDisplay();
	void updateDisplay();
	bool isCloseRequested();
	inline static float getFrameTimeSeconds() { return delta; };
};