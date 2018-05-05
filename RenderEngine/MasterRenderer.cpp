#include "MasterRenderer.h"
#include "MatrixMath.h"
#include "DisplayManager.h"

const float MasterRenderer::NEAR_PLANE = 0.1f;
const float MasterRenderer::FAR_PLANE = 1000;

MasterRenderer::MasterRenderer(const Camera *camera): 
		entityShader(StaticShader()),
		entityRenderer(&entityShader),
		terrainShader(TerrainShader()),
		terrainRenderer(&terrainShader) {

	entities = std::unordered_map<TexturedModel, std::vector<Entity>, TexturedModelHasher, TexturedModelComparator>();
	terrains = std::vector<const Terrain*>();
	projectionMatrix = MatrixMath::createProjectionMatrix(camera->Zoom, DisplayManager::getAspectRatio(), NEAR_PLANE, FAR_PLANE);

	entityShader.start();
	entityShader.loadAmbientLighting(0.1f);
	entityShader.loadProjectionMatrix(projectionMatrix);
	entityShader.stop();

	terrainShader.start();
	terrainShader.loadAmbientLighting(0.1f);
	terrainShader.loadProjectionMatrix(projectionMatrix);
	terrainShader.stop();
}

void MasterRenderer::render(const Light *sun, const Camera *camera) {
	prepare();
	entityShader.start();
	entityShader.loadLight(sun);
	entityShader.loadViewMatrix(camera);
	entityRenderer.render(entities);
	entityShader.stop();

	terrainShader.start();
	terrainShader.loadLight(sun);
	terrainShader.loadViewMatrix(camera);
	terrainRenderer.render(terrains);
	terrainShader.stop();

	terrains.clear();
	entities.clear();
}

void MasterRenderer::addEntity(const Entity entity) {
	TexturedModel texturedModel = entity.getModel();
	Texture texture = texturedModel.getTexture();
	entities[texturedModel].push_back(entity);
}

void MasterRenderer::addTerrain(const Terrain *terrain) {
	terrains.push_back(terrain);
}

void MasterRenderer::cleanUp() {
	entityShader.cleanUp();
	terrainShader.cleanUp();
}

void MasterRenderer::prepare() const {
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.15f, 0.0f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}