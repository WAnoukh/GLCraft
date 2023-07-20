#include "World.h"

World::World() : chunks(new Chunk*[size*size]) {
	for (size_t x = 0; x < size; ++x) {
		for (size_t z = 0; z < size; ++z) {
			chunks[posToIndex(x, z)] = new Chunk(glm::vec2(x, z));
		}
	}
}

size_t World::getGeometry(float*& geometry) {
	ChunkGeometry* chunkGeometries = new ChunkGeometry[size * size];
	size_t totalLength = 0;
	for (size_t i = 0; i < size * size; ++i) {
		glm::vec2* uvs;
		glm::vec3* vertices;
		size_t length = chunks[i]->getGeometry(uvs, vertices);
		geometry = new float[length * 5];
		for (size_t j = 0; j < length; ++j) {
			geometry[j * 5] = vertices[j].x;
			geometry[j * 5 + 1] = vertices[j].y;
			geometry[j * 5 + 2] = vertices[j].z;
			geometry[j * 5 + 3] = uvs[j].x;
			geometry[j * 5 + 4] = uvs[j].y;
		}
		delete[] uvs;
		delete[] vertices;
		chunkGeometries[i] = { geometry, length*5 };
		totalLength += length*5;
	}
	geometry = new float[totalLength];
	size_t written = 0;
	for (size_t i = 0; i < size * size; ++i) {
		ChunkGeometry & curChunk = chunkGeometries[i];
		for (size_t j = 0; j < curChunk.length; ++j) {
			geometry[written + j] = curChunk.geometry[j];
		}
		written += curChunk.length;
		delete[] curChunk.geometry;
	}

	delete[] chunkGeometries;
	return written;
}

size_t World::posToIndex(int x, int z) {
	if (x > size || x < 0 || z > size || z < 0) {
		throw "World::posToIndex error : pos outside the world !";
	}
	return static_cast<size_t>(x + z * size);
}

void World::indexToPos(size_t index, int& x, int& y) {
	if (index > size * size) {
		throw "World::posToIndex error : index too large !";
	}
	x = index % size;
	y = index / size;
}