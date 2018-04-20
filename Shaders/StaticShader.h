#pragma once

#include "ShaderProgram.h"

class StaticShader : public ShaderProgram
{
public:
	StaticShader();
protected:
	void bindAttributes();
private:
	static const char *VERTEX_FILE;
	static const char *FRAGMENT_FILE;
};