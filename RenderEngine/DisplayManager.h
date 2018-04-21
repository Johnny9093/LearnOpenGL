#pragma once

#include <GLFW\glfw3.h>

class DisplayManager
{
public:
	static GLFWwindow *getWindow();

	static bool createDisplay(int width, int height, const char *title, GLFWcursorposfun mouse_callback, GLFWscrollfun scroll_callback);
	static void updateDisplay();
	static void closeDisplay();
	static bool windowShouldClose();
	static float getAspectRatio();

private:
	static GLFWwindow* window;
	static int width;
	static int height;
};