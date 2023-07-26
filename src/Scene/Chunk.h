#pragma once
#include "BlockData.h"
#include "../../third_parties/glm/glm.hpp"

extern size_t defaultChunkHeight;
extern size_t defaultChunkSize;

class World;

/*
extern const float cubeUvs[];
extern const glm::vec3 vertices[];
*/

class Chunk
{
public:
	Chunk(glm::ivec2 position, World& world) : world(world), size(defaultChunkSize), height(defaultChunkHeight),
	blockCount(size*size*height), chunkX(position.x), chunkZ(position.y),
	chunkPos(position.x, 0.0f, position.y),
	blockMatrix(new unsigned short int[blockCount]) {
		generate();
	}
	~Chunk();
	Chunk(const Chunk&) = delete;
	Chunk& operator=(Chunk const&) = delete;
	size_t getSize() const { return size; }
	size_t getHeight() const { return height; }
	size_t getBlockCount() const { return blockCount; }
	glm::vec3 getIndexWorldPos(size_t index);
	BlockId getBlock(glm::vec3 position);
	bool isBlockInChunk(glm::vec3 position);

	void generate();

	size_t getGeometry(glm::vec3*& uvs, glm::vec3*& verts);

private:
	const World& world;
	const size_t size;
	const size_t height;
	const size_t blockCount;
	const unsigned int chunkX;
	const unsigned int chunkZ;
	const glm::vec3 chunkPos;
	bool generated = false;
	unsigned short int* blockMatrix;
	
	size_t getBlockIndexFromLocalPos(glm::uvec3 position);
	glm::uvec3 getIndexLocalPos(size_t index);
};

