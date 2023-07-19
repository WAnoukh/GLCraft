#pragma once
#include "BlockData.h"
#include "../third_parties/glm/glm.hpp"

extern size_t defaultChunkHeight;
extern size_t defaultChunkSize;

/*
extern const float cubeUvs[];
extern const glm::vec3 vertices[];
*/

class Chunk
{
public:
	Chunk(glm::uvec2 position): size(defaultChunkSize), height(defaultChunkHeight), 
	blockCount(size*size*height), x(position.x), z(position.y), 
	blockMatrix(new unsigned short int*[blockCount]) {
		for (size_t i = 0; i < blockCount; ++i) {
			blockMatrix[i] = nullptr;
		}
		generate();
	}
	~Chunk();
	Chunk(const Chunk&) = delete;
	Chunk& operator=(Chunk const&) = delete;

	size_t getSize() const { return size; }
	size_t getHeight() const { return height; }
	size_t getBlockCount() const { return blockCount; }
	size_t getBlockIndex(glm::uvec3 position);
	glm::uvec3 getIndexPos(size_t index);
	BlockId getBlock(glm::uvec3 position);

	void generate();

	size_t getGeometry(glm::vec2*& uvs, glm::vec3*& verts);

private:
	const size_t size;
	const size_t height;
	const size_t blockCount;
	const unsigned int x;
	const unsigned int z;
	bool generated = false;
	unsigned short int** blockMatrix;
};

