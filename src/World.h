#pragma once
#include "Chunk.h"
#include "../third_parties/glm/glm.hpp"
class World
{
public:
	World(): chunk(new Chunk(glm::uvec2(0,0))) {}

	size_t getGeometry(float*& geometry);
private:
	Chunk* chunk;
};

