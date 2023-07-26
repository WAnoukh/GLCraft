#pragma once
#include "Chunk.h"
#include "../../third_parties/glm/glm.hpp"
#include <list>

extern size_t CHUNK_COUNT;

struct ChunkGeometry {
	float* geometry = nullptr;
	size_t length = 0;
};


void chunkGeometryThread(Chunk** chunks, ChunkGeometry* cgs, size_t nb);

class World
{
public:
	World();
	size_t getGeometry(float*& geometry);
	bool isBlockLoaded(glm::vec3 pos) const;
	BlockId getBlock(glm::vec3 pos) const;
	unsigned short int getBlockOpacity(glm::vec3 pos) const;
private:
	size_t size = 50;
	Chunk** chunks;
	size_t posToIndex(int x, int z) const;
	void indexToPos(size_t index, int& x, int& y) const;

};

