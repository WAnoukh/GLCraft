#pragma once
#include "BlockData.h"
#include "third_parties/glm/glm.hpp"

size_t defaultChunkHeight = 200;
size_t defaultChunkSize = 32;

class Chunk
{
public:
	Chunk(unsigned int x, unsigned int y): size(defaultChunkSize), height(defaultChunkHeight), blockCount(size*size*height),
											x(x), y(y), blockMatrix(new BlockType*[blockCount]) {}
	~Chunk();
	Chunk(const Chunk&) = delete;
	Chunk& operator=(Chunk const&) = delete;

	size_t getSize() const { return size; }
	size_t getHeight() const { return height; }
	BlockType getBlock(glm::uvec3 position);
	size_t getBlockIndex(glm::uvec3 position);

	void generate();

private:
	const size_t size;
	const size_t height;
	const size_t blockCount;
	const unsigned int x;
	const unsigned int y;
	BlockType** blockMatrix;


};

