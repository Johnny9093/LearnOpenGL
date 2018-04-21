#include <glad/glad.h>

#include "DisplayManager.h"
#include <iostream>

// Callback function to reset the viewport with the correct coordinates whenever a window resize occurs
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// Initialize the viewport in which OpenGL will draw 
	// Basically mapping OpenGLs' [-1, 1] coordinates to our windows' [0, WIDTH] and [0, HEIGHT] coordinates
	glViewport(0, 0, width, height);
}

GLFWwindow* DisplayManager::window;
int DisplayManager::width;
int DisplayManager::height;

GLFWwindow *DisplayManager::getWindow() {
	return window;
}

float DisplayManager::getAspectRatio() {
	return (width / (float)height);
}

bool DisplayManager::createDisplay(int width, int height, const char *title, GLFWcursorposfun mouse_callback, GLFWscrollfun scroll_callback)
{
	// Initialize GLFW and tell it which OpenGL version we're using (3.3 Core)
	// Core means we'll get access to a smaller subset of OpenGL features (without backwards-compatible features we no longer need)
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create GLFW window
	DisplayManager::width = width;
	DisplayManager::height = height;
	window = glfwCreateWindow(width, height, title, NULL, NULL);

	// Capture mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		closeDisplay();
		return false;
	}

	// Make the context of our window the main context on the current thread
	glfwMakeContextCurrent(window);

	// Registering callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// Initialize GLAD with the OS-specific function to get function addresses and load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		closeDisplay();
		return false;
	}

	return true;
}

void DisplayManager::updateDisplay()
{
	// Check and call events and swap the buffers
	// Swapping refers to the Double Buffer - read more at https://learnopengl.com/#!Getting-started/Hello-Window
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool DisplayManager::windowShouldClose()
{
	return glfwWindowShouldClose(window);
}

void DisplayManager::closeDisplay()
{
	glfwTerminate();
}