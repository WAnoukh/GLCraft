#include "World.h"
#include <thread>
#include <queue>

World::World() : chunks(new Chunk*[size*size]) {
	for (size_t x = 0; x < size; ++x) {
		for (size_t z = 0; z < size; ++z) {
			chunks[posToIndex(x, z)] = new Chunk(glm::vec2(x, z),*this);
		}
	}
}

void chunkGeometryThread(Chunk** chunks, ChunkGeometry* cgs, size_t nb) {
	const size_t blockCount = chunks[0]->getBlockCount();
	glm::vec3* uvs = new glm::vec3[blockCount * 6 * 6];
	glm::vec3* vertices = new glm::vec3[blockCount * 6 * 6];
	for (size_t i = 0; i < nb; ++i) {
		size_t length = chunks[i]->getGeometry(uvs, vertices);
		float* tempGeometry = new float[length * 6];
		for (size_t j = 0; j < length; ++j) {
			tempGeometry[j * 6] = vertices[j].x;
			tempGeometry[j * 6 + 1] = vertices[j].y;
			tempGeometry[j * 6 + 2] = vertices[j].z;
			tempGeometry[j * 6 + 3] = uvs[j].x;
			tempGeometry[j * 6 + 4] = uvs[j].y;
			tempGeometry[j * 6 + 5] = uvs[j].z;
		}
		cgs[i] = {tempGeometry, length * 6};
	}
	delete[] uvs;
	delete[] vertices;
}

#define THR_NUM 6

#define MULT
size_t World::getGeometry(float*& geometry) {
#ifdef MULT

	ChunkGeometry* chunkGeometries = new ChunkGeometry[size * size];
	size_t totalLength = 0;
	std::queue<std::thread> threads;
	int chkPerThr = size * size / THR_NUM;
	for (size_t i = 0; i < THR_NUM; ++i) {
		if (i == THR_NUM - 1) {
			threads.emplace(chunkGeometryThread, chunks + (i * chkPerThr), &chunkGeometries[i * chkPerThr],  (size * size) - (i * chkPerThr));
		}
		else {
			threads.emplace(chunkGeometryThread, chunks + (i * chkPerThr), &chunkGeometries[i * chkPerThr], chkPerThr);
		}
		
	}
	while (!threads.empty()) {
		threads.front().join();
		threads.pop();
	}
	for (size_t i = 0; i < size * size; ++i) {
		//chunkGeometryThread(*chunks[i], chunkGeometries[i]);
		totalLength += chunkGeometries[i].length;
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
#endif // !1
#ifndef MULT
	ChunkGeometry* chunkGeometries = new ChunkGeometry[size * size];
	size_t totalLength = 0;
	const size_t blockCount = chunks[0]->getBlockCount();
	glm::vec3* uvs = new glm::vec3[blockCount * 6 * 6];
	glm::vec3* vertices = new glm::vec3[blockCount * 6 * 6];
	for (size_t i = 0; i < size * size; ++i) {
		size_t length = chunks[i]->getGeometry(uvs, vertices);
		float* tempGeometry = new float[length * 6];
		for (size_t j = 0; j < length; ++j) {
			tempGeometry[j * 6] = vertices[j].x;
			tempGeometry[j * 6 + 1] = vertices[j].y;
			tempGeometry[j * 6 + 2] = vertices[j].z;
			tempGeometry[j * 6 + 3] = uvs[j].x;
			tempGeometry[j * 6 + 4] = uvs[j].y;
			tempGeometry[j * 6 + 5] = uvs[j].z;
		}
		chunkGeometries[i] = { tempGeometry, length * 6 };
		totalLength += chunkGeometries[i].length;
	}
	delete[] uvs;
	delete[] vertices;
	geometry = new float[totalLength];
	size_t written = 0;
	for (size_t i = 0; i < size * size; ++i) {
		ChunkGeometry& curChunk = chunkGeometries[i];
		for (size_t j = 0; j < curChunk.length; ++j) {
			geometry[written + j] = curChunk.geometry[j];
		}
		written += curChunk.length;
		delete[] curChunk.geometry;
	}
	delete[] chunkGeometries;
	return written;
#endif // !MULT
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