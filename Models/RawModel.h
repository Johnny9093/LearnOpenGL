#pragma once

class RawModel
{
public:
	RawModel(unsigned int vaoId, unsigned int vertexCount);

	unsigned int getVAO();
	unsigned int getVertexCount();

private:
	unsigned int vaoId;
	unsigned int vertexCount;
};

