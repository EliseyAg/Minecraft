#include "ChunkRenderer.hpp"
#include "../../Resources/ResourceManager.hpp"

#include <glm/gtc/noise.hpp>
#include <ctime>
#include <cmath>
#include <thread>

namespace Renderer
{
	std::vector<std::vector<Game::Chunk::s_blocks_polygones>> ChunkRenderer::m_blocks_polygones = {};
	std::vector<glm::vec2> ChunkRenderer::chunks_coords = {};
	std::unique_ptr<Game::Chunk> ChunkRenderer::chunk = {};
	std::vector<std::vector<std::shared_ptr<std::pair<std::string, glm::vec3>>>> ChunkRenderer::m_blocks = {};
	std::vector<std::vector<std::shared_ptr<std::pair<std::string, glm::vec3>>>> ChunkRenderer::blocks = {};

	std::shared_ptr<RenderEngine::Texture2D> ChunkRenderer::m_pTexture = nullptr;
	std::shared_ptr<RenderEngine::ShaderProgram> ChunkRenderer::m_pShaderProgram = nullptr;

	static std::vector<std::shared_ptr<std::pair<std::string, glm::vec3>>> bl_pos;
	static std::vector<Game::Chunk::s_blocks_polygones> bl_pol;

	void ChunkRenderer::setTextureAtlas(std::shared_ptr<RenderEngine::Texture2D> pTexture)
	{
		m_pTexture = pTexture;
	}

	void ChunkRenderer::setShaderProgram(std::shared_ptr<RenderEngine::ShaderProgram> pShaderProgram)
	{
		m_pShaderProgram = pShaderProgram;
	}


	void ChunkRenderer::update_blocks(std::shared_ptr<std::pair<std::string, glm::vec3>> block)
	{
		Game::Chunk::s_blocks_polygones f = {};
		for (int b = 0; b < size(m_blocks); b++)
		{
			for (int c = 0; c < size(m_blocks[b]); c++)
			{
				if (m_blocks[b][c]->first != "Leaves")
				{
					if ((block->second == m_blocks[b][c]->second - glm::vec3(0, 1, 0)))
					{
						f.m_blocks_polygones[0] = true;
					}
					else if ((block->second == m_blocks[b][c]->second - glm::vec3(0, -1, 0)))
					{
						f.m_blocks_polygones[1] = true;
					}
					else if ((block->second == m_blocks[b][c]->second - glm::vec3(0, 0, 1)))
					{
						f.m_blocks_polygones[2] = true;
					}
					else if ((block->second == m_blocks[b][c]->second - glm::vec3(0, 0, -1)))
					{
						f.m_blocks_polygones[3] = true;
					}
					else if ((block->second == m_blocks[b][c]->second - glm::vec3(1, 0, 0)))
					{
						f.m_blocks_polygones[4] = true;
					}
					else if ((block->second == m_blocks[b][c]->second - glm::vec3(-1, 0, 0)))
					{
						f.m_blocks_polygones[5] = true;
					}
				}
			}
		}
		if (!(f.m_blocks_polygones[0] && f.m_blocks_polygones[1] && f.m_blocks_polygones[2] && f.m_blocks_polygones[3] && f.m_blocks_polygones[4] && f.m_blocks_polygones[5]))
		{
			bl_pos.push_back(block);
			bl_pol.push_back(f);
		}
	}

	void ChunkRenderer::deleteBlock(const glm::vec3& coords)
	{
		for (int i = 0; i < size(chunks_coords); i++)
		{
			int c = -1;
			for (int j = 0; j < size(m_blocks[i]); j++)
			{
				for (int b = 0; b < size(blocks[i]); b++)
				{
					if (blocks[i][b] == m_blocks[i][j])
					{
						c = b;
						break;
					}
				}
				if (m_blocks[i][j]->second == coords && c != -1)
				{
					m_blocks[i].erase(m_blocks[i].begin() + j);
					blocks[i].erase(blocks[i].begin() + c);
					m_blocks_polygones[i].erase(m_blocks_polygones[i].begin() + c);
					break;
				}
			}
		}
		
		for (int i = 0; i < size(chunks_coords); i++)
		{
			for (int j = 0; j < size(m_blocks[i]); j++)
			{
				int c = -1;
				bl_pos.clear();
				bl_pol.clear();
				for (int b = 0; b < size(blocks[i]); b++)
				{
					if (blocks[i][b] == m_blocks[i][j])
					{
						c = b;
						break;
					}
				}
				if      ((coords == m_blocks[i][j]->second - glm::vec3(0, 1, 0)))
				{
					update_blocks(m_blocks[i][j]);
					if (c != -1)
					{
						blocks[i][c] = bl_pos[0];
						m_blocks_polygones[i][c] = bl_pol[0];
					}
					else
					{
						blocks[i].push_back(bl_pos[0]);
						m_blocks_polygones[i].push_back(bl_pol[0]);
					}
				}
				else if ((coords == m_blocks[i][j]->second - glm::vec3(0, -1, 0)))
				{
					update_blocks(m_blocks[i][j]);
					if (c != -1)
					{
						blocks[i][c] = bl_pos[0];
						m_blocks_polygones[i][c] = bl_pol[0];
					}
					else
					{
						blocks[i].push_back(bl_pos[0]);
						m_blocks_polygones[i].push_back(bl_pol[0]);
					}
				}
				else if ((coords == m_blocks[i][j]->second - glm::vec3(0, 0, 1)))
				{
					update_blocks(m_blocks[i][j]);
					if (c != -1)
					{
						blocks[i][c] = bl_pos[0];
						m_blocks_polygones[i][c] = bl_pol[0];
					}
					else
					{
						blocks[i].push_back(bl_pos[0]);
						m_blocks_polygones[i].push_back(bl_pol[0]);
					}
				}
				else if ((coords == m_blocks[i][j]->second - glm::vec3(0, 0, -1)))
				{
					update_blocks(m_blocks[i][j]);
					if (c != -1)
					{
						blocks[i][c] = bl_pos[0];
						m_blocks_polygones[i][c] = bl_pol[0];
					}
					else
					{
						blocks[i].push_back(bl_pos[0]);
						m_blocks_polygones[i].push_back(bl_pol[0]);
					}
				}
				else if ((coords == m_blocks[i][j]->second - glm::vec3(1, 0, 0)))
				{
					update_blocks(m_blocks[i][j]);
					if (c != -1)
					{
						blocks[i][c] = bl_pos[0];
						m_blocks_polygones[i][c] = bl_pol[0];
					}
					else
					{
						blocks[i].push_back(bl_pos[0]);
						m_blocks_polygones[i].push_back(bl_pol[0]);
					}
				}
				else if ((coords == m_blocks[i][j]->second - glm::vec3(-1, 0, 0)))
				{
					update_blocks(m_blocks[i][j]);
					if (c != -1)
					{
						blocks[i][c] = bl_pos[0];
						m_blocks_polygones[i][c] = bl_pol[0];
					}
					else
					{
						blocks[i].push_back(bl_pos[0]);
						m_blocks_polygones[i].push_back(bl_pol[0]);
					}
				}
			}
		}
	}

	void ChunkRenderer::placeBlock(const glm::vec3& coords, const std::string& type)
	{
		for (int i = 0; i < size(chunks_coords); i++)
		{
			if (chunks_coords[i].x * 16 - 8 <= coords.x && chunks_coords[i].x * 16 + 7 >= coords.x &&
				chunks_coords[i].y * 16 - 8 <= coords.z && chunks_coords[i].y * 16 + 7 >= coords.z)
			{
				bl_pos.clear();
				bl_pol.clear();
				update_blocks(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair(type, coords)));
				m_blocks[i].push_back(bl_pos[0]);
				blocks[i].push_back(bl_pos[0]);
				m_blocks_polygones[i].push_back(bl_pol[0]);
				break;
			}
		}
		for (int i = 0; i < size(m_blocks); i++)
		{
			for (int j = 0; j < size(m_blocks[i]); j++)
			{
				Game::Chunk::s_blocks_polygones f = {};
				f.m_blocks_polygones[0] = true;
				f.m_blocks_polygones[1] = true;
				f.m_blocks_polygones[2] = true;
				f.m_blocks_polygones[3] = true;
				f.m_blocks_polygones[4] = true;
				f.m_blocks_polygones[5] = true;
				int c = -1;
				bl_pos.clear();
				bl_pol.clear();
				for (int b = 0; b < size(blocks[i]); b++)
				{
					if (blocks[i][b] == m_blocks[i][j])
					{
						c = b;
						break;
					}
				}
				if (c != -1)
				{
					if ((coords == m_blocks[i][j]->second - glm::vec3(0, 1, 0)))
					{
						update_blocks(m_blocks[i][j]);
						if (bl_pol[0].m_blocks_polygones == f.m_blocks_polygones)
						{
							blocks[i].erase(blocks[i].begin() + c);
							m_blocks_polygones[i].erase(m_blocks_polygones[i].begin() + c);
						}
						else
						{
							blocks[i][c] = bl_pos[0];
							m_blocks_polygones[i][c] = bl_pol[0];
						}
						continue;
					}
					else if ((coords == m_blocks[i][j]->second - glm::vec3(0, -1, 0)))
					{
						update_blocks(m_blocks[i][j]);
						if (bl_pol[0].m_blocks_polygones == f.m_blocks_polygones)
						{
							blocks[i].erase(blocks[i].begin() + c);
							m_blocks_polygones[i].erase(m_blocks_polygones[i].begin() + c);
						}
						else
						{
							blocks[i][c] = bl_pos[0];
							m_blocks_polygones[i][c] = bl_pol[0];
						}
						continue;
					}
					else if ((coords == m_blocks[i][j]->second - glm::vec3(0, 0, 1)))
					{
						update_blocks(m_blocks[i][j]);
						if (bl_pol[0].m_blocks_polygones == f.m_blocks_polygones)
						{
							blocks[i].erase(blocks[i].begin() + c);
							m_blocks_polygones[i].erase(m_blocks_polygones[i].begin() + c);
						}
						else
						{
							blocks[i][c] = bl_pos[0];
							m_blocks_polygones[i][c] = bl_pol[0];
						}
						continue;
					}
					else if ((coords == m_blocks[i][j]->second - glm::vec3(0, 0, -1)))
					{
						update_blocks(m_blocks[i][j]);
						if (bl_pol[0].m_blocks_polygones == f.m_blocks_polygones)
						{
							blocks[i].erase(blocks[i].begin() + c);
							m_blocks_polygones[i].erase(m_blocks_polygones[i].begin() + c);
						}
						else
						{
							blocks[i][c] = bl_pos[0];
							m_blocks_polygones[i][c] = bl_pol[0];
						}
						continue;
					}
					else if ((coords == m_blocks[i][j]->second - glm::vec3(1, 0, 0)))
					{
						update_blocks(m_blocks[i][j]);
						if (bl_pol[0].m_blocks_polygones == f.m_blocks_polygones)
						{
							blocks[i].erase(blocks[i].begin() + c);
							m_blocks_polygones[i].erase(m_blocks_polygones[i].begin() + c);
						}
						else
						{
							blocks[i][c] = bl_pos[0];
							m_blocks_polygones[i][c] = bl_pol[0];
						}
						continue;
					}
					else if ((coords == m_blocks[i][j]->second - glm::vec3(-1, 0, 0)))
					{
						update_blocks(m_blocks[i][j]);
						if (bl_pol[0].m_blocks_polygones == f.m_blocks_polygones)
						{
							blocks[i].erase(blocks[i].begin() + c);
							m_blocks_polygones[i].erase(m_blocks_polygones[i].begin() + c);
						}
						else
						{
							blocks[i][c] = bl_pos[0];
							m_blocks_polygones[i][c] = bl_pol[0];
						}
						continue;
					}
				}
			}
		}
	}

	double angle(const glm::vec2& a, const glm::vec2& b)
	{
		double sc_mult = a.x * b.x + a.y * b.y;
		double len_a = sqrt((a.x) * (a.x) + (a.y) * (a.y));
		double len_b = sqrt((b.x) * (b.x) + (b.y) * (b.y));
		return glm::degrees(glm::acos(sc_mult / (len_a * len_b)));
	}

	void ChunkRenderer::render(const glm::vec3& camera_position, const glm::vec3& camera_rotation)
	{
		glm::vec2 pos = glm::vec2(0.f);
		float yaw = glm::radians(camera_rotation.y + 90.f);
		pos.x += glm::cos(yaw) * 16;
		pos.y -= glm::sin(yaw) * 16;
		for (int i = 0; i < size(chunks_coords); i++)
		{
			if (chunks_coords[i].x * 16 - 8 <= camera_position.x && chunks_coords[i].x * 16 + 7 >= camera_position.x &&
				chunks_coords[i].y * 16 - 8 <= camera_position.z && chunks_coords[i].y * 16 + 7 >= camera_position.z)
			{
				chunk->setPosition(chunks_coords[i]);
				chunk->setBlocksPositions(blocks[i]);
				chunk->setBlocksPolygones(m_blocks_polygones[i]);
				chunk->render(camera_position);
				continue;
			}
			else
			{
				if ((chunks_coords[i].x * 16 - 8) - camera_position.x <= pos.x && (chunks_coords[i].x * 16 + 7) - camera_position.x >= pos.x &&
					(chunks_coords[i].y * 16 - 8) - camera_position.z <= pos.y && (chunks_coords[i].y * 16 + 7) - camera_position.z >= pos.y)
				{
					chunk->setPosition(chunks_coords[i]);
					chunk->setBlocksPositions(blocks[i]);
					chunk->setBlocksPolygones(m_blocks_polygones[i]);
					chunk->render(camera_position);
					continue;
				}

				if (angle(glm::vec2(chunks_coords[i].x * 16 - camera_position.x, chunks_coords[i].y * 16 - camera_position.z), pos) <= 100)
				{
					if (chunks_coords[i].x * 16 - camera_position.x < 1 * 16 && chunks_coords[i].y * 16 - camera_position.z < 1 * 16)
					{
						chunk->setPosition(chunks_coords[i]);
						chunk->setBlocksPositions(blocks[i]);
						chunk->setBlocksPolygones(m_blocks_polygones[i]);
						chunk->render(camera_position);
						continue;
					}
				}
			}
		}
	}

	void ChunkRenderer::generate_world()
	{
		blocks.clear();
		m_blocks.clear();
		m_blocks_polygones.clear();
		chunk = std::make_unique<Game::Chunk>(std::move(m_pTexture), std::move(m_pShaderProgram));
		srand(time(0));
		float SEED = rand();
		for (int u = -2; u <= 1; u++)
		{
			for (int v = -2; v <= 1; v++)
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
							_u = x + u * 16;
						}
						else
						{
							_u = x + u * 16;
						}
						if (v >= 0)
						{
							_v = y + v * 16;
						}
						else
						{
							_v = y + v * 16;
						}
						float height = (int)(-glm::perlin(glm::vec3(_u * 0.05f, _v * 0.05f, SEED)) * 20) + 5;
						bl_pos.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Grass",      glm::vec3(_u, height, _v))));
						bl_pos.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Dirt",	      glm::vec3(_u, height - 1, _v))));
						bl_pos.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Dirt",	      glm::vec3(_u, height - 2, _v))));
						bl_pos.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Dirt",	      glm::vec3(_u, height - 3, _v))));
						for (int i = height - 4; i >= -10; i--)
							bl_pos.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Coblestone", glm::vec3(_u, i, _v))));
					}
				}
				m_blocks.push_back(bl_pos);
			}
		}
		//int height = (int)(-glm::perlin(glm::vec3(1 * 0.05f, 0 * 0.05f, SEED)) * 20) + 5;
		//m_blocks[3].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Wood",   glm::vec3( 1,  height + 1,  0))));
		//m_blocks[3].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Wood",   glm::vec3( 1,  height + 2,  0))));
		//m_blocks[3].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Wood",   glm::vec3( 1,  height + 3,  0))));
		//m_blocks[3].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Wood",   glm::vec3( 1,  height + 4,  0))));
		//m_blocks[3].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Wood",   glm::vec3( 1,  height + 5,  0))));
		//m_blocks[3].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 1,  height + 6,  0))));
		//m_blocks[3].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 2,  height + 6,  0))));
		//m_blocks[3].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 0,  height + 6,  0))));
		//m_blocks[3].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 1,  height + 6,  1))));
		//m_blocks[3].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 1,  height + 6, -1))));
		//m_blocks[3].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 2,  height + 5,  0))));
		//m_blocks[3].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 2,  height + 5, -1))));
		//m_blocks[3].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 0,  height + 5,  0))));
		//m_blocks[3].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 0,  height + 5,  1))));
		//m_blocks[3].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 1,  height + 5,  1))));
		//m_blocks[3].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 2,  height + 5,  1))));
		//m_blocks[3].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 1,  height + 5, -1))));
		//m_blocks[3].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 0,  height + 5, -1))));
		//m_blocks[3].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 2,  height + 4,  0))));
		//m_blocks[3].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 2,  height + 4, -1))));
		//m_blocks[3].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 0,  height + 4,  0))));
		//m_blocks[3].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 0,  height + 4,  1))));
		//m_blocks[3].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 1,  height + 4,  1))));
		//m_blocks[3].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 2,  height + 4,  1))));
		//m_blocks[3].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 1,  height + 4, -1))));
		//m_blocks[3].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 0,  height + 4, -1))));

		for (int k = 0; k < size(m_blocks); k++)
		{
			bl_pos.clear();
			bl_pol.clear();
			for (int i = 0; i < size(m_blocks[k]); i++)
			{
				update_blocks(m_blocks[k][i]);
			}
			blocks.push_back(bl_pos);
			m_blocks_polygones.push_back(bl_pol);
		}
	}

	bool ChunkRenderer::getObjectsInArea(const glm::vec3& BottomLeftFront, const glm::vec3& TopRightFront, const glm::vec3& TopLeftBack)
	{
		bool is_colide = false;
		for (int i = 0; i < size(chunks_coords); i++)
		{
			if (chunks_coords[i].x * 16 - 8 <= BottomLeftFront.x && chunks_coords[i].x * 16 + 7 >= BottomLeftFront.x &&
				chunks_coords[i].y * 16 - 8 <= TopRightFront.z && chunks_coords[i].y * 16 + 7 >= TopRightFront.z)
			{
				chunk->setBlocksPositions(m_blocks[i]);
				is_colide = chunk->getObjectsInArea(BottomLeftFront, TopRightFront, TopLeftBack);
			}
		}
		return is_colide;
	}
}