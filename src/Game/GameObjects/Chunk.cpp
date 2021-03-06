#include "Chunk.hpp"

namespace Game
{
	std::vector<std::pair<int, float>> arr;

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

	void Chunk::render(glm::vec3& camera_position)
	{
		arr.clear();
		for (int i = 0; i < size(m_blocks); i++) {
			arr.push_back(std::pair<int, float>(i, ((m_blocks[i]->second.x - camera_position.x) + (m_blocks[i]->second.y - camera_position.y) * (m_blocks[i]->second.z - camera_position.z)) / 3));
		}

		for (int i = 0; i < size(m_blocks); i++) {
			for (int j = 0; j < size(m_blocks) - 1; j++) {
				if (arr[j].second < arr[j + 1].second && arr[j].second > 0) {
					std::pair<int, float> mem = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = mem;
				}
				if (arr[j].second > arr[j + 1].second && arr[j].second < 0) {
					std::pair<int, float> mem = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = mem;
				}
			}
		}

		for (int i = 0; i < size(m_blocks); i++)
		{
			block->setPosition(m_blocks[arr[i].first]->second + glm::vec3(m_position.x * 16, 0, m_position.y * 16));
			block->setType(m_blocks[arr[i].first]->first);
			block->setPolygones(m_blocks_polygones[arr[i].first].blocks_polygones);
			block->render(camera_position);
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