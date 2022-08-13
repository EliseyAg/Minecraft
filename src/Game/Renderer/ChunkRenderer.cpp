#include "ChunkRenderer.hpp"
#include "../../Resources/ResourceManager.hpp"

namespace Renderer
{
	ChunkRenderer::ChunkRenderer(std::shared_ptr<RenderEngine::Texture2D> pTexture,
		std::shared_ptr<RenderEngine::ShaderProgram> pShaderProgram)
	{
		chunk = std::make_unique<Game::Chunk>(std::move(pTexture), std::move(pShaderProgram));
	}

	void ChunkRenderer::render()
	{
		for (int i = 0; i < size(chunks_coords); i++)
		{
			chunk->setPosition(chunks_coords[i]);
			chunk->setBlocksPositions(blocks[i]);
			chunk->setBlocksPolygones(blocks_polygones[i]);
			chunk->render();
		}
	}

	void ChunkRenderer::generate_world()
	{
		blocks.clear();
		m_blocks.clear();
		blocks_polygones.clear();
		std::vector<std::shared_ptr<std::pair<std::string, glm::vec3>>> bl_pos;
		std::vector<Game::Chunk::s_blocks_polygones> bl_pol;
		for (int u = -1; u <= 0; u++)
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
						if (u == 0)
						{
							_u = x * (u + 1);
						}
						else if (u > 0)
						{
							_u = x * u;
						}
						else
						{
							_u = x * u - 1;
						}
						if (v == 0)
						{
							_v = y * (v + 1);
						}
						else if (v > 0)
						{
							_u = x * u;
						}
						else
						{
							_v = y * v -1;
						}
						bl_pos.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Grass",      glm::vec3(_u,  0, _v))));
						bl_pos.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Dirt",	      glm::vec3(_u, -1, _v))));
						bl_pos.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Dirt",	      glm::vec3(_u, -2, _v))));
						bl_pos.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Dirt",	      glm::vec3(_u, -3, _v))));
						bl_pos.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Coblestone", glm::vec3(_u, -4, _v))));
						bl_pos.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Coblestone", glm::vec3(_u, -5, _v))));
						bl_pos.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Coblestone", glm::vec3(_u, -6, _v))));
						bl_pos.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Coblestone", glm::vec3(_u, -7, _v))));
					}
				}
				bl_pos.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Wood", glm::vec3(0, 1, 1))));
				m_blocks.push_back(bl_pos);
			}
		}

		for (int k = 0; k < size(m_blocks); k++)
		{
			bl_pos.clear();
			bl_pol.clear();
			for (int i = 0; i < size(m_blocks[k]); i++)
			{
				Game::Chunk::s_blocks_polygones f = {};
				for (int b = 0; b < size(m_blocks); b++)
				{
					for (int j = 0; j < size(m_blocks[b]); j++)
					{
						if      ((m_blocks[k][i]->second == m_blocks[b][j]->second - glm::vec3( 0,  1,  0)))
						{
							f.blocks_polygones[0] = true;
						}
						else if ((m_blocks[k][i]->second == m_blocks[b][j]->second - glm::vec3( 0, -1,  0)))
						{
							f.blocks_polygones[1] = true;
						}
						else if ((m_blocks[k][i]->second == m_blocks[b][j]->second - glm::vec3( 0,  0,  1)))
						{
							f.blocks_polygones[2] = true;
						}
						else if ((m_blocks[k][i]->second == m_blocks[b][j]->second - glm::vec3( 0,  0, -1)))
						{
							f.blocks_polygones[3] = true;
						}
						else if ((m_blocks[k][i]->second == m_blocks[b][j]->second - glm::vec3( 1,  0,  0)))
						{
							f.blocks_polygones[4] = true;
						}
						else if ((m_blocks[k][i]->second == m_blocks[b][j]->second - glm::vec3(-1,  0,  0)))
						{
							f.blocks_polygones[5] = true;
						}
					}
				}
				if (!(f.blocks_polygones[0] && f.blocks_polygones[1] && f.blocks_polygones[2] && f.blocks_polygones[3] && f.blocks_polygones[4] && f.blocks_polygones[5]))
				{
					bl_pos.push_back(m_blocks[k][i]);
					bl_pol.push_back(f);
				}
			}
			blocks.push_back(bl_pos);
			blocks_polygones.push_back(bl_pol);
		}
	}
}