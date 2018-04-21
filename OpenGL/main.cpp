#include "StaticShader.h"
#include "Loader.h"
#include "RawModel.h"
#include "Renderer.h"
#include "DisplayManager.h"
#include "Camera.h"

#include <iostream>

// callbacks
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void processInput(GLFWwindow *window);

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

const int WIDTH = 800;
const int HEIGHT = 600;
const char* TITLE = "LearnOpenGL";

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

int main()
{
	#pragma region GLFW Window

	if (!DisplayManager::createDisplay(WIDTH, HEIGHT, TITLE, mouse_callback, scroll_callback)) {
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

	#pragma endregion

	#pragma region Initialization

	Loader loader = Loader();
	StaticShader shader = StaticShader();
	Renderer renderer = Renderer();

	RawModel model = loader.loadToVAO(vertices, textureCoords, indices);
	Texture texture = Texture(loader.loadTexture("res\\container.jpg"));
	TexturedModel staticModel = TexturedModel(model, texture);
	Entity entity = Entity(staticModel, 0, 0, 0, 0, 0, 0, 1, 1, 1);

	#pragma endregion

	#pragma region Render Loop

	// Start render loop
	while (!DisplayManager::windowShouldClose()) {
		
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		renderer.prepare(shader, camera);
		shader.start();
		shader.loadViewMatrix(camera);
		renderer.render(entity, shader);
		shader.stop();

		DisplayManager::updateDisplay();
		processInput(DisplayManager::getWindow());
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
void processInput(GLFWwindow *window) {

	// Exit the application when the Escape key is pressed
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
	}

	float xoffset = (float)xpos - lastX;
	float yoffset = lastY - (float)ypos; // reversed since y-coordinates go from bottom to top

	lastX = (float)xpos;
	lastY = (float)ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll((float)yoffset);
}