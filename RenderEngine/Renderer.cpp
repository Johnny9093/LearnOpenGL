#include "Renderer.h"
#include "MatrixMath.h"
#include "DisplayManager.h"

#include <glad/glad.h>

const float Renderer::NEAR_PLANE = 0.1f;
const float Renderer::FAR_PLANE = 1000;

Renderer::Renderer(StaticShader *shader) {
	Renderer::shader = shader;

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void Renderer::prepare(Camera camera) {
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.15f, 0.0f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	projectionMatrix = MatrixMath::createProjectionMatrix(camera, DisplayManager::getAspectRatio(), NEAR_PLANE, FAR_PLANE);
	shader->loadProjectionMatrix(projectionMatrix);
}

void Renderer::render(std::unordered_map<TexturedModel, std::vector<Entity>, TexturedModelHasher, TexturedModelComparator> entities) {
	for (auto it = entities.begin(); it != entities.end(); ++it) {
		TexturedModel model = it->first;
		std::vector<Entity> modelEntities = it->second;

		prepareTexturedModel(model);

		for (Entity entity : modelEntities) {
			prepareInstance(entity);
			glDrawElements(GL_TRIANGLES, model.getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);
		}

		unbindTexturedModel();
	}
}

void Renderer::prepareTexturedModel(TexturedModel texturedModel) {
	RawModel model = texturedModel.getRawModel();
	glBindVertexArray(model.getVAO());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	Texture texture = texturedModel.getTexture();
	shader->loadSpecularLighting(texture.getShineDamper(), texture.getReflectivity());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.getTextureId());
}

void Renderer::unbindTexturedModel() {
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void Renderer::prepareInstance(Entity entity) {
	glm::mat4 transformation = MatrixMath::createTransformationMatrix(entity.getPosition(), entity.getRotationX(), entity.getRotationY(), entity.getRotationZ(), entity.getScale());
	shader->loadTransformationMatrix(transformation);
}
