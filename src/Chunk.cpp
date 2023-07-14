#include "Chunk.h"

//size_t defaultChunkHeight = 200;
//size_t defaultChunkSize = 32;
size_t defaultChunkHeight = 3;
size_t defaultChunkSize = 1;

const float cubeUvs[] = {
    // texture coords
    0.0f,  0.0f,
    1.0f,  0.0f,
    1.0f,  1.0f,
    1.0f,  1.0f,
    0.0f,  1.0f,
    0.0f,  0.0f,

    0.0f,  0.0f,
    1.0f,  0.0f,
    1.0f,  1.0f,
    1.0f,  1.0f,
    0.0f,  1.0f,
    0.0f,  0.0f,

    1.0f,  0.0f,
    1.0f,  1.0f,
    0.0f,  1.0f,
    0.0f,  1.0f,
    0.0f,  0.0f,
    1.0f,  0.0f,

    1.0f,  0.0f,
    1.0f,  1.0f,
    0.0f,  1.0f,
    0.0f,  1.0f,
    0.0f,  0.0f,
    1.0f,  0.0f,

    0.0f,  1.0f,
    1.0f,  1.0f,
    1.0f,  0.0f,
    1.0f,  0.0f,
    0.0f,  0.0f,
    0.0f,  1.0f,

    0.0f,  1.0f,
    1.0f,  1.0f,
    1.0f,  0.0f,
    1.0f,  0.0f,
    0.0f,  0.0f,
    0.0f,  1.0f
};

const glm::vec3 vertices[] = {
    glm::vec3(-0.5f, -0.5f, -0.5f),
    glm::vec3(0.5f, -0.5f, -0.5f),
    glm::vec3(0.5f,  0.5f, -0.5f),
    glm::vec3(0.5f,  0.5f, -0.5f),
    glm::vec3(-0.5f,  0.5f, -0.5f),
    glm::vec3(-0.5f, -0.5f, -0.5f),

    glm::vec3(-0.5f, -0.5f,  0.5f),
    glm::vec3(0.5f, -0.5f,  0.5f),
    glm::vec3(0.5f,  0.5f,  0.5f),
    glm::vec3(0.5f,  0.5f,  0.5f),
    glm::vec3(-0.5f,  0.5f,  0.5f),
    glm::vec3(-0.5f, -0.5f,  0.5f),

    glm::vec3(-0.5f,  0.5f,  0.5f),
    glm::vec3(-0.5f,  0.5f, -0.5f),
    glm::vec3(-0.5f, -0.5f, -0.5f),
    glm::vec3(-0.5f, -0.5f, -0.5f),
    glm::vec3(-0.5f, -0.5f,  0.5f),
    glm::vec3(-0.5f,  0.5f,  0.5f),

    glm::vec3(0.5f,  0.5f,  0.5f),
    glm::vec3(0.5f,  0.5f, -0.5f),
    glm::vec3(0.5f, -0.5f, -0.5f),
    glm::vec3(0.5f, -0.5f, -0.5f),
    glm::vec3(0.5f, -0.5f,  0.5f),
    glm::vec3(0.5f,  0.5f,  0.5f),

    glm::vec3(-0.5f, -0.5f, -0.5f),
    glm::vec3(0.5f, -0.5f, -0.5f),
    glm::vec3(0.5f, -0.5f,  0.5f),
    glm::vec3(0.5f, -0.5f,  0.5f),
    glm::vec3(-0.5f, -0.5f,  0.5f),
    glm::vec3(-0.5f, -0.5f, -0.5f),

    glm::vec3(-0.5f,  0.5f, -0.5f),
    glm::vec3(0.5f,  0.5f, -0.5f),
    glm::vec3(0.5f,  0.5f,  0.5f),
    glm::vec3(0.5f,  0.5f,  0.5f),
    glm::vec3(-0.5f,  0.5f,  0.5f),
    glm::vec3(-0.5f,  0.5f, -0.5f)

};


void setChunkSize(size_t newSize) {
	defaultChunkSize = newSize;
}

void setChunkHeight(size_t newHeight) {
	defaultChunkHeight = newHeight;
}

Chunk::~Chunk() {
	if (generated){
		for (size_t i = 0; i < blockCount; ++i) {
			delete blockMatrix[i];
		}
	}
	delete[] blockMatrix;
}

BlockType Chunk::getBlock(glm::uvec3 position) {
	if (position.x >= size || position.y >= size || position.z >= height) {
		throw "Chunk.position invalid argument : argument is too large";
	}
	return *blockMatrix[getBlockIndex(position)];
}

void Chunk::generate() {
	generated = true;
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
				size_t index = getBlockIndex(glm::uvec3(ix, iy, iz));
				*blockMatrix[index] = type;
			}
		}
	}
}

size_t Chunk::getGeometry(glm::vec2*& uvs, glm::vec3*& verts) {
    uvs = new glm::vec2[blockCount * 6*6];
    verts = new glm::vec3 [blockCount * 6 * 6];
    for (size_t i = 0; i < blockCount; ++i) {
        glm::vec3 pos = getIndexPos(i);
        for (size_t j = 0; j < 6 * 6; ++j) {
            verts[i * 6 * 6 + j] = vertices[j];
            uvs[i * 6 * 6 + j] = glm::vec2(cubeUvs[2*j], cubeUvs[2 * j+1]);
        }
    }
	return blockCount * 6 * 6;
}

size_t Chunk::getBlockIndex(glm::uvec3 position) {
	if (position.x >= size || position.y >= size || position.z >= height) {
		throw "Chunk.getBlockIndex invalid argument : argument is too large";
	}
	return position.x + (position.z * size + position.y) * size;
}

glm::uvec3 Chunk::getIndexPos(size_t index) {
	if (index >= blockCount) {
		throw "Chunk.getBlockIndex invalid argument : argument is too large";
	}
	unsigned int z = index / (height * size);
	index %= height * size;
	unsigned int y = index / size;
	index %= size;
	unsigned int x = index;

	return glm::uvec3(x, y, z);
}