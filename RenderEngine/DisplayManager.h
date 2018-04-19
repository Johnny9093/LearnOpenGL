#pragma once

#include <GLFW\glfw3.h>

class DisplayManager
{
public:
	static GLFWwindow *getWindow();

	static bool CreateDisplay();
	static void UpdateDisplay();
	static void CloseDisplay();
	static bool WindowShouldClose();

private:
	static GLFWwindow* window;
};