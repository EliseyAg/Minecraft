#include "Chunk.hpp"

namespace Game
{
	std::pair<int, float> arr[9];

	Chunk::Chunk(std::shared_ptr<RenderEngine::Texture2D> pTexture,
				 std::shared_ptr<RenderEngine::ShaderProgram> pShaderProgram)
	{
		std::vector<std::string> subTexturesNames = {
													 "Grass_Top",
													 "Grass_Left",
													 "Dirt"
		};
		block = std::make_unique<Block>(pTexture, subTexturesNames, pShaderProgram);
		blocks.push_back(std::make_pair("Grass", glm::vec3(0.f)));
		blocks.push_back(std::make_pair("Grass", glm::vec3(0.f, 0.f, -1.f)));
		blocks.push_back(std::make_pair("Grass", glm::vec3(-1.f, 0.f, 0.f)));
		blocks.push_back(std::make_pair("Grass", glm::vec3(0.f, 0.f, 1.f)));
		blocks.push_back(std::make_pair("Grass", glm::vec3(1.f, 0.f, 0.f)));
		blocks.push_back(std::make_pair("Grass", glm::vec3(-1.f, 0.f, -1.f)));
		blocks.push_back(std::make_pair("Grass", glm::vec3(1.f, 0.f, -1.f)));
		blocks.push_back(std::make_pair("Grass", glm::vec3(-1.f, 0.f, 1.f)));
		blocks.push_back(std::make_pair("Grass", glm::vec3(1.f, 0.f, 1.f)));
	}

	void Chunk::render(glm::vec3& camera_position)
	{
		for (int i = 0; i < 9; i++) {
			arr[i] = std::pair<int, float>(i, ((blocks[i].second.x - camera_position.x) * (blocks[i].second.y - camera_position.y) * (blocks[i].second.z - camera_position.z)) / 3);
		}

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 8; j++) {
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

		for (int i = 0; i < 9; i++)
		{
			block->setPosition(blocks[arr[i].first].second);
			block->render(camera_position);
		}
	}
}