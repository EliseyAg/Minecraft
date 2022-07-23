#include "ChunkRenderer.hpp"
#include "../../Resources/ResourceManager.hpp"

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
			chunk->setBlocksPositions(blocks);
			chunk->setBlocksPolygones(blocks_polygones);
			chunk->render(camera_position);
		}
	}

	void ChunkRenderer::generate_world()
	{
		blocks.clear();
		m_blocks.clear();
		blocks_polygones.clear();
		for (int x = -8; x <= 7; x++)
		{
			for (int y = -8; y <= 7; y++)
			{
				m_blocks.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Grass", glm::vec3(x, 0, y))));
				m_blocks.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Dirt", glm::vec3(x, -1, y))));
				m_blocks.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Dirt", glm::vec3(x, -2, y))));
				m_blocks.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Dirt", glm::vec3(x, -3, y))));
				m_blocks.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Coblestone", glm::vec3(x, -4, y))));
				m_blocks.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Coblestone", glm::vec3(x, -5, y))));
				m_blocks.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Coblestone", glm::vec3(x, -6, y))));
				m_blocks.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Coblestone", glm::vec3(x, -7, y))));
			}
		}
		for (int i = 0; i < size(m_blocks); i++)
		{
			bool f[6];
			for (int c = 0; c < 6; c++)
			{
				f[c] = false;
			}
			for (int j = 0; j < size(m_blocks); j++)
			{
				if ((m_blocks[i]->second == m_blocks[j]->second - glm::vec3(0,  1, 0)))
				{
					f[0] = true;
				}
				if ((m_blocks[i]->second == m_blocks[j]->second - glm::vec3(0, -1, 0)))
				{
					f[1] = true;
				}
				if ((m_blocks[i]->second == m_blocks[j]->second - glm::vec3(0, 0,  1)))
				{
					f[2] = true;
				}
				if ((m_blocks[i]->second == m_blocks[j]->second - glm::vec3(0, 0, -1)))
				{
					f[3] = true;
				}
				if ((m_blocks[i]->second == m_blocks[j]->second - glm::vec3( 1, 0, 0)))
				{
					f[4] = true;
				}
				if ((m_blocks[i]->second == m_blocks[j]->second - glm::vec3(-1, 0, 0)))
				{
					f[5] = true;
				}
			}
			if (!(f[0] && f[1] && f[2] && f[3] && f[4] && f[5]))
			{
				blocks.push_back(m_blocks[i]);
				Game::Chunk::s_blocks_polygones _f;
				for (int c = 0; c < 6; c++)
				{
					_f.blocks_polygones[c] = f[c];
				}
				blocks_polygones.push_back(_f);
			}
		}
	}
}