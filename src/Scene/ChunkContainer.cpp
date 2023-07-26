#include "ChunkContainer.h"

ChunkContainer::ChunkContainer(World& world, size_t size, glm::vec2 center) : world(world), size(size), xOffset(0), zOffset(0),
cornerPos(static_cast<int>(center.x) - (size / 2), static_cast<int>(center.y) - (size / 2)),
chunks(new Chunk* [size * size]) {
	generateChunks();
};

ChunkContainer::~ChunkContainer() {
	clearChunks();
	delete[] chunks;
};

void ChunkContainer::generateChunks() {
	size_t index;
	glm::ivec2 pos;
	for (size_t x = cornerPos.x; x < cornerPos.x + size; ++x) {
		for (size_t z = cornerPos.y; z < cornerPos.y + size; ++z) {
			pos.x = x; pos.y = z;
			index = posToIndex(pos);
			chunks[index] = new Chunk(pos, world);
		}
	}
}

void ChunkContainer::clearChunks() {
	for (size_t i = 0; i < size * size; ++i) {
		delete chunks[i];
	}
}