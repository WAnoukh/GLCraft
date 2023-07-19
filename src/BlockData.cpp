#include "BlockData.h"
#include "../third_parties/json/json.hpp"
#include "../third_parties/json/json.hpp"
#include <fstream>
#include <iostream>
#include <vector>

const std::string ATLAS_PATH = "src/Rendering/Textures/AtlasInfos.json";
const std::string BLOCK_DATA_PATH = "src/Rendering/Textures/BlockData.json";

using json = nlohmann::json;

BlockManager* BlockManager::bm = nullptr;

void BlockManager::refreshData() {
	// Reading atlas data to know texture order
	std::ifstream f(ATLAS_PATH);
	json textureData = json::parse(f);
	std::vector<std::string> textureNames = textureData["Blocks"];
	for (size_t i = 0; i < textureNames.size(); ++i) {
		std::string& name = textureNames[i];
		textureNameMap[name] = i;
	}

	// Reading block infos
	std::ifstream f2(BLOCK_DATA_PATH);
	json blockData = json::parse(f2);
	size_t count = 0;
	for (json::iterator it = blockData.begin(); it != blockData.end(); ++it) {
		BlockData& curBlock = blocksData[count];
		curBlock.name = it.key();
		curBlock.ID = count;
		curBlock.TextureUp = textureNameMap[(*it)["TOP"]];
		curBlock.TextureSide = textureNameMap[(*it)["SIDE"]];
		curBlock.TextureDown = textureNameMap[(*it)["DOWN"]];
		++count;
	}
	blocksDataSize = count;
}

size_t copyBlockGeometry(unsigned short id, glm::vec3*& verts, glm::vec2*& uvs, const size_t beggin) {
	BlockData& curBlock = BlockManager::getInstance().getBlockData(id);

	// TOP FACE
	glm::vec2 topUvOffset = textureIdToUv(curBlock.TextureUp);
	for (size_t i = 0; i < 6; ++i) {
		verts[beggin + i] = FACE_UP[i];
		uvs[beggin + i] = FACE_UV[i] + topUvOffset;
	}

	// BOTTOM FACE
	glm::vec2 bottomUvOffset = textureIdToUv(curBlock.TextureDown);
	for (size_t i = 0; i < 6; ++i) {
		verts[beggin + 6 + i] = FACE_DOWN[i];
		uvs[beggin + 6 + i] = FACE_UV[i] + bottomUvOffset;
	}

	// SIDE FACE
	glm::vec2 sideUvOffset = textureIdToUv(curBlock.TextureDown);
	for (size_t i = 0; i < 6; ++i) {
		glm::vec2 sideUv = FACE_UV[i] + sideUvOffset;
		verts[beggin + 12 + i] = FACE_EAST[i];
		verts[beggin + 18 + i] = FACE_NORTH[i];
		verts[beggin + 24 + i]	 = FACE_WEST[i];
		verts[beggin + 30 + i] = FACE_SOUTH[i];
		for (size_t j = 0; j < 6; ++j) {
			uvs[beggin + j*6 + 12 + i] = sideUv;
		}
	}
	return static_cast<size_t>(6) * 6;
}

glm::vec2 textureIdToUv(unsigned short int id) {
	return glm::vec2(static_cast<float>(id % ATLAS_WIDTH), static_cast<float>(id / ATLAS_WIDTH));
}