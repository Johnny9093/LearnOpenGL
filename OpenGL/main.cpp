#include "MasterRenderer.h"
#include "Loader.h"
#include "OBJLoader.h"
#include "RawModel.h"
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
	if (!DisplayManager::createDisplay(WIDTH, HEIGHT, TITLE, mouse_callback, scroll_callback)) {
		return -1;
	}

	MasterRenderer renderer = MasterRenderer(&camera);
	Loader loader = Loader();

	RawModel stickMesh = OBJLoader::loadObjModel("stickfigure", loader);
	Texture stickTexture = Texture(loader.loadTexture("res\\wall.jpg"));
	stickTexture.setReflectivity(1.0f);
	stickTexture.setShineDamper(100);

	TexturedModel stickModel = TexturedModel(stickMesh, stickTexture);
	Entity stick = Entity(stickModel, 3, 0, -5, 0, 0, 0, 1, 1, 1);

	/*RawModel dragonMesh = OBJLoader::loadObjModel("dragon", loader);
	Texture dragonTexture = Texture(loader.loadTexture("res\\dragon.png"));
	dragonTexture.setReflectivity(1.0f);
	dragonTexture.setShineDamper(200);

	TexturedModel dragonModel = TexturedModel(dragonMesh, dragonTexture);
	Entity dragon = Entity(dragonModel, 0, 0, -15, 0, 0, 0, 1, 1, 1);*/

	Light light = Light(glm::vec3(800, 200, 400), glm::vec3(1, 1, 1));

	Texture terrainTexture = Texture(loader.loadTexture("res\\grass.png"));
	terrainTexture.setReflectivity(0);
	terrainTexture.setShineDamper(0.1);

	Terrain terrain1 = Terrain(0, 0, &loader, terrainTexture);
	Terrain terrain2 = Terrain(1, 0, &loader, terrainTexture);

	// Start render loop
	while (!DisplayManager::windowShouldClose()) {
		
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		renderer.addEntity(stick);
		//renderer.addEntity(dragon);
		renderer.addTerrain(&terrain1);
		renderer.addTerrain(&terrain2);

		renderer.render(&light, &camera);

		//dragon.rotate(0, 0.15f, 0);
		//stick.rotate(0, 0.1f, 0);

		DisplayManager::updateDisplay();
		processInput(DisplayManager::getWindow());
	}

	// Cleanup
	renderer.cleanUp();
	loader.cleanUp();
	DisplayManager::closeDisplay();
	return 0;
}

// Process keyboard input
void processInput(GLFWwindow *window) {

	// Exit the application when the Escape key is pressed
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	float velocityModifier = 1.0f;

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		velocityModifier = 100.0f;
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