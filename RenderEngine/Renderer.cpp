#include "Renderer.h"

#include <glad/glad.h>

void Renderer::prepare()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::render(TexturedModel texturedModel) {
	glBindVertexArray(texturedModel.getModel().getVAO());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturedModel.getTexture().getTextureId());
	glDrawElements(GL_TRIANGLES, texturedModel.getModel().getVertexCount(), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}
