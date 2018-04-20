#include "RawModel.h"

RawModel::RawModel(int vaoId, int vertexCount)
{
	RawModel::vaoId = vaoId;
	RawModel::vertexCount = vertexCount;
}

int RawModel::getVAO()
{
	return RawModel::vaoId;
}

int RawModel::getVertexCount()
{
	return RawModel::vertexCount;
}
