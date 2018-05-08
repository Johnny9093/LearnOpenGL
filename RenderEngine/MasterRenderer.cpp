#include "MasterRenderer.h"
#include "MatrixMath.h"
#include "DisplayManager.h"

const float MasterRenderer::NEAR_PLANE = 0.1f;
const float MasterRenderer::FAR_PLANE = 1000;
const glm::vec3 skyColor = glm::vec3(0.07, 0.1, 0.3);

MasterRenderer::MasterRenderer(const Camera *camera): 
		entityShader(StaticShader()),
		entityRenderer(&entityShader),
		terrainShader(TerrainShader()),
		terrainRenderer(&terrainShader) {
	
	enableCulling();

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
	terrainShader.loadSkyColor(skyColor);
	terrainShader.stop();
}

void MasterRenderer::render(const Light *sun, const Camera *camera) {
	prepare();
	entityShader.start();
	entityShader.loadSkyColor(skyColor);
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

const void MasterRenderer::enableCulling() {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

const void MasterRenderer::disableCulling() {
	glDisable(GL_CULL_FACE);
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
	glClearColor(skyColor.r, skyColor.g, skyColor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}