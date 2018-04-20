#include "RawModel.h"

RawModel::RawModel(unsigned int vaoId, unsigned int vertexCount)
{
	RawModel::vaoId = vaoId;
	RawModel::vertexCount = vertexCount;
}

unsigned int RawModel::getVAO() {
	return RawModel::vaoId;
}

unsigned int RawModel::getVertexCount() {
	return RawModel::vertexCount;
}
