#include "ChunkRenderer.hpp"
#include "../../Resources/ResourceManager.hpp"

namespace Renderer
{
	std::vector<std::shared_ptr<std::pair<int, float>>> arr;
	ChunkRenderer::ChunkRenderer(std::shared_ptr<RenderEngine::Texture2D> pTexture,
		std::shared_ptr<RenderEngine::ShaderProgram> pShaderProgram)
	{
		chunk = std::make_unique<Game::Chunk>(std::move(pTexture), std::move(pShaderProgram));
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
			chunk->setBlocksPositions(blocks[i]);
			chunk->setBlocksPolygones(blocks_polygones[i]);
			chunk->render(camera_position);
		}
	}

	void ChunkRenderer::generate_world()
	{
		blocks.clear();
		m_blocks.clear();
		blocks_polygones.clear();
		std::vector<std::shared_ptr<std::pair<std::string, glm::vec3>>> bl_pos;
		std::vector<Game::Chunk::s_blocks_polygones> bl_pol;
		for (int u = 0; u <= 0; u++)
		{
			for (int v = -1; v <= 0; v++)
			{
				chunks_coords.push_back(glm::vec2(u, v));
				bl_pos.clear();
				for (int x = -8; x <= 7; x++)
				{
					for (int y = -8; y <= 7; y++)
					{
						int _u, _v = 0;
						if (u >= 0)
						{
							_u = x * (u + 1);
						}
						else
						{
							_u = x * u;
						}
						if (v >= 0)
						{
							_v = y * (v + 1);
						}
						else
						{
							_v = y * v;
						}
						bl_pos.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Grass", glm::vec3(_u,  0, _v))));
						bl_pos.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Dirt",	glm::vec3(_u, -1, _v))));
						bl_pos.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Dirt",	glm::vec3(_u, -2, _v))));
						bl_pos.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Dirt",	glm::vec3(_u, -3, _v))));
						bl_pos.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Coblestone", glm::vec3(_u, -4, _v))));
						bl_pos.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Coblestone", glm::vec3(_u, -5, _v))));
						bl_pos.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Coblestone", glm::vec3(_u, -6, _v))));
						bl_pos.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Coblestone", glm::vec3(_u, -7, _v))));
					}
				}
				m_blocks.push_back(bl_pos);
			}
		}
		for (int k = 0; k < size(m_blocks); k++)
		{
			bl_pos.clear();
			bl_pol.clear();
			for (int i = 0; i < size(m_blocks[k]); i++)
			{
				bool f[6];
				for (int c = 0; c < 6; c++)
				{
					f[c] = false;
				}
				for (int b = 0; b < size(m_blocks); b++)
				{
					for (int j = 0; j < size(m_blocks[k]); j++)
					{
						if ((m_blocks[k][i]->second == m_blocks[b][j]->second - glm::vec3(0, 1, 0)))
						{
							f[0] = true;
						}
						if ((m_blocks[k][i]->second == m_blocks[b][j]->second - glm::vec3(0, -1, 0)))
						{
							f[1] = true;
						}
						if ((m_blocks[k][i]->second == m_blocks[b][j]->second - glm::vec3(0, 0, 1)))
						{
							f[2] = true;
						}
						if ((m_blocks[k][i]->second == m_blocks[b][j]->second - glm::vec3(0, 0, -1)))
						{
							f[3] = true;
						}
						if ((m_blocks[k][i]->second == m_blocks[b][j]->second - glm::vec3(1, 0, 0)))
						{
							f[4] = true;
						}
						if ((m_blocks[k][i]->second == m_blocks[b][j]->second - glm::vec3(-1, 0, 0)))
						{
							f[5] = true;
						}
					}
					if (!(f[0] && f[1] && f[2] && f[3] && f[4] && f[5]))
					{
						bl_pos.push_back(m_blocks[k][i]);
						Game::Chunk::s_blocks_polygones _f;
						for (int c = 0; c < 6; c++)
						{
							_f.blocks_polygones[c] = f[c];
						}
						bl_pol.push_back(_f);
					}
				}
			}
			blocks.push_back(bl_pos);
			blocks_polygones.push_back(bl_pol);
		}
	}
}