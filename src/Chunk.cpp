#include "Chunk.h"

//size_t defaultChunkHeight = 200;
//size_t defaultChunkSize = 32;
size_t defaultChunkHeight = 200;
size_t defaultChunkSize = 16;

const float cubeUvs[] = {
    // texture coords
    0.0f,  1.0f,
    1.0f,  1.0f,
    0.0f,  0.0f,
    0.0f,  0.0f,
    1.0f,  1.0f,
    1.0f,  0.0f,

    0.0f,  1.0f,
    1.0f,  1.0f,
    0.0f,  0.0f,
    0.0f,  0.0f,
    1.0f,  1.0f,
    1.0f,  0.0f,

    0.0f,  1.0f,
    1.0f,  1.0f,
    0.0f,  0.0f,
    0.0f,  0.0f,
    1.0f,  1.0f,
    1.0f,  0.0f,

    0.0f,  1.0f,
    1.0f,  1.0f,
    0.0f,  0.0f,
    0.0f,  0.0f,
    1.0f,  1.0f,
    1.0f,  0.0f,

    0.0f,  1.0f,
    1.0f,  1.0f,
    0.0f,  0.0f,
    0.0f,  0.0f,
    1.0f,  1.0f,
    1.0f,  0.0f,

    0.0f,  1.0f,
    1.0f,  1.0f,
    0.0f,  0.0f,
    0.0f,  0.0f,
    1.0f,  1.0f,
    1.0f,  0.0f,
};

/*const glm::vec3 vertices[] = {
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

};*/

const glm::vec3 vertices[] = {
    glm::vec3(-0.5f, -0.5f,  0.5f),
    glm::vec3( 0.5f, -0.5f,  0.5f),
    glm::vec3(-0.5f,  0.5f,  0.5f),
    glm::vec3(-0.5f,  0.5f,  0.5f),
    glm::vec3( 0.5f, -0.5f,  0.5f),
    glm::vec3( 0.5f,  0.5f,  0.5f),

    glm::vec3( 0.5f, -0.5f,  0.5f),
    glm::vec3( 0.5f, -0.5f, -0.5f),
    glm::vec3( 0.5f,  0.5f,  0.5f),
    glm::vec3( 0.5f,  0.5f,  0.5f),
    glm::vec3( 0.5f, -0.5f, -0.5f),
    glm::vec3( 0.5f,  0.5f, -0.5f),

    glm::vec3( 0.5f, -0.5f, -0.5f),
    glm::vec3(-0.5f, -0.5f, -0.5f),
    glm::vec3( 0.5f,  0.5f, -0.5f),
    glm::vec3( 0.5f,  0.5f, -0.5f),
    glm::vec3(-0.5f, -0.5f, -0.5f),
    glm::vec3(-0.5f,  0.5f, -0.5f),

    glm::vec3( -0.5f, -0.5f, -0.5f),
    glm::vec3( -0.5f, -0.5f,  0.5f),
    glm::vec3( -0.5f,  0.5f, -0.5f),
    glm::vec3( -0.5f,  0.5f, -0.5f),
    glm::vec3( -0.5f, -0.5f,  0.5f),
    glm::vec3( -0.5f,  0.5f,  0.5f),

    glm::vec3(-0.5f, 0.5f,  0.5f),
    glm::vec3( 0.5f, 0.5f,  0.5f),
    glm::vec3(-0.5f, 0.5f, -0.5f),
    glm::vec3(-0.5f, 0.5f, -0.5f),
    glm::vec3( 0.5f, 0.5f,  0.5f),
    glm::vec3(0.5f, 0.5f, -0.5f),

    glm::vec3(0.5f, -0.5f,  0.5f),
    glm::vec3(-0.5f,  -0.5f,  0.5f),
    glm::vec3(0.5f, -0.5f, -0.5f),
    glm::vec3(0.5f, -0.5f, -0.5f),
    glm::vec3(-0.5f,  -0.5f,  0.5f),
    glm::vec3(-0.5f,  -0.5f, -0.5f),

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
	if (position.x >= size || position.z >= size || position.y >= height) {
		throw "Chunk.position invalid argument : argument is too large";
	}
	return *blockMatrix[getBlockIndex(position)];
}

void Chunk::generate() {
	generated = true;
	static const unsigned int groundHeight = 100;
	static const unsigned int rockDepth = 3;
	for (size_t ix = 0; ix < size; ++ix) {
		for (size_t iy = 0; iy < height; ++iy) {
			for (size_t iz = 0; iz < size; ++iz) {
				BlockType type = BlockType::Air;
                if (iy < groundHeight -1) {
                    if (iy < groundHeight - rockDepth) {
                        type = BlockType::Stone;
                    }
                    else {
                        type = BlockType::Dirt;
                    }
                }else if (iy < groundHeight) {
                    type = BlockType::Grass;
                }
				size_t index = getBlockIndex(glm::uvec3(ix, iy, iz));
                if (!blockMatrix[index] ) { 
                    blockMatrix[index] = new BlockType; 
                }
                *blockMatrix[index] = type;
			}
		}
	}
}

size_t Chunk::getGeometry(glm::vec2*& uvs, glm::vec3*& verts) {
    uvs = new glm::vec2[blockCount * 6 * 6];
    verts = new glm::vec3 [blockCount * 6 * 6];
    for (size_t i = 0; i < blockCount; ++i) {
        if (*blockMatrix[i] == BlockType::Air) { continue; }
        glm::vec3 pos = getIndexPos(i);
        for (size_t j = 0; j < 6 * 6; ++j) {
            verts[i * 6 * 6 + j] = vertices[j] + pos;
            glm::vec2 newUVs = glm::vec2(cubeUvs[2 * j], cubeUvs[2 * j + 1]);
            blockUvs(*blockMatrix[i], newUVs);
            uvs[i * 6 * 6 + j] = newUVs;
        }
    }
	return blockCount * 6 * 6;
}

size_t Chunk::getBlockIndex(glm::uvec3 position) {
	if (position.x >= size || position.z >= size || position.y >= height) {
		throw "Chunk.getBlockIndex invalid argument : argument is too large";
	}
	return position.x + (position.y * size + position.z) * size;
}

glm::uvec3 Chunk::getIndexPos(size_t index) {
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