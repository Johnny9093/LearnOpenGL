#pragma once

#include <GLFW\glfw3.h>

class DisplayManager
{
public:
	static GLFWwindow *getWindow();

	static bool createDisplay();
	static void updateDisplay();
	static void closeDisplay();
	static bool windowShouldClose();

private:
	static GLFWwindow* window;
};