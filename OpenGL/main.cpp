#include "StaticShader.h"
#include "Loader.h"
#include "OBJLoader.h"
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

const int WIDTH = 1280;
const int HEIGHT = 720;
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

	/*RawModel model = loader.loadToVAO(vertices, textureCoords, indices);*/
	RawModel stickMesh = OBJLoader::loadObjModel("stickfigure", loader);
	Texture stickTexture = Texture(loader.loadTexture("res\\wall.jpg"));
	TexturedModel stickModel = TexturedModel(stickMesh, stickTexture);
	Entity stick = Entity(stickModel, 3, 0, -40, 0, 0, 0, 1, 1, 1);

	RawModel dragonMesh = OBJLoader::loadObjModel("dragon", loader);
	Texture dragonTexture = Texture(loader.loadTexture("res\\dragon.png"));
	TexturedModel dragonModel = TexturedModel(dragonMesh, dragonTexture);
	Entity dragon = Entity(dragonModel, 0, 0, -50, 0, 0, 0, 1, 1, 1);

	Light light = Light(glm::vec3(0, 0, -20), glm::vec3(1, 0, 0));

	#pragma endregion

	#pragma region Render Loop

	// Start render loop
	while (!DisplayManager::windowShouldClose()) {
		
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		renderer.prepare(shader, camera);
		shader.start();
		shader.loadLight(light);
		shader.loadViewMatrix(camera);
		renderer.render(dragon, shader);
		renderer.render(stick, shader);
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

	float velocityModifier = 1.0f;

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		velocityModifier = 1.75f;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime, velocityModifier);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime, velocityModifier);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime, velocityModifier);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime, velocityModifier);
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