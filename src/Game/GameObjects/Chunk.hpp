#pragma once
#include "glm/vec2.hpp"
#include "Block.hpp"
#include <vector>
#include <string>

namespace Game
{
	class Chunk
	{
	public:
		Chunk(std::shared_ptr<RenderEngine::Texture2D> pTexture,
			  std::shared_ptr<RenderEngine::ShaderProgram> pShaderProgram);

		void render(glm::vec3& camera_position);
		void update(const uint64_t delta);

		struct s_blocks_polygones { bool blocks_polygones[6]; };
		std::vector<s_blocks_polygones> m_blocks_polygones;

		void setPosition(glm::vec2 position);
		void setBlocksPolygones(std::vector<s_blocks_polygones> blocks_polygones);
		void setBlocksPositions(std::vector<std::shared_ptr<std::pair<std::string, glm::vec3>>> blocks);
	private:
		glm::vec2 m_position;
		std::unique_ptr<Block> block;
		std::vector<std::shared_ptr<std::pair<std::string, glm::vec3>>> m_blocks;
	};
}