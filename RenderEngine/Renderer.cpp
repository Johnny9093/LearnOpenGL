#include "Renderer.h"
#include "MatrixMath.h"
#include "DisplayManager.h"

#include <glad/glad.h>

const float Renderer::FOV = 70;
const float Renderer::NEAR_PLANE = 0.1f;
const float Renderer::FAR_PLANE = 1000;

Renderer::Renderer(StaticShader shader) {
	projectionMatrix = MatrixMath::createProjectionMatrix(DisplayManager::getWidth(), DisplayManager::getHeight(), FOV, NEAR_PLANE, FAR_PLANE);
	shader.start();
	shader.loadProjectionMatrix(projectionMatrix);
	shader.stop();
}

void Renderer::prepare() {
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(Entity entity, StaticShader shader) {

	RawModel model = entity.getModel().getRawModel();
	Texture texture = entity.getModel().getTexture();

	glBindVertexArray(model.getVAO());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glm::mat4 transformation = MatrixMath::createTransformationMatrix(entity.getPosition(), entity.getRotationX(), entity.getRotationY(), entity.getRotationZ(), entity.getScale());
	shader.loadTransformationMatrix(transformation);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.getTextureId());
	glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}
