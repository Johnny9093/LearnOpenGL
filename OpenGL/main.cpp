#include "StaticShader.h"
#include "Loader.h"
#include "RawModel.h"
#include "Renderer.h"
#include "DisplayManager.h"

#include <iostream>

void processInput(GLFWwindow *window, Entity *entity);

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

	Loader loader = Loader();
	Renderer renderer = Renderer();
	StaticShader shader = StaticShader();

	RawModel model = loader.loadToVAO(vertices, textureCoords, indices);
	Texture texture = Texture(loader.loadTexture("res\\container.jpg"));
	TexturedModel texturedModel = TexturedModel(model, texture);
	Entity entity = Entity(texturedModel, 0, 0, 0, 0, 0, 0, 1, 1, 1);

	#pragma region Render Loop

	// Start render loop
	while (!DisplayManager::windowShouldClose())
	{
		renderer.prepare();
		shader.start();
		renderer.render(entity, shader);
		shader.stop();

		DisplayManager::updateDisplay();

		// Check for specific input
		processInput(DisplayManager::getWindow(), &entity);
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
void processInput(GLFWwindow *window, Entity *entity) {
	float x = 0.0f;
	float y = 0.0f;

	// Calculate dx and dy and move entity accordingly
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		x += 0.005f;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		x -= 0.005f;
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		y += 0.005f;
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		y -= 0.005f;
	}

	entity->move(x, y, 0);

	// Exit the application when the Escape key is pressed
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}