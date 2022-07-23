#pragma once
#include "../GameObjects/Chunk.hpp"
#include "../../Resources/ResourceManager.hpp"
#include "glm/vec2.hpp"

#include <memory>
#include <vector>

namespace Renderer
{
	class ChunkRenderer
	{
	public:
		ChunkRenderer(std::shared_ptr<RenderEngine::Texture2D> pTexture,
					  std::shared_ptr<RenderEngine::ShaderProgram> pShaderProgram);

		void render(glm::vec3& camera_position);
		void generate_world();
		void saveworld();
		void loadworld();

		std::vector<Game::Chunk::s_blocks_polygones> blocks_polygones;
	private:
		std::vector<glm::vec2> chunks_coords;
		std::unique_ptr<Game::Chunk> chunk;
		std::vector<std::shared_ptr<std::pair<std::string, glm::vec3>>> m_blocks;
		std::vector<std::shared_ptr<std::pair<std::string, glm::vec3>>> blocks;
	};
}