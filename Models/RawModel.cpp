#include "RawModel.h"

RawModel::RawModel(unsigned int vaoId, unsigned int vertexCount) {
	RawModel::vaoId = vaoId;
	RawModel::vertexCount = vertexCount;
}

const unsigned int RawModel::getVAO() const {
	return RawModel::vaoId;
}

const unsigned int RawModel::getVertexCount() const {
	return RawModel::vertexCount;
}
