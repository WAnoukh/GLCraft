#include "World.h"

World::World() : chunks(new Chunk*[size*size]) {
	for (size_t x = 0; x < size; ++x) {
		for (size_t z = 0; z < size; ++z) {
			chunks[posToIndex(x, z)] = new Chunk(glm::vec2(x, z),*this);
		}
	}
}

size_t World::getGeometry(float*& geometry) {
	ChunkGeometry* chunkGeometries = new ChunkGeometry[size * size];
	size_t totalLength = 0;
	for (size_t i = 0; i < size * size; ++i) {
		glm::vec3* uvs;
		glm::vec3* vertices;
		size_t length = chunks[i]->getGeometry(uvs, vertices);
		geometry = new float[length * 6];
		for (size_t j = 0; j < length; ++j) {
			geometry[j * 6] = vertices[j].x;
			geometry[j * 6 + 1] = vertices[j].y;
			geometry[j * 6 + 2] = vertices[j].z;
			geometry[j * 6 + 3] = uvs[j].x;
			geometry[j * 6 + 4] = uvs[j].y;
			geometry[j * 6 + 5] = uvs[j].z;
		}
		delete[] uvs;
		delete[] vertices;
		chunkGeometries[i] = { geometry, length*6 };
		totalLength += length*6;
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

unsigned short int World::getBlockOpacity(glm::vec3 pos) const {
	if (!isBlockLoaded(pos)) return 0;
	BlockId id = getBlock(pos);
	return BlockManager::getInstance().getBlockOpacity(id);
}

bool World::isBlockLoaded(glm::vec3 pos) const{
	return pos.x >= 0 && pos.y >= 0 && pos.z >= 0 && pos.x < size * defaultChunkSize && pos.y < defaultChunkHeight && pos.z < size * defaultChunkSize;
}

BlockId World::getBlock(glm::vec3 pos) const {
	if (pos.x < 0 || pos.y < 0 || pos.z < 0 || pos.x > size * defaultChunkSize || pos.y > defaultChunkHeight || pos.z > size * defaultChunkSize) {
		throw "World::getBlock error : block not loaded";
	}
	int chunkX = static_cast<int>(pos.x) / defaultChunkSize, chunkZ = static_cast<int>(pos.z) / defaultChunkSize;
	Chunk& blockChunk = *chunks[posToIndex(chunkX,chunkZ)];
	return blockChunk.getBlock(pos);
}

size_t World::posToIndex(int x, int z) const {
	if (x > size || x < 0 || z > size || z < 0) {
		throw "World::posToIndex error : pos outside the world !";
	}
	return static_cast<size_t>(x + z * size);
}

void World::indexToPos(size_t index, int& x, int& y) const {
	if (index > size * size) {
		throw "World::posToIndex error : index too large !";
	}
	x = index % size;
	y = index / size;
}