#include "RawModel.h"

RawModel::RawModel(int vaoID, int vertexCount)
{
	RawModel::vaoID = vaoID;
	RawModel::vertexCount = vertexCount;
}

int RawModel::getVAO()
{
	return RawModel::vaoID;
}

int RawModel::getVertexCount()
{
	return RawModel::vertexCount;
}
