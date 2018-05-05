#pragma once

class RawModel
{
public:
	RawModel(unsigned int vaoId, unsigned int vertexCount);

	const unsigned int getVAO() const;
	const unsigned int getVertexCount() const;

private:
	unsigned int vaoId;
	unsigned int vertexCount;
};

