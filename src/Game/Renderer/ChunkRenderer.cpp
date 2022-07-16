#include "ChunkRenderer.hpp"

namespace Renderer
{
	std::vector<std::shared_ptr<std::pair<int, float>>> arr;
	ChunkRenderer::ChunkRenderer(std::shared_ptr<RenderEngine::Texture2D> pTexture,
		std::shared_ptr<RenderEngine::ShaderProgram> pShaderProgram)
	{
		chunk = std::make_unique<Game::Chunk>(std::move(pTexture), std::move(pShaderProgram));
		chunks_coords.push_back(glm::vec2(0.f));
		//chunks_coords.push_back(glm::vec2(0.f, 1.f));
		//chunks_coords.push_back(glm::vec2(0.f, -1.f));
	}

	void ChunkRenderer::render(glm::vec3& camera_position)
	{
		arr.clear();
		for (int i = 0; i < size(chunks_coords); i++) {
			arr.push_back(std::make_shared<std::pair<int, float>>(i, ((chunks_coords[i].x - camera_position.x) + (chunks_coords[i].y - camera_position.y)) / 2));
		}

		for (int i = 0; i < size(chunks_coords); i++) {
			for (int j = 0; j < size(chunks_coords) - 1; j++) {
				if (arr[j]->second < arr[j + 1]->second && arr[j]->second > 0) {
					std::shared_ptr<std::pair<int, float>> mem = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = mem;
				}
				if (arr[j]->second > arr[j + 1]->second && arr[j]->second < 0) {
					std::shared_ptr<std::pair<int, float>> mem = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = mem;
				}
			}
		}

		for (int i = 0; i < size(chunks_coords); i++)
		{
			chunk->setPosition(chunks_coords[arr[i]->first]);
			chunk->render(camera_position);
		}
	}
}