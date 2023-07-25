#pragma once
#include "Chunk.h"
#include "../third_parties/glm/glm.hpp"

extern size_t CHUNK_COUNT;

struct ChunkGeometry {
	float* geometry = nullptr;
	size_t length = 0;
};

class World
{
public:
	World();

	size_t getGeometry(float*& geometry);
	bool isBlockLoaded(glm::vec3 pos) const;
	BlockId getBlock (glm::vec3 pos) const;
	unsigned short int getBlockOpacity(glm::vec3 pos) const;
private:
	size_t size = 40;
	Chunk** chunks;

	size_t posToIndex(int x, int z) const;
	void indexToPos(size_t index, int& x, int& y) const;
	
};

