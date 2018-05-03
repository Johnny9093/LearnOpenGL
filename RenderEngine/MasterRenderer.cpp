#include "MasterRenderer.h"

MasterRenderer::MasterRenderer(): shader(StaticShader()), renderer(Renderer(&shader)) {
	shader.start();
	shader.loadAmbientLighting(0.1f);
	shader.stop();

	entities = std::unordered_map<TexturedModel, std::vector<Entity>, TexturedModelHasher, TexturedModelComparator>();
}

void MasterRenderer::render(Light sun, Camera camera) {
	shader.start();
	renderer.prepare(camera);
	shader.loadLight(sun);
	shader.loadViewMatrix(camera);
	renderer.render(entities);
	shader.stop();
}

void MasterRenderer::addEntity(const Entity entity) {
	TexturedModel texturedModel = entity.getModel();
	Texture texture = texturedModel.getTexture();
	entities[texturedModel].push_back(entity);
}

void MasterRenderer::cleanUp() {
	shader.cleanUp();
}
