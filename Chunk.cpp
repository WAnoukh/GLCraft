#include "Chunk.h"

Chunk::~Chunk() {
	for (size_t i = 0; i < blockCount; ++i) { delete blockMatrix[i]; }
	delete[] blockMatrix;
}

BlockType Chunk::getBlock(glm::uvec3 position) {
	if (position.x >= size || position.y >= size || position.z >= height) {
		throw "Chunk.position invalid argument : argument is too large";
	}
	return *blockMatrix[getBlockIndex(position)];
}

size_t Chunk::getBlockIndex(glm::uvec3 position) {
	if (position.x >= size || position.y >= size || position.z >= height) {
		throw "Chunk.getBlockIndex invalid argument : argument is too large";
	}
	return position.x + (position.y * size + position.y) * size;
}

void Chunk::generate() {
	static const unsigned int groundHeight = 30;
	static const unsigned int rockDepth = 4;
	for (size_t ix = 0; ix < size; ++ix) {
	for (size_t iy = 0; iy < size; ++iy) {
	for (size_t iz = 0; iz < size; ++iz) {
		BlockType type = BlockType::Air;
		if (iz < groundHeight-1) {
			if (iz < groundHeight - rockDepth) {
				type = BlockType::Stone;
			}
			else{
				type = BlockType::Dirt;
			}
		}
		else if (iz < groundHeight) {
			type = BlockType::Grass;
		}
		size_t index = getBlockIndex(glm::uvec3(x, y, z));
		*blockMatrix[index] = type;
	}
	}
	}
}