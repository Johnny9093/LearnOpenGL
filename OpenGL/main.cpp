#include "StaticShader.h"
#include "Loader.h"
#include "RawModel.h"
#include "Renderer.h"
#include "DisplayManager.h"

#include <iostream>

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

void processInput(GLFWwindow *window, Entity *entity, Camera *camera);

int main()
{
	#pragma region GLFW Window

	if (!DisplayManager::createDisplay()) {
		return -1;
	}

	#pragma endregion

	#pragma region Data

	std::vector<float> vertices = {
		-0.5f,0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,0.5f,-0.5f,

		-0.5f,0.5f,0.5f,
		-0.5f,-0.5f,0.5f,
		0.5f,-0.5f,0.5f,
		0.5f,0.5f,0.5f,

		0.5f,0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,0.5f,
		0.5f,0.5f,0.5f,

		-0.5f,0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,0.5f,
		-0.5f,0.5f,0.5f,

		-0.5f,0.5f,0.5f,
		-0.5f,0.5f,-0.5f,
		0.5f,0.5f,-0.5f,
		0.5f,0.5f,0.5f,

		-0.5f,-0.5f,0.5f,
		-0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,0.5f
	};

	std::vector<float> textureCoords = {
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0
	};

	std::vector<unsigned int> indices = {
		0,1,3,
		3,1,2,
		4,5,7,
		7,5,6,
		8,9,11,
		11,9,10,
		12,13,15,
		15,13,14,
		16,17,19,
		19,17,18,
		20,21,23,
		23,21,22
	};

	//std::vector<float> vertices = {
	//	-0.5f, 0.5f, 0.0f,
	//	-0.5f, -0.5f, 0.0f,
	//	0.5f, -0.5f, 0.0f,
	//	0.5f, 0.5f, 0.0f,
	//};

	//std::vector<float> textureCoords{
	//	0, 0,
	//	0, 1,
	//	1, 1,
	//	1, 0
	//};

	//std::vector<unsigned int> indices = {
	// 	0, 1, 3,
	//	3, 1, 2
	//};

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
	StaticShader shader = StaticShader();
	Renderer renderer = Renderer(shader);

	RawModel model = loader.loadToVAO(vertices, textureCoords, indices);
	Texture texture = Texture(loader.loadTexture("res\\container.jpg"));
	TexturedModel staticModel = TexturedModel(model, texture);
	Entity entity = Entity(staticModel, 0, 0, 0, 0, 0, 0, 1, 1, 1);
	Camera camera = Camera();

	#pragma region Render Loop

	// Start render loop
	while (!DisplayManager::windowShouldClose()) {
		
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		renderer.prepare();
		shader.start();
		shader.loadViewMatrix(camera);
		renderer.render(entity, shader);
		shader.stop();

		DisplayManager::updateDisplay();

		// Check for specific input
		processInput(DisplayManager::getWindow(), &entity, &camera);
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
void processInput(GLFWwindow *window, Entity *entity, Camera *camera) {

	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->move(cameraSpeed * camera->getFront());
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->move(-(cameraSpeed * camera->getFront()));
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->move(-(glm::normalize(glm::cross(camera->getFront(), glm::vec3(0.0f, 1.0f, 0.0f))) * cameraSpeed));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->move(glm::normalize(glm::cross(camera->getFront(), glm::vec3(0.0f, 1.0f, 0.0f))) * cameraSpeed);

	// Exit the application when the Escape key is pressed
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}