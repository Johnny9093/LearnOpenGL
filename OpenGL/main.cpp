#include "StaticShader.h"
#include "Loader.h"
#include "RawModel.h"
#include "Renderer.h"
#include "DisplayManager.h"

#include <iostream>

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
	Entity entity = Entity(staticModel, 0, 0, -4, 0, 0, 0, 1, 1, 1);
	Camera camera = Camera();

	#pragma region Render Loop

	// Start render loop
	while (!DisplayManager::windowShouldClose()) {
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
	/*float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;*/

	float pitch = 0.0f;
	float yaw = 0.0f;
	float roll = 0.0f;

	float c_x = 0.0f;
	float c_y = 0.0f;
	float c_z = 0.0f;

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		yaw += 0.5f;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		yaw -= 0.5f;
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		pitch += 0.5f;
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		pitch -= 0.5f;
	}

	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		roll -= 0.05f;
	}

	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
		roll += 0.05f;
	}

	// Camera

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		c_x += 0.05f;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		c_x -= 0.05f;
	}

	/*if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		c_y += 0.005f;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		c_y -= 0.005f;
	}*/

	/*if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		c_z -= 0.005f;
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		c_z += 0.005f;
	}*/

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		c_z -= 0.05f;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		c_z += 0.05f;
	}

	/*entity->move(x, y, z);*/
	camera->move(c_x, c_y, c_z);
	camera->givePitch(pitch);
	camera->giveYaw(yaw);
	camera->giveRoll(roll);

	// Exit the application when the Escape key is pressed
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}