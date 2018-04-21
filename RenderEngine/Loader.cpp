#include "Loader.h"

#include "stb_image.h"
#include <glad\glad.h>
#include <iostream>

RawModel Loader::loadToVAO(std::vector<float> vertices, std::vector<float> textureCoords, std::vector<unsigned int> indices) {
	unsigned int vaoId = createVAO();
	bindIndicesBuffer(indices);
	storeDataInAttributeList(0, 3, vertices);
	storeDataInAttributeList(1, 2, textureCoords);
	unbindVAO();
	return RawModel(vaoId, indices.size());
}

unsigned int Loader::loadTexture(const char *texturePath) {
	// Flip texture vertically to match coordinate system
	stbi_set_flip_vertically_on_load(true);

	// Create and bind texture
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	vaoIds.push_back(texture);

	// Set wrapping and filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load texture image
	int width, height, nrChannels;
	unsigned char *imgData = stbi_load(texturePath, &width, &height, &nrChannels, 0);

	if (imgData) {
		// Generate texture and mipmaps
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}

	// Free image memory
	stbi_image_free(imgData);

	return texture;
}

unsigned int Loader::createVAO()
{
	unsigned int VAO;

	// Generate VAO and store it's ID
	glGenVertexArrays(1, &VAO);
	vaoIds.push_back(VAO);

	// Binding the VAO to record the VBO data and vertex attributes configuration
	glBindVertexArray(VAO);
	
	return VAO;
}

void Loader::storeDataInAttributeList(int attributeNumber, int coordinateSize, std::vector<float> vertices)
{
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	vboIds.push_back(VBO);

	// Binding the VBO and copying the vertices to the vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW); // GL_STATIC_DRAW means this data will change very rarely, if at all.
	
	// Put the VBO in the attribute list of the VAO
	glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::bindIndicesBuffer(std::vector<unsigned int> indices) {
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	vboIds.push_back(VBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);
}

void Loader::unbindVAO()
{
	glBindVertexArray(0);
}

void Loader::cleanUp()
{
	glDeleteVertexArrays(vaoIds.size(), vaoIds.data());
	glDeleteBuffers(vboIds.size(), vboIds.data());
	glDeleteTextures(textureIds.size(), textureIds.data());
}