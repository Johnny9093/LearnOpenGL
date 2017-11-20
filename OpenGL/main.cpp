#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>

// Window constants
const int WIDTH = 800;
const int HEIGHT = 600;
const char* TITLE = "LearnOpenGL";

// Declaring the window resize callback function
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
	// Initialize GLFW and tell it which OpenGL version we're using (3.3 Core)
	// Core means we'll get access to a smaller subset of OpenGL features (without backwards-compatible features we no longer need)
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create GLFW window
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);

	if (window == NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Make the context of our window the main context on the current thread
	glfwMakeContextCurrent(window);

	// Initialize GLAD with the OS-specific function to get function addresses, which is given by GLFW
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Initialize the viewport in which OpenGL will draw 
	// Basically mapping OpenGLs' [-1, 1] coordinates to our windows' [0, WIDTH] and [0, HEIGHT] coordinates
	glViewport(0, 0, 800, 600);

	// Registering the window resize callback function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return 0;
}

// Callback function to reset the viewport with the correct coordinates whenever a window resize occurrs
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}