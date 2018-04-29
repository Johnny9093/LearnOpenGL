#include "Renderer.h"
#include "MatrixMath.h"
#include "DisplayManager.h"

#include <glad/glad.h>

const float Renderer::NEAR_PLANE = 0.1f;
const float Renderer::FAR_PLANE = 1000;

Renderer::Renderer() {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void Renderer::prepare(StaticShader shader, Camera camera) {
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	projectionMatrix = MatrixMath::createProjectionMatrix(camera, DisplayManager::getAspectRatio(), NEAR_PLANE, FAR_PLANE);
	shader.start();
	shader.loadProjectionMatrix(projectionMatrix);
	shader.stop();
}

void Renderer::render(Entity entity, StaticShader shader) {

	RawModel model = entity.getModel().getRawModel();
	Texture texture = entity.getModel().getTexture();
	glm::mat4 transformation = MatrixMath::createTransformationMatrix(entity.getPosition(), entity.getRotationX(), entity.getRotationY(), entity.getRotationZ(), entity.getScale());

	glBindVertexArray(model.getVAO());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	shader.loadTransformationMatrix(transformation);
	shader.loadSpecularLighting(texture.getShineDamper(), texture.getReflectivity());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.getTextureId());
	glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
}
