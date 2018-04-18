#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

#include <iostream>

// Declaring the window resize callback function
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// Window settings
const int WIDTH = 800;
const int HEIGHT = 600;
const char* TITLE = "LearnOpenGL";

int main()
{
	#pragma region GLFW Window

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

	// Registering the window resize callback function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Initialize GLAD with the OS-specific function to get function addresses and load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	#pragma endregion

	#pragma region Shaders

	Shader shader("vertex.s", "fragment.s");

	#pragma endregion

	#pragma region Data

	float vertices[] = {
		//x      y     z     r     g     b
		0.5f, -0.5f, 0.0f,	1.0f, 1.0f, 1.0f,  // bottom right
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, // bottom left
		0.0f, 0.5f, 0.0f,	1.0f, 1.0f, 1.0f // top
	};

	unsigned int indices[] = {
		0, 1, 2
	};

	#pragma endregion

	#pragma region Buffers

	unsigned int VAO, VBO, EBO;

	// Generating vertex array object to hold our VBO configuration and attributes
	glGenVertexArrays(1, &VAO);

	// Generating vertex buffer
	glGenBuffers(1, &VBO);

	// Generating index buffer
	glGenBuffers(1, &EBO);

	// Binding the VAO to record the VBO data and vertex attributes configuration
	glBindVertexArray(VAO);

	// VBO

	// Binding the VBO and copying the vertices to the vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // GL_STATIC_DRAW means this data will change very rarely, if at all.

	// Tell OpenGL how to read the VBO:
	// We passed in vertices structured as an array of floats, where every first triplet of floats is a vertex, and every second triplet of floats is a color.
	// This also registers the VBO as the vertex attribute's bound vertex buffer object
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color attribute	 (location, size, type, ?, stride (space between same attribute of next vertex), pointer (offset from start of vertex to attribute))
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// EBO

	// Binding the EBO and copying the indices to the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Unbind current buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	#pragma endregion

	#pragma region Render Loop

	// Start render loop
	while (!glfwWindowShouldClose(window))
	{
		// Check for specific input
		processInput(window);

		// Set background color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Start using the shader program with our defined shaders
		shader.use();

		// Bind VAO to get the vertex attribute configuration and vertex data
		glBindVertexArray(VAO);
		
		// Draw indexed vertices
		// Bind the EBO and draw the indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		// Check and call events and swap the buffers
		// Swapping refers to the Double Buffer - read more at https://learnopengl.com/#!Getting-started/Hello-Window
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	#pragma endregion

	#pragma region Cleanup

	glfwTerminate();
	return 0;

	#pragma endregion
}

// Callback function to reset the viewport with the correct coordinates whenever a window resize occurrs
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// Initialize the viewport in which OpenGL will draw 
	// Basically mapping OpenGLs' [-1, 1] coordinates to our windows' [0, WIDTH] and [0, HEIGHT] coordinates
	glViewport(0, 0, width, height);
}

// Process keyboard input
void processInput(GLFWwindow *window)
{
	// Exit the application when the Escape key is pressed
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}