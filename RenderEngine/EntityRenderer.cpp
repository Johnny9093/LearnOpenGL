#include "EntityRenderer.h"
#include "MatrixMath.h"
#include "DisplayManager.h"
#include "MasterRenderer.h"

#include <glad/glad.h>

EntityRenderer::EntityRenderer(StaticShader *shader) {
	EntityRenderer::shader = shader;
}

void EntityRenderer::render(const std::unordered_map<TexturedModel, std::vector<Entity>, TexturedModelHasher, TexturedModelComparator> entities) const {
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

void EntityRenderer::prepareTexturedModel(const TexturedModel texturedModel) const {
	RawModel model = texturedModel.getRawModel();
	glBindVertexArray(model.getVAO());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	Texture texture = texturedModel.getTexture();

	if (texture.getHasTransparency()) {
		MasterRenderer::disableCulling();
	}

	shader->loadUseFakeLighting(texture.getUseFakeLighting());
	shader->loadSpecularLighting(texture.getShineDamper(), texture.getReflectivity());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.getTextureId());
}

void EntityRenderer::unbindTexturedModel() const {
	MasterRenderer::enableCulling();
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void EntityRenderer::prepareInstance(const Entity entity) const {
	glm::mat4 transformation = MatrixMath::createTransformationMatrix(entity.getPosition(), entity.getRotationX(), entity.getRotationY(), entity.getRotationZ(), entity.getScale());
	shader->loadTransformationMatrix(transformation);
}
