#include "TerrainRenderer.h"
#include "MatrixMath.h"

TerrainRenderer::TerrainRenderer(TerrainShader *shader) {
	TerrainRenderer::shader = shader;
}

void TerrainRenderer::render(const std::vector<const Terrain*> terrains) const {
	for (const Terrain *terrain : terrains) {
		prepareTerrain(terrain);
		loadModelMatrix(terrain);

		glDrawElements(GL_TRIANGLES, terrain->getModel().getVertexCount(), GL_UNSIGNED_INT, 0);
	}

	unbindTerrain();
}

void TerrainRenderer::prepareTerrain(const Terrain *terrain) const {
	const RawModel model = terrain->getModel();
	glBindVertexArray(model.getVAO());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	const Texture texture = terrain->getTexture();
	shader->loadSpecularLighting(texture.getShineDamper(), texture.getReflectivity());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.getTextureId());
}

void TerrainRenderer::unbindTerrain() const {
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void TerrainRenderer::loadModelMatrix(const Terrain *terrain) const {
	glm::mat4 transformation = MatrixMath::createTransformationMatrix(glm::vec3(terrain->getX(), 0, terrain->getZ()), 0, 0, 0, glm::vec3(1));
	shader->loadTransformationMatrix(transformation);
}
