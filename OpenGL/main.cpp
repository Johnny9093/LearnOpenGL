#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// Declaring the window resize callback function
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// Settings
const int WIDTH = 800;
const int HEIGHT = 600;
const char* TITLE = "LearnOpenGL";

// Shader code
const char *rectangleVertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char *triangleVertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 color;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"	color = aColor;\n"
"}\0";

const char *gradientFragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 gradient;"
"void main()\n"
"{\n"
"   FragColor = gradient; // vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

const char *aColorFragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 aColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(aColor, 1.0);\n"
"}\n\0";

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

	// Registering the window resize callback function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Initialize GLAD with the OS-specific function to get function addresses and load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Creating vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Compiling
	glShaderSource(vertexShader, 1, &rectangleVertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Error checking
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Error: Vertex shader compilation failed." << std::endl;
	}

	// Creating vertex shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Compiling
	glShaderSource(fragmentShader, 1, &gradientFragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Error checking
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Error: Fragment shader compilation failed." << std::endl;
	}

	// Creating shader program
	unsigned int shaderProgram = glCreateProgram();

	// Linking shaders to shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Error checking
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success) 
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "Error: Shader program linkage failed." << std::endl;
	}

	// Deleting shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float triangle[] = {
		//x      y     z     r     g     b
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
		0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f // top
	};

	float rectangle_vertices[] = {
		-1.0f, -1.0f, 0.0f, // bottom left
		1.0f, -1.0f, 0.0f, // bottom right
		-1.0f, 1.0f, 0.0f, // top left
		1.0f,  1.0f, 0.0f // top right
	};

	unsigned int triangle_indices[] = {
		0, 1, 2
	};

	unsigned int rectangle_indices[] = {
		0, 1, 2,
		1, 2, 3
	};

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
	#pragma region Gradient
	//// Binding the VBO and copying the vertices to the vertex buffer
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW); // GL_STATIC_DRAW means this data will change very rarely, if at all.

	//// Tell OpenGL how to read the VBO:
	//// We passed in vertices structured as an array of floats, where every triplet of floats is a vertex.
	//// This also registers the VBO as the vertex attribute's bound vertex buffer object
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
	#pragma endregion

	// Binding the VBO and copying the vertices to the vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW); // GL_STATIC_DRAW means this data will change very rarely, if at all.

	// Tell OpenGL how to read the VBO:
	// We passed in vertices structured as an array of floats, where every triplet of floats is a vertex.
	// This also registers the VBO as the vertex attribute's bound vertex buffer object
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color attribute	 (location, size, type, ?, stride (space between same attribute of next vertex), pointer (offset from start of vertex to attribute))
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// EBO

	// Binding the EBO and copying the indices to the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangle_indices), triangle_indices, GL_STATIC_DRAW);

	// Unbind current buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Unbind VAO
	glBindVertexArray(0);

	// Start render loop
	while (!glfwWindowShouldClose(window))
	{
		// Check for specific input
		processInput(window);

		// Rendering
		//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Calculate gradient
		float time = glfwGetTime();
		float green = (sin(time) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "gradient");

		// Start using the shader program with our defined shaders
		glUseProgram(shaderProgram);

		// Set gradient
		glUniform4f(vertexColorLocation, 0.0f, green, 0.0f, 1.0f);

		// Bind VAO to get the vertex attribute configuration and vertex data
		glBindVertexArray(VAO);
		
		//// Draw vertices
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		// Draw indexed vertices
		// Bind the EBO and draw the indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Check and call events and swap the buffers
		// Swapping refers to the Double Buffer - read more at https://learnopengl.com/#!Getting-started/Hello-Window
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
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