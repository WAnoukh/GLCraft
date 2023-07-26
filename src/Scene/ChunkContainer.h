#pragma once
#include "Chunk.h"


class ChunkContainer
{
public:
	ChunkContainer(World& world, size_t size, glm::vec2 center);
	~ChunkContainer();

	void updatePos(glm::ivec2);

private:
	World& world;
	size_t size;
	size_t xOffset;
	size_t zOffset;
	glm::ivec2 cornerPos;
	Chunk** chunks;

	inline size_t posToIndex(glm::ivec2 pos) { 
		return ((pos.x + xOffset)%size) + size * ((pos.y + zOffset)%size); 
	}
	inline glm::ivec2 indexToPos(size_t i) { return glm::ivec2(i%size + xOffset, i/size + zOffset); }

	void generateChunks();
	void clearChunks();
};

