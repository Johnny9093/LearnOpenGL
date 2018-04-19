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

const int WIDTH = 800;
const int HEIGHT = 600;
const char* TITLE = "LearnOpenGL";

GLFWwindow* DisplayManager::window;

GLFWwindow *DisplayManager::getWindow() {
	return window;
}

bool DisplayManager::createDisplay()
{
	// Initialize GLFW and tell it which OpenGL version we're using (3.3 Core)
	// Core means we'll get access to a smaller subset of OpenGL features (without backwards-compatible features we no longer need)
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create GLFW window
	window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		closeDisplay();
		return false;
	}

	// Make the context of our window the main context on the current thread
	glfwMakeContextCurrent(window);

	// Registering the window resize callback function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

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