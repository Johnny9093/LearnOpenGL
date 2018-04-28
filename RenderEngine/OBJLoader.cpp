#include "OBJLoader.h"

#include <fstream>
#include <sstream>
#include <iostream>

RawModel OBJLoader::loadObjModel(const std::string filePath, Loader loader)
{
	std::string objString;
	std::ifstream fileStream;
	std::stringstream objStream;

	// exceptions (check)
	fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		// read obj
		fileStream.open("res/" + filePath + ".obj");
		objStream << fileStream.rdbuf();
		fileStream.close();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::OBJ::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	int lineNumber = 0;
	std::string line;
	std::vector<glm::vec3> vertices = {};
	std::vector<glm::vec2> textures = {};
	std::vector<glm::vec3> normals = {};
	std::vector<unsigned int> indices = {};

	std::vector<float> verticesf;
	std::vector<float> texturesf;
	std::vector<float> normalsf;

	short stage = -1;

	try {
		while (std::getline(objStream, line)) {
			
			if (++lineNumber % 1000 == 0) {
				std::cout << "Read " << lineNumber << " lines." << std::endl;
			}

			std::istringstream iss(line);
			std::string token;

			std::getline(iss, token, ' ');

			// line represents vertex coordinates
			if (token == "v") {
				if (stage > 0) {
					throw std::exception("INVALID_VERTEX_POSITIONS");
				} else {
					stage = 0;
				}

				glm::vec3 vertex = glm::vec3();
				std::getline(iss, token, ' ');
				vertex.x = std::stof(token);
				std::getline(iss, token, ' ');
				vertex.y = std::stof(token);
				std::getline(iss, token, ' ');
				vertex.z = std::stof(token);
				vertices.push_back(vertex);
			}
			// line represents texture coordinates
			else if (token == "vt") {
				if (stage > 1) {
					throw std::exception("INVALID_TEXTURE_COORDINATES");
				}
				else {
					stage = 1;
				}

				glm::vec2 texture = glm::vec2();
				std::getline(iss, token, ' ');
				texture.x = std::stof(token);
				std::getline(iss, token, ' ');
				texture.y = std::stof(token);
				textures.push_back(texture);
			}
			// line represents normal vector
			else if (token == "vn") {
				if (stage > 2) {
					throw std::exception("INVALID_VECTOR_NORMALS");
				}
				else {
					stage = 2;
				}

				glm::vec3 normal = glm::vec3();
				std::getline(iss, token, ' ');
				normal.x = std::stof(token);
				std::getline(iss, token, ' ');
				normal.y = std::stof(token);
				std::getline(iss, token, ' ');
				normal.z = std::stof(token);
				normals.push_back(normal);
			}
			// line represents index
			else if (token == "f") {
				if (stage < 3) {
					stage = 3;

					texturesf = std::vector<float>(vertices.size() * 2);
					normalsf = std::vector<float>(vertices.size() * 3);
				}

				for (short i = 0; i < 3; i++) {
					std::getline(iss, token, ' ');
					std::string vert = token;
					std::istringstream vertiss(vert);
					std::string coord;

					std::getline(vertiss, coord, '/');
					unsigned int vin = std::stof(coord);
					std::getline(vertiss, coord, '/');
					unsigned int tin = std::stof(coord);
					std::getline(vertiss, coord, '/');
					unsigned int nin = std::stoul(coord);

					OBJLoader::processVertex(vin, tin, nin, &indices, &textures, &texturesf, &normals, &normalsf);
				}
			}
		}
	}
	catch (std::exception ex) {
		std::cout << "ERROR::OBJ::INVALID_FILE_FORMAT:\n" << ex.what() << std::endl;
	}

	verticesf = std::vector<float>(vertices.size() * 3);

	unsigned int vertexPointer = 0;

	for (auto vertex : vertices) {
		verticesf[vertexPointer++] = vertex.x;
		verticesf[vertexPointer++] = vertex.y;
		verticesf[vertexPointer++] = vertex.z;
	}

	return loader.loadToVAO(verticesf, texturesf, normalsf, indices);
}

void OBJLoader::processVertex(unsigned int vin, unsigned int tin, unsigned int nin, std::vector<unsigned int> *indices,
							  std::vector<glm::vec2> *textures, std::vector<float> *texturesf,
							  std::vector<glm::vec3> *normals, std::vector<float> *normalsf) {
	auto currentVertexPointer = vin - 1;
	indices->push_back(currentVertexPointer);
	auto tex = textures->at(tin - 1);
	texturesf->at(currentVertexPointer * 2) = tex.x;
	texturesf->at(currentVertexPointer * 2 + 1) = 1 - tex.y;
	auto normal = normals->at(nin - 1);
	normalsf->at(currentVertexPointer * 3) = normal.x;
	normalsf->at(currentVertexPointer * 3 + 1) = normal.y;
	normalsf->at(currentVertexPointer * 3 + 2) = normal.z;
}
