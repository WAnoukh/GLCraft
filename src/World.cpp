#include "World.h"

size_t World::getGeometry(float*& geometry) {
	glm::vec2* uvs;
	glm::vec3* vertex;
	size_t length = chunk->getGeometry(uvs, vertex);
	geometry = new float[length * 5];
	for (size_t i = 0; i < length; ++i) {
		geometry[i * 5] = vertex[i].x;
		geometry[i * 5 + 1] = vertex[i].y;
		geometry[i * 5 + 2] = vertex[i].z;
		geometry[i * 5 + 3] = uvs[i].x;
		geometry[i * 5 + 4] = uvs[i].y;
	}
	return length*5;
}