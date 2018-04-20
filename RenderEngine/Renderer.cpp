#include "Renderer.h"
#include "MatrixMath.h"

#include <glad/glad.h>

void Renderer::prepare()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
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
