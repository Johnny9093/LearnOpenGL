#pragma once

#include "Entity.h"
#include "StaticShader.h"

class Renderer
{
public:
	void prepare();
	void render(Entity entity, StaticShader shader);
};