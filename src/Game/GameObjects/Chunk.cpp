#include "Chunk.hpp"

namespace Game
{
	Chunk::Chunk(std::shared_ptr<RenderEngine::Texture2D> pTexture,
				 std::shared_ptr<RenderEngine::ShaderProgram> pShaderProgram)
	{
		std::vector<std::string> GrassBlock = {
													 "Grass_Top",
													 "Grass_Left",
													 "Dirt"
		};
		block = std::make_unique<Block>(pTexture, GrassBlock, pShaderProgram);
		m_position = glm::vec2(0.f);
	}

	void Chunk::render()
	{
		for (int i = 0; i < size(m_blocks); i++)
		{
			block->setPosition(m_blocks[i]->second + glm::vec3(m_position.x * 16, 0, m_position.y * 16));
			block->setType(m_blocks[i]->first);
			block->setPolygones(m_blocks_polygones[i].blocks_polygones);
			block->render();
		}
	}

	void Chunk::update(const uint64_t delta)
	{
		for (int i = 0; i < size(m_blocks); i++)
		{
			block->update(delta);
		}
	}

	void Chunk::setPosition(glm::vec2 position)
	{
		m_position = position;
	}

	void Chunk::setBlocksPositions(std::vector<std::shared_ptr<std::pair<std::string, glm::vec3>>> blocks)
	{
		m_blocks = blocks;
	}

	void Chunk::setBlocksPolygones(std::vector<s_blocks_polygones> blocks_polygones)
	{
		m_blocks_polygones = blocks_polygones;
	}
}