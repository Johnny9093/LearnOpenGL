#pragma once

class RawModel
{
public:
	RawModel(int vaoID, int vertexCount);

	int getVAO();
	int getVertexCount();

private:
	int vaoID;
	int vertexCount;
};

