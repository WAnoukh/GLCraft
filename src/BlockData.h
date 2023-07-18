#pragma once
#include <map>
#include <string>
#include <iostream>
#include "../third_parties/glm/glm.hpp"

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

const size_t ATLAS_SIZE = 32 * 32;

enum class BlockType {
	Air,
	Dirt,
	Grass,
	Stone
};

struct BlockData {
	std::string name = "";
	unsigned short int ID = 0;
	unsigned short int TextureUp = 0;
	unsigned short int TextureSide = 0;
	unsigned short int TextureDown = 0;
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
	BlockData& getBlockData(unsigned short int id) { return blocksData[id]; }
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

inline void blockUvs(BlockType bt, glm::vec2& uv) {
	
	switch (bt)
	{
	case BlockType::Air:
		uv = glm::vec2(1.0f, 1.0f);
		break;
	case BlockType::Dirt:
		uv.x += 2;
		break;
	case BlockType::Grass:
		uv.x += 1;
		break;
	case BlockType::Stone:
		uv.x += 3;
		break;
	default:
		break;
	}
	uv /= 32;
}


size_t copyBlockGeometry(BlockType bt, glm::vec3*& verts, glm::vec2*& uvs, size_t beggin);