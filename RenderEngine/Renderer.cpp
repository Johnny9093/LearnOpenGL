#include "Renderer.h"

#include <glad/glad.h>

void Renderer::prepare()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::render(RawModel model) {
	glBindVertexArray(model.getVAO());
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount());
	//glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}
