#include "BlockData.h"
#include "../../third_parties/json/json.hpp"
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
		BlockData& curBlock = blocksData[(*it)["ID"]];
		curBlock.name = it.key();
		curBlock.ID = (*it)["ID"];

		const std::string str_null = "null";

		std::cout << (*it)["TOP"] << std::endl;
		if ((*it)["TOP"] != "null") {
			curBlock.TextureUp = textureNameMap[(*it)["TOP"]];
		}

		if ((*it)["TOP"] != str_null) {
			curBlock.TextureSide = textureNameMap[(*it)["SIDE"]];
		}

		if ((*it)["TOP"] != str_null) {
			curBlock.TextureDown = textureNameMap[(*it)["DOWN"]];
		}

		if ((*it)["OPACITY"] != str_null) {
			if ((*it)["OPACITY"] == "opaque") {
				curBlock.opacity = 1;
			}else if ((*it)["OPACITY"] == "transparent") {
				curBlock.opacity = 2;
			}else if ((*it)["OPACITY"] == "semi-transparent") {
				curBlock.opacity = 3;
			}
		}


		++count;
	}
	blocksDataSize = count;
}

size_t copyBlockGeometry(BlockId id, glm::vec3*& verts, glm::vec3*& uvs, const size_t beginning, char neighbor) {
	BlockData& curBlock = BlockManager::getInstance().getBlockData(id);

	size_t written = 0;

	// TOP FACE
	if (neighbor & 1) { //Checking the first bit
		for (size_t i = 0; i < 6; ++i) {
			verts[beginning + i] = FACE_UP[i];
			uvs[beginning + i] = glm::vec3(FACE_UV[i].x, FACE_UV[i].y, curBlock.TextureUp);
		}
		written += 6;
	}

	// BOTTOM FACE
	if ((neighbor >> 1) & 1) {//Checking the second bit
		for (size_t i = 0; i < 6; ++i) {
			verts[beginning + written + i] = FACE_DOWN[i];
			uvs[beginning + written + i] = glm::vec3(FACE_UV[i].x, FACE_UV[i].y, curBlock.TextureDown);
		}
		written += 6;
	}

	// SIDE FACE
	if ((neighbor >> 2) & 1) {
		for (size_t i = 0; i < 6; ++i) {
			verts[beginning + written + i] = FACE_NORTH[i];
			//uvs[beginning + written + i] = sideUv;
			uvs[beginning + written + i] = glm::vec3(FACE_UV[i].x, FACE_UV[i].y, curBlock.TextureSide);
		}
		written += 6;
	}
	if ((neighbor >> 3) & 1) {
		for (size_t i = 0; i < 6; ++i) {
			verts[beginning + written + i] = FACE_EAST[i];
			//uvs[beginning + written + i] = sideUv;
			uvs[beginning + written + i] = glm::vec3(FACE_UV[i].x, FACE_UV[i].y, curBlock.TextureSide);
		}
		written += 6;
	}
	if ((neighbor >> 4) & 1) {
		for (size_t i = 0; i < 6; ++i) {
			verts[beginning + written + i] = FACE_SOUTH[i];
			//uvs[beginning + written + i] = sideUv;
			uvs[beginning + written + i] = glm::vec3(FACE_UV[i].x, FACE_UV[i].y, curBlock.TextureSide);
		}
		written += 6;
	}
	if ((neighbor >> 5) & 1) {
		for (size_t i = 0; i < 6; ++i) {
			verts[beginning + written + i] = FACE_WEST[i];
			//uvs[beginning + written + i] = sideUv;
			uvs[beginning + written + i] = glm::vec3(FACE_UV[i].x, FACE_UV[i].y, curBlock.TextureSide);
		}
		written += 6;
	}
	return beginning + written;
}

glm::vec2 textureIdToUv(unsigned short int id) {
	return glm::vec2(static_cast<float>(id % ATLAS_WIDTH), static_cast<float>(id / ATLAS_WIDTH));
}