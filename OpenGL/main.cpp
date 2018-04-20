#include "StaticShader.h"
#include "Loader.h"
#include "RawModel.h"
#include "Renderer.h"
#include "DisplayManager.h"

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

float mixValue = 0.2f;
void processInput(GLFWwindow *window);

int main()
{
	#pragma region GLFW Window

	if (!DisplayManager::createDisplay()) {
		return -1;
	}

	#pragma endregion

	#pragma region Data

	std::vector<float> vertices = {
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
	};

	std::vector<float> textureCoords{
		0, 0,
		0, 1,
		1, 1,
		1, 0
	};

	std::vector<unsigned int> indices = {
	 	0, 1, 3,
		3, 1, 2
	};

	//float vertices[] = {
	//	//x      y     z     r     g     b
	//	0.5f, -0.5f, 0.0f,	1.0f, 1.0f, 1.0f,  // bottom right
	//	-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, // bottom left
	//	0.0f, 0.5f, 0.0f,	1.0f, 1.0f, 1.0f // top
	//};

	//// Rectangle
	//float vertices[] = {
	//	// positions          // colors           // texture coords
	//	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	//	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	//};

	#pragma endregion

	#pragma region Textures

	#pragma region Texture 1

	//// Create and bind texture
	//unsigned int texture1;
	//glGenTextures(1, &texture1);
	//glBindTexture(GL_TEXTURE_2D, texture1);

	//// Set wrapping and filtering options
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//// Flip vertically to match coordinate system
	//stbi_set_flip_vertically_on_load(true);

	//// Load texture image
	//int width, height, nrChannels;
	//unsigned char *imgData = stbi_load("res\\container.jpg", &width, &height, &nrChannels, 0);

	//if (imgData) {
	//	// Generate texture and mipmaps
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);
	//	glGenerateMipmap(GL_TEXTURE_2D);
	//}
	//else {
	//	std::cout << "Failed to load texture" << std::endl;
	//}

	//// Free image memory
	//stbi_image_free(imgData);

	#pragma endregion

	#pragma region Texture 2

	//// Create and bind texture
	//unsigned int texture2;
	//glGenTextures(1, &texture2);
	//glBindTexture(GL_TEXTURE_2D, texture2);

	//// Set wrapping and filtering options
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//// Load texture image
	//width, height, nrChannels = 0;
	//imgData = stbi_load("res\\awesomeface.png", &width, &height, &nrChannels, 0);

	//if (imgData) {
	//	// Generate texture and mipmaps
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
	//	glGenerateMipmap(GL_TEXTURE_2D);
	//}
	//else {
	//	std::cout << "Failed to load texture" << std::endl;
	//}

	//// Free image memory
	//stbi_image_free(imgData);

	#pragma endregion

	#pragma endregion

	#pragma region VAO

	//unsigned int VAO, VBO, EBO;

	//// Generating vertex array object to hold our VBO configuration and attributes
	//glGenVertexArrays(1, &VAO);

	//// Generating vertex buffer
	//glGenBuffers(1, &VBO);

	//// Generating index buffer
	//glGenBuffers(1, &EBO);

	//// Binding the VAO to record the VBO data and vertex attributes configuration
	//glBindVertexArray(VAO);

	//// VBO

	//// Binding the VBO and copying the vertices to the vertex buffer
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // GL_STATIC_DRAW means this data will change very rarely, if at all.

	//// Tell OpenGL how to read the VBO:
	//// We passed in vertices structured as an array of floats, where every first triplet of floats is a vertex, and every second triplet of floats is a color.
	//// This also registers the VBO as the vertex attribute's bound vertex buffer object
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//// Color attribute	 (location, size, type, ?, stride (space between same attribute of next vertex), pointer (offset from start of vertex to attribute))
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	//// Texture coordinates
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(2);

	//// EBO

	//// Binding the EBO and copying the indices to the index buffer
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//// Unbind current buffer
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	#pragma endregion

	Loader loader = Loader();
	Renderer renderer = Renderer();
	StaticShader shader = StaticShader();

	RawModel model = loader.loadToVAO(vertices, textureCoords, indices);
	ModelTexture texture = ModelTexture(loader.loadTexture("res\\container.jpg"));
	TexturedModel texturedModel = TexturedModel(model, texture);

	#pragma region Render Loop

	// Start using the shader program with our defined shaders


	//shader.setInt("texture2", 1);

	// Bind textures
	//glActiveTexture(GL_TEXTURE0); // container
	//glBindTexture(GL_TEXTURE_2D, texture1);
	//glActiveTexture(GL_TEXTURE1); // smiley
	//glBindTexture(GL_TEXTURE_2D, texture2);

	// Start render loop
	while (!DisplayManager::windowShouldClose())
	{
		renderer.prepare();
		shader.start();
		renderer.render(texturedModel);
		shader.stop();

		DisplayManager::updateDisplay();

		// Check for specific input
		processInput(DisplayManager::getWindow());

		// Set background color
		//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);

		//// Compute position offset
		//float timeValue = glfwGetTime();
		//float vertical = sin(timeValue) / 2.0f;
		//float horizontal = cos(timeValue) / 2.0f;
		//
		//shader.setVec3("offset", horizontal, vertical, 0);

		//// Set color gradient
		//shader.setVec4("gradient", 0, sin(timeValue) / 2.0f + 0.5f, 0, 0);

		//shader.setFloat("mixValue", mixValue);

		// Bind VAO to get the vertex attribute configuration and vertex data
		//glBindVertexArray(VAO);
		
		// Draw indexed vertices
		// Bind the EBO and draw the indices
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	#pragma endregion

	#pragma region Cleanup

	shader.cleanUp();
	loader.cleanUp();
	DisplayManager::closeDisplay();
	return 0;

	#pragma endregion
}

// Process keyboard input
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		mixValue += 0.005f; // change this value accordingly (might be too slow or too fast based on system hardware)
		if (mixValue >= 1.0f)
			mixValue = 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		mixValue -= 0.005f; // change this value accordingly (might be too slow or too fast based on system hardware)
		if (mixValue <= 0.0f)
			mixValue = 0.0f;
	}

	// Exit the application when the Escape key is pressed
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}