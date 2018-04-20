#pragma once

#include "Entity.h"
#include "StaticShader.h"

class Renderer
{
public:
	Renderer(StaticShader shader);

	void prepare();
	void render(Entity entity, StaticShader shader);

private:
	static const float FOV;
	static const float NEAR_PLANE;
	static const float FAR_PLANE;

	glm::mat4 projectionMatrix;
};