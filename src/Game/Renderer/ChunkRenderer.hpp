#pragma once
#include "../GameObjects/Chunk.hpp"
#include "glm/vec2.hpp"

#include <memory>

namespace Renderer
{
	class ChunkRenderer
	{
	public:
		ChunkRenderer();

		void render();
		void saveworld();
		void loadworld();
	private:
		glm::vec2 chunks_coords[256];
		std::unique_ptr<Game::Chunk> chunk;
	};
}