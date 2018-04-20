#pragma once

class RawModel
{
public:
	RawModel(int vaoId, int vertexCount);

	int getVAO();
	int getVertexCount();

private:
	int vaoId;
	int vertexCount;
};

