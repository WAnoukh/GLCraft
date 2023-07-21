#pragma once
#include <map>
#include <string>
#include <iostream>
#include "../third_parties/glm/glm.hpp"

using BlockId = unsigned short int;

const glm::vec2 FACE_UV[6] = {
	// texture coords
	glm::vec2(0.0f,  1.0f),
	glm::vec2(1.0f,  1.0f),
	glm::vec2(0.0f,  0.0f),
	glm::vec2(0.0f,  0.0f),
	glm::vec2(1.0f,  1.0f),
	glm::vec2(1.0f,  0.0f)
};

const glm::vec3 FACE_NORTH[6]{
	glm::vec3(0.5f, -0.5f,  0.5f),
	glm::vec3(0.5f, -0.5f, -0.5f),
	glm::vec3(0.5f,  0.5f,  0.5f),
	glm::vec3(0.5f,  0.5f,  0.5f),
	glm::vec3(0.5f, -0.5f, -0.5f),
	glm::vec3(0.5f,  0.5f, -0.5f)
};

const glm::vec3 FACE_SOUTH[6]{
	glm::vec3(-0.5f, -0.5f, -0.5f),
	glm::vec3(-0.5f, -0.5f,  0.5f),
	glm::vec3(-0.5f,  0.5f, -0.5f),
	glm::vec3(-0.5f,  0.5f, -0.5f),
	glm::vec3(-0.5f, -0.5f,  0.5f),
	glm::vec3(-0.5f,  0.5f,  0.5f)
};

const glm::vec3 FACE_EAST[6]{
	glm::vec3(-0.5f, -0.5f,  0.5f),
	glm::vec3(0.5f, -0.5f,  0.5f),
	glm::vec3(-0.5f,  0.5f,  0.5f),
	glm::vec3(-0.5f,  0.5f,  0.5f),
	glm::vec3(0.5f, -0.5f,  0.5f),
	glm::vec3(0.5f,  0.5f,  0.5f)
};

const glm::vec3 FACE_WEST[6]{
	glm::vec3(0.5f, -0.5f, -0.5f),
	glm::vec3(-0.5f, -0.5f, -0.5f),
	glm::vec3(0.5f,  0.5f, -0.5f),
	glm::vec3(0.5f,  0.5f, -0.5f),
	glm::vec3(-0.5f, -0.5f, -0.5f),
	glm::vec3(-0.5f,  0.5f, -0.5f)
};

const glm::vec3 FACE_UP[6]{
	glm::vec3(-0.5f,  0.5f,  0.5f),
	glm::vec3(0.5f,  0.5f,  0.5f),
	glm::vec3(-0.5f,  0.5f, -0.5f),
	glm::vec3(-0.5f,  0.5f, -0.5f),
	glm::vec3(0.5f,  0.5f,  0.5f),
	glm::vec3(0.5f,  0.5f, -0.5f)
};

const glm::vec3 FACE_DOWN[6] = {
	glm::vec3( 0.5f, -0.5f,  0.5f),
	glm::vec3(-0.5f, -0.5f,  0.5f),
	glm::vec3( 0.5f, -0.5f, -0.5f),
	glm::vec3( 0.5f, -0.5f, -0.5f),
	glm::vec3(-0.5f, -0.5f,  0.5f),
	glm::vec3(-0.5f, -0.5f, -0.5f),
};

const size_t ATLAS_WIDTH = 32;
const size_t ATLAS_SIZE = ATLAS_WIDTH * ATLAS_WIDTH;

namespace Opacity {
	const unsigned short int INVISIBLE = 0;
	const unsigned short int OPAQUE = 1;
	const unsigned short int TRANSPARENT = 2;
	const unsigned short int SEMI_TRANSPARENT = 3;

}



/*enum class BlockType {
	Air,
	Dirt,
	Grass,
	Stone
};*/

struct BlockData {
	std::string name = "";
	BlockId ID = 0;
	unsigned short int TextureUp = 0;
	unsigned short int TextureSide = 0;
	unsigned short int TextureDown = 0;
	unsigned short int opacity = 0;
};

class BlockManager {
public:
	static BlockManager& getInstance() {
		if (bm == nullptr) {
			bm = new BlockManager();
		}
		return *bm;
	}
	static void freeInstance() {
		delete bm;
		bm = nullptr;
	}
	void refreshData();
	BlockData& getBlockData(BlockId id) { return blocksData[id]; }
	unsigned short int getBlockOpacity(BlockId id){ return blocksData[id].opacity; }
	unsigned short int getBlockId(std::string& name) {
		for (size_t i = 0; i < blocksDataSize; ++i) {
			if (blocksData[i].name == name) {
				return blocksData[i].ID;
			}
		}
		throw "BlockManager::getBlockData error, name not found !";
	}
private:
	static BlockManager* bm;
	std::map<std::string, int> textureNameMap;
	BlockData blocksData[ATLAS_SIZE];
	size_t blocksDataSize;
	BlockManager() { refreshData(); };
	~BlockManager() {};
};

glm::vec2 textureIdToUv(unsigned short int id);

size_t copyBlockGeometry(BlockId id, glm::vec3*& verts, glm::vec2*& uvs, size_t beginning, char neighbor);