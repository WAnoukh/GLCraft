#include "Chunk.h"
#include "../third_parties/PerlinNoise/PerlinNoise.hpp"
#include "World.h"

const BlockId AIR   = 0;
const BlockId STONE = 1;
const BlockId DIRT  = 2;
const BlockId GRASS = 3;


//size_t defaultChunkHeight = 200;
//size_t defaultChunkSize = 32;
size_t defaultChunkHeight = 200;
size_t defaultChunkSize = 16;

void setChunkSize(size_t newSize) {
	defaultChunkSize = newSize;
}

void setChunkHeight(size_t newHeight) {
	defaultChunkHeight = newHeight;
}

Chunk::~Chunk() {
	if (generated){
		for (size_t i = 0; i < blockCount; ++i) {
			if (blockMatrix[i])
				delete blockMatrix[i];
		}
	}
	delete[] blockMatrix;
}

BlockId Chunk::getBlock(glm::vec3 worldPos) {
	worldPos -= glm::vec3(chunkX*size, 0.0f, chunkZ*size);
	if (isBlockInChunk(worldPos)) {
		throw "Chunk.position invalid argument : argument is too large";
	}
	return *blockMatrix[getBlockIndexFromLocalPos(static_cast<glm::uvec3>(worldPos))];
}

bool Chunk::isBlockInChunk(glm::vec3 worldPos) {
	return (worldPos.x >= size || worldPos.z >= size || worldPos.y >= height || worldPos.x < 0 || worldPos.z < 0 || worldPos.y < 0);
}

glm::vec3 Chunk::getIndexWorldPos(size_t index) {
	if (index >= blockCount) {
		throw "Chunk.getBlockIndex invalid argument : argument is too large";
	}
	unsigned int y = index / (size * size);
	index %= size * size;
	unsigned int z = index / size;
	index %= size;
	unsigned int x = index;

	return glm::vec3(x - chunkX, y, z - chunkZ);
}



void Chunk::generate() {
	const siv::PerlinNoise::seed_type seed = 123456u;
	const siv::PerlinNoise perlin{ seed };
	generated = true;
	static const unsigned int groundHeightDefault = 150;
	static const unsigned int rockDepth = 3;
	for (size_t ix = 0; ix < size; ++ix) {
		for (size_t iz = 0; iz < size; ++iz) {
			const unsigned int groundHeight = groundHeightDefault + perlin.octave2D_01(((ix+chunkX*size) * 0.01), ((iz+chunkZ*size) * 0.01), 4)*10;
			for (size_t iy = 0; iy < height; ++iy) {
                BlockId type = AIR;
                if (iy < groundHeight -1) {
                    if (iy < groundHeight - rockDepth - 10 +perlin.octave2D_01(((ix + chunkX * size + 500000) * 0.01), ((iz + chunkZ * size + 500000) * 0.01), 4) * 10) {
                        type = STONE;
                    }
                    else {
                        type = DIRT;
                    }
                }else if (iy < groundHeight) {
                    type = GRASS;
                }
				size_t index = getBlockIndexFromLocalPos(glm::uvec3(ix, iy, iz));
                if (!blockMatrix[index] ) { 
                    blockMatrix[index] = new BlockId;
                }
                *blockMatrix[index] = type;
			}
		}
	}
}

size_t Chunk::getGeometry(glm::vec3*& uvs, glm::vec3*& verts) {
	uvs = new glm::vec3[blockCount * 6 * 6];
	verts = new glm::vec3[blockCount * 6 * 6];
	size_t length = 0;
	for (size_t i = 0; i < blockCount; ++i) {
		BlockManager& bm = BlockManager::getInstance();
		if (bm.getBlockOpacity(*blockMatrix[i]) == 0) { //if block invisible
			continue;
		}
		glm::uvec3 pos = getIndexLocalPos(i);

		//Checking block occlusions
		char occlusionMask = 0b00111111;

		//Top face
		if (pos.y < height - 1) { //Not the highest layer
			size_t index = getBlockIndexFromLocalPos(pos + glm::uvec3(0.0f, 1.0f, 0.0f));
			BlockId& topBlock = *blockMatrix[index];
			if (bm.getBlockOpacity(topBlock) == Opacity::OPAQUE) {
				occlusionMask &= ~1; // editing the first bit
			}
		}

		//Bottom face
		if (pos.y > 0) { 
			size_t index = getBlockIndexFromLocalPos(pos + glm::uvec3(0.0f, -1.0f, 0.0f));
			BlockId botBlock = *blockMatrix[index];
			if (bm.getBlockOpacity(botBlock) == Opacity::OPAQUE) {
				occlusionMask &= ~(1 << 1); // editing the second bit
			}
		}

		if (pos.x < size -1) { //NORTH
			size_t index = getBlockIndexFromLocalPos(pos + glm::uvec3(1.0f, 0.0f, 0.0f));
			BlockId botBlock = *blockMatrix[index];
			if (bm.getBlockOpacity(botBlock) == Opacity::OPAQUE) {
				occlusionMask &= ~(1 << 2); // editing the second bit
			}
		}else if (world.getBlockOpacity(
			chunkPos * static_cast<float>(size) + static_cast<glm::vec3>(pos) + glm::vec3(1.0f, .0f, .0f)
		) == Opacity::OPAQUE) {
			occlusionMask &= ~(1 << 2);
		}

		if (pos.z < size - 1) { //EAST
			size_t index = getBlockIndexFromLocalPos(pos + glm::uvec3(0.0f, 0.0f, 1.0f));
			BlockId botBlock = *blockMatrix[index];
			if (bm.getBlockOpacity(botBlock) == Opacity::OPAQUE) {
				occlusionMask &= ~(1 << 3); // editing the second bit
			}
		}else if (world.getBlockOpacity(
			chunkPos * static_cast<float>(size) + static_cast<glm::vec3>(pos) + glm::vec3(.0f, .0f, 1.0f)
		) == Opacity::OPAQUE) {
			occlusionMask &= ~(1 << 3);
		}

		if (pos.x > 0) { //SOUTH
			size_t index = getBlockIndexFromLocalPos(pos + glm::uvec3(-1.0f, 0.0f, 0.0f));
			BlockId botBlock = *blockMatrix[index];
			if (bm.getBlockOpacity(botBlock) == Opacity::OPAQUE) {
				occlusionMask &= ~(1 << 4); // editing the second bit
			}
		}else if (world.getBlockOpacity(
			chunkPos* static_cast<float>(size) + static_cast<glm::vec3>(pos) + glm::vec3(-1.0f, .0f, .0f)
			) == Opacity::OPAQUE) {
			occlusionMask &= ~(1 << 4);
		}

		if (pos.z > 0) { //WEST
			size_t index = getBlockIndexFromLocalPos(pos + glm::uvec3(0.0f, 0.0f, -1.0f));
			BlockId botBlock = *blockMatrix[index];
			if (bm.getBlockOpacity(botBlock) == Opacity::OPAQUE) {
				occlusionMask &= ~(1 << 5); // editing the second bit
			}
		}else if (world.getBlockOpacity(
			chunkPos * static_cast<float>(size) + static_cast<glm::vec3>(pos) + glm::vec3(.0f, .0f, -1.0f)
		) == Opacity::OPAQUE) {
			occlusionMask &= ~(1 << 5);
		}

		size_t newLength = copyBlockGeometry(*blockMatrix[i], verts, uvs, length, occlusionMask);
		for (size_t j = length; j < newLength; ++j) {
			verts[j] += static_cast<glm::vec3>(pos) + (chunkPos * static_cast<float>(size));
		}
		length = newLength;
	}
	std::cout << length << std::endl;
	return length;
}

size_t Chunk::getBlockIndexFromLocalPos(glm::uvec3 position) {
	if (position.x >= size || position.z >= size || position.y >= height) {
		throw "Chunk.getBlockIndex invalid argument : argument is too large";
	}
	return position.x + (position.y * size + position.z) * size;
}

glm::uvec3 Chunk::getIndexLocalPos(size_t index) {
	if (index >= blockCount) {
		throw "Chunk.getBlockIndex invalid argument : argument is too large";
	}
	unsigned int y = index / (size*size);
	index %= size * size;
	unsigned int z = index / size;
	index %= size;
	unsigned int x = index;

	return glm::uvec3(x, y, z);
}

