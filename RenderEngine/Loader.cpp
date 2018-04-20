#include "Loader.h"

#include <glad\glad.h>

RawModel Loader::loadToVAO(std::vector<float> vertices, std::vector<unsigned int> indices)
{
	unsigned int vaoID = createVAO();
	bindIndicesBuffer(indices);
	storeDataInAttributeList(0, vertices);
	unbindVAO();
	return RawModel(vaoID, indices.size());
}

int Loader::createVAO()
{
	unsigned int VAO;

	// Generate VAO and store it's ID
	glGenVertexArrays(1, &VAO);
	vaoIDs.push_back(VAO);

	// Binding the VAO to record the VBO data and vertex attributes configuration
	glBindVertexArray(VAO);
	
	return VAO;
}

void Loader::storeDataInAttributeList(int attributeNumber, std::vector<float> vertices)
{
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	vboIDs.push_back(VBO);

	// Binding the VBO and copying the vertices to the vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW); // GL_STATIC_DRAW means this data will change very rarely, if at all.
	
	// Put the VBO in the attribute list of the VAO
	glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// Unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::bindIndicesBuffer(std::vector<unsigned int> indices) {
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	vboIDs.push_back(VBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);
}

void Loader::unbindVAO()
{
	glBindVertexArray(0);
}

void Loader::cleanUp()
{
	glDeleteVertexArrays(vaoIDs.size(), vaoIDs.data());
	glDeleteBuffers(vboIDs.size(), vboIDs.data());
}