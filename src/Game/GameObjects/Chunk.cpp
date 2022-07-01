#include "Chunk.hpp"
#include "../../Resources/ResourceManager.hpp"

namespace Game
{
	std::pair<int, float> arr[9];

	Chunk::Chunk(std::shared_ptr<RenderEngine::Texture2D> pTexture,
				 std::shared_ptr<RenderEngine::ShaderProgram> pShaderProgram)
	{
		std::vector<std::string> GrassBlock = {
													 "Grass_Top",
													 "Grass_Left",
													 "Dirt"
		};
		block = std::make_unique<Block>(pTexture, GrassBlock, pShaderProgram);

		blocks = ResourceManager::loadWorld(blocks, "saved_worlds/world1.txt");

		m_position = glm::vec2(0.f);
	}

	void Chunk::render(glm::vec3& camera_position)
	{
		for (int i = 0; i < size(blocks); i++) {
			arr[i] = std::pair<int, float>(i, ((blocks[i]->second.x - camera_position.x) + (blocks[i]->second.y - camera_position.y) * (blocks[i]->second.z - camera_position.z)) / 3);
		}

		for (int i = 0; i < size(blocks); i++) {
			for (int j = 0; j < size(blocks) - 1; j++) {
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

		for (int i = 0; i < size(blocks); i++)
		{
			block->setPosition(blocks[arr[i].first]->second + glm::vec3(m_position.x * 16, 0, m_position.y * 16));
			block->setType(blocks[arr[i].first]->first);
			block->render(camera_position);
		}
	}

	void Chunk::update(const uint64_t delta)
	{
		for (int i = 0; i < size(blocks); i++)
		{
			block->update(delta);
		}
	}

	void Chunk::setPosition(glm::vec2 position)
	{
		m_position = position;
	}
}