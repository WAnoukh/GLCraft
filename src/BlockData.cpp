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

size_t copyBlockGeometry(BlockType bt, glm::vec3*& verts, glm::vec2*& uvs, size_t beggin) {
	return 0;
}