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
private:
	size_t size = 10;
	Chunk** chunks;

	size_t posToIndex(int x, int z);

	void indexToPos(size_t index, int& x, int& y);
	
};

