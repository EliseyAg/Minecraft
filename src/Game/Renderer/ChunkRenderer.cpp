#include "ChunkRenderer.hpp"
#include "../../Resources/ResourceManager.hpp"

#include <glm/gtc/noise.hpp>
#include <ctime>
#include <cmath>
#include <thread>
#include <iostream>

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 16
#define CHUNK_HEIGHT 64

namespace Renderer
{
	std::vector<std::vector<Game::Chunk::s_blocks_polygones>> ChunkRenderer::m_blocks_polygones = {};
	std::vector<glm::vec2> ChunkRenderer::chunks_coords = {};
	std::unique_ptr<Game::Chunk> ChunkRenderer::chunk = {};
	std::vector<std::vector<std::string>> ChunkRenderer::m_blocks = {};

	unsigned long long int ChunkRenderer::SEED = 0;

	std::shared_ptr<RenderEngine::Texture2D> ChunkRenderer::m_pTexture = nullptr;

	static std::vector<std::string> bl_pos;
	static std::vector<Game::Chunk::s_blocks_polygones> bl_pol;

	void ChunkRenderer::generate_seed()
	{
		srand(time(0));
		unsigned long long int max = pow(2, 64);
		SEED = rand() % max;
	}

	void ChunkRenderer::setTextureAtlas(std::shared_ptr<RenderEngine::Texture2D> pTexture)
	{
		m_pTexture = pTexture;
		chunk = std::make_unique<Game::Chunk>(std::move(m_pTexture));
	}

	void ChunkRenderer::update_blocks(std::pair<std::string, glm::vec3> block)
	{
		Game::Chunk::s_blocks_polygones f = {};
		f.m_blocks_polygones[0] = false;
		f.m_blocks_polygones[1] = false;
		f.m_blocks_polygones[2] = false;
		f.m_blocks_polygones[3] = false;
		f.m_blocks_polygones[4] = false;
		f.m_blocks_polygones[5] = false;
		for (int b = 0; b < size(m_blocks); b++)
		{
			int c = 0;
			for (int x = 0; x < CHUNK_SIZE_X; x++)
			{
				for (int z = 0; z < CHUNK_SIZE_Y; z++)
				{
					for (int y = 0; y < CHUNK_HEIGHT; y++)
					{
						if (m_blocks[b][c] != "Leaves" && m_blocks[b][c] != "Air")
						{
							if ((block.second == glm::vec3(x, y, z) - glm::vec3(0, 1, 0)))
							{
								f.m_blocks_polygones[0] = true;
							}
							else if ((block.second == glm::vec3(x, y, z) - glm::vec3(0, -1, 0)))
							{
								f.m_blocks_polygones[1] = true;
							}
							else if ((block.second == glm::vec3(x, y, z) - glm::vec3(0, 0, 1)))
							{
								f.m_blocks_polygones[2] = true;
							}
							else if ((block.second == glm::vec3(x, y, z) - glm::vec3(0, 0, -1)))
							{
								f.m_blocks_polygones[3] = true;
							}
							else if ((block.second == glm::vec3(x, y, z) - glm::vec3(1, 0, 0)))
							{
								f.m_blocks_polygones[4] = true;
							}
							else if ((block.second == glm::vec3(x, y, z) - glm::vec3(-1, 0, 0)))
							{
								f.m_blocks_polygones[5] = true;
							}
						}
						c++;
					}
				}
			}
		}
		bl_pol.push_back(f);
	}

	/*void ChunkRenderer::deleteBlock(const glm::vec3& coords)
	{
		for (int i = 0; i < size(chunks_coords); i++)
		{
			for (int j = 0; j < size(m_blocks[i]); j++)
			{
				if (m_blocks[i][j]->second == coords)
				{
					m_blocks[i][j]->first = "Air";
					m_blocks[i][j]->first = "Air";
					update_blocks(m_blocks[i][j]);
					m_blocks_polygones[i][j] = bl_pol[0];
					break;
				}
			}
		}
		
		for (int i = 0; i < size(chunks_coords); i++)
		{
			for (int j = 0; j < size(m_blocks[i]); j++)
			{
				bl_pos.clear();
				bl_pol.clear();
				if      ((coords == m_blocks[i][j]->second - glm::vec3(0, 1, 0)))
				{
					update_blocks(m_blocks[i][j]);
					m_blocks[i][j] = bl_pos[0];
					m_blocks_polygones[i][j] = bl_pol[0];
				}
				else if ((coords == m_blocks[i][j]->second - glm::vec3(0, -1, 0)))
				{
					update_blocks(m_blocks[i][j]);
					update_blocks(m_blocks[i][j]);
					m_blocks[i][j] = bl_pos[0];
					m_blocks_polygones[i][j] = bl_pol[0];
				}
				else if ((coords == m_blocks[i][j]->second - glm::vec3(0, 0, 1)))
				{
					update_blocks(m_blocks[i][j]);
					update_blocks(m_blocks[i][j]);
					m_blocks[i][j] = bl_pos[0];
					m_blocks_polygones[i][j] = bl_pol[0];
				}
				else if ((coords == m_blocks[i][j]->second - glm::vec3(0, 0, -1)))
				{
					update_blocks(m_blocks[i][j]);
					m_blocks[i][j] = bl_pos[0];
					m_blocks_polygones[i][j] = bl_pol[0];
				}
				else if ((coords == m_blocks[i][j]->second - glm::vec3(1, 0, 0)))
				{
					update_blocks(m_blocks[i][j]);
					m_blocks[i][j] = bl_pos[0];
					m_blocks_polygones[i][j] = bl_pol[0];
				}
				else if ((coords == m_blocks[i][j]->second - glm::vec3(-1, 0, 0)))
				{
					update_blocks(m_blocks[i][j]);
					m_blocks[i][j] = bl_pos[0];
					m_blocks_polygones[i][j] = bl_pol[0];
				}
			}
		}
	}

	void ChunkRenderer::placeBlock(const glm::vec3& coords, const std::string& type)
	{
		for (int i = 0; i < size(chunks_coords); i++)
		{
			if (chunks_coords[i].x * CHUNK_SIZE_X <= coords.x && chunks_coords[i].x * CHUNK_SIZE_X + CHUNK_SIZE_X - 1 >= coords.x &&
				chunks_coords[i].y * CHUNK_SIZE_Y <= coords.z && chunks_coords[i].y * CHUNK_SIZE_Y + CHUNK_SIZE_Y - 1 >= coords.z)
			{
				for (int j = 0; j < size(m_blocks[i]); j++)
				{
					int lx = coords.x - chunks_coords[i].x * CHUNK_SIZE_X - 1;
					int ly = coords.y + CHUNK_HEIGHT / 2;
					int lz = coords.z - chunks_coords[i].y * CHUNK_SIZE_Y - 1;
					if (m_blocks[i][j]->second == coords && m_blocks[i][j]->first == "Air")
					{
						if ((lz * CHUNK_SIZE_Y + lx) * CHUNK_HEIGHT + ly == j)
						{
							std::cout << "URA!!";
						}
						m_blocks[i][j]->first = type;
						m_blocks[i][j]->first = type;
						update_blocks(m_blocks[i][j]);
						m_blocks_polygones[i][j] = bl_pol[0];
						break;
					}
				}
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
				bl_pos.clear();
				bl_pol.clear();
				if ((coords == m_blocks[i][j]->second - glm::vec3(0, 1, 0)))
				{
					update_blocks(m_blocks[i][j]);
					m_blocks[i][j] = bl_pos[0];
					m_blocks_polygones[i][j] = bl_pol[0];
					continue;
				}
				else if ((coords == m_blocks[i][j]->second - glm::vec3(0, -1, 0)))
				{
					update_blocks(m_blocks[i][j]);
					m_blocks[i][j] = bl_pos[0];
					m_blocks_polygones[i][j] = bl_pol[0];
					continue;
				}
				else if ((coords == m_blocks[i][j]->second - glm::vec3(0, 0, 1)))
				{
					update_blocks(m_blocks[i][j]);
					m_blocks[i][j] = bl_pos[0];
					m_blocks_polygones[i][j] = bl_pol[0];
					continue;
				}
				else if ((coords == m_blocks[i][j]->second - glm::vec3(0, 0, -1)))
				{
					update_blocks(m_blocks[i][j]);
					m_blocks[i][j] = bl_pos[0];
					m_blocks_polygones[i][j] = bl_pol[0];
					continue;
				}
				else if ((coords == m_blocks[i][j]->second - glm::vec3(1, 0, 0)))
				{
					update_blocks(m_blocks[i][j]);
					m_blocks[i][j] = bl_pos[0];
					m_blocks_polygones[i][j] = bl_pol[0];
					continue;
				}
				else if ((coords == m_blocks[i][j]->second - glm::vec3(-1, 0, 0)))
				{
					update_blocks(m_blocks[i][j]);
					m_blocks[i][j] = bl_pos[0];
					m_blocks_polygones[i][j] = bl_pol[0];
					continue;
				}
			}
		}
	}*/

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
		pos.x += glm::cos(yaw) * CHUNK_SIZE_X;
		pos.y -= glm::sin(yaw) * CHUNK_SIZE_Y;
		for (int i = 0; i < size(chunks_coords); i++)
		{
			chunk->setPosition(chunks_coords[i]);
			chunk->setBlocksPositions(m_blocks[i]);
			chunk->setBlocksPolygones(m_blocks_polygones[i]);
			chunk->render(camera_position);
		}
	}

	void ChunkRenderer::unload_world()
	{
		m_blocks.clear();
		chunks_coords.clear();
		m_blocks.clear();
		m_blocks_polygones.clear();
		bl_pos.clear();
		bl_pol.clear();
	}

	void ChunkRenderer::generate_world(const int u, const int v)
	{
		chunks_coords.push_back(glm::vec2(u, v));
		bl_pos.clear();

		for (int x = 0; x <= 15; x++)
		{
			for (int y = 0; y <= 15; y++)
			{
				int _u = x + u * CHUNK_SIZE_X;
				int _v = y + v * CHUNK_SIZE_Y;
				int height = (int)(-glm::perlin(glm::vec3(_u * 0.05f, _v * 0.05f, SEED)) * 10) + 10;
				for (int h = 0; h < height - 4; h++)
					bl_pos.push_back("Coblestone");

				bl_pos.push_back("Dirt");
				bl_pos.push_back("Dirt");
				bl_pos.push_back("Dirt");
				bl_pos.push_back("Dirt");
				bl_pos.push_back("Grass");

				for (int h = height + 1; h < CHUNK_HEIGHT; h++)
					bl_pos.push_back("Air");
			}
		}
		m_blocks.push_back(bl_pos);

		//int height = (int)(-glm::perlin(glm::vec3(1 * 0.05f, 0 * 0.05f, SEED)) * 30);
		//m_blocks[0].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Wood",   glm::vec3( 1,  height + 1,  0))));
		//m_blocks[0].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Wood",   glm::vec3( 1,  height + 2,  0))));
		//m_blocks[0].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Wood",   glm::vec3( 1,  height + 3,  0))));
		//m_blocks[0].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Wood",   glm::vec3( 1,  height + 4,  0))));
		//m_blocks[0].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Wood",   glm::vec3( 1,  height + 5,  0))));
		//m_blocks[0].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 1,  height + 6,  0))));
		//m_blocks[0].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 2,  height + 6,  0))));
		//m_blocks[0].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 0,  height + 6,  0))));
		//m_blocks[0].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 1,  height + 6,  1))));
		//m_blocks[0].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 1,  height + 6, -1))));
		//m_blocks[0].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 2,  height + 5,  0))));
		//m_blocks[0].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 2,  height + 5, -1))));
		//m_blocks[0].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 0,  height + 5,  0))));
		//m_blocks[0].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 0,  height + 5,  1))));
		//m_blocks[0].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 1,  height + 5,  1))));
		//m_blocks[0].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 2,  height + 5,  1))));
		//m_blocks[0].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 1,  height + 5, -1))));
		//m_blocks[0].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 0,  height + 5, -1))));
		//m_blocks[0].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 2,  height + 4,  0))));
		//m_blocks[0].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 2,  height + 4, -1))));
		//m_blocks[0].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 0,  height + 4,  0))));
		//m_blocks[0].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 0,  height + 4,  1))));
		//m_blocks[0].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 1,  height + 4,  1))));
		//m_blocks[0].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 2,  height + 4,  1))));
		//m_blocks[0].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 1,  height + 4, -1))));
		//m_blocks[0].push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair("Leaves", glm::vec3( 0,  height + 4, -1))));
	}

	void ChunkRenderer::update_world()
	{
		m_blocks_polygones.clear();
		for (int k = 0; k < size(m_blocks); k++)
		{
			bl_pol.clear();
			int i = 0;
			for (int x = 0; x < CHUNK_SIZE_X; x++)
			{
				for (int z = 0; z < CHUNK_SIZE_Y; z++)
				{
					for (int y = 0; y < CHUNK_HEIGHT; y++)
					{
						update_blocks(std::make_pair(m_blocks[k][i], glm::vec3(chunks_coords[k].x * CHUNK_SIZE_X + x, y, chunks_coords[k].y * CHUNK_SIZE_Y + z)));
						i++;
					}
				}
			}
			m_blocks_polygones.push_back(bl_pol);
		}
		bl_pol.clear();
	}

	bool ChunkRenderer::getObjectsInArea(const glm::vec3& BottomLeftFront, const glm::vec3& TopRightFront, const glm::vec3& TopLeftBack)
	{
		bool is_colide = false;
		for (int i = 0; i < size(chunks_coords); i++)
		{
			if (chunks_coords[i].x * CHUNK_SIZE_X <= BottomLeftFront.x && chunks_coords[i].x * CHUNK_SIZE_X + CHUNK_SIZE_X - 1 >= BottomLeftFront.x &&
				chunks_coords[i].y * CHUNK_SIZE_Y <= TopRightFront.z   && chunks_coords[i].y * CHUNK_SIZE_Y + CHUNK_SIZE_Y - 1 >= TopRightFront.z)
			{
				//chunk->setBlocksPositions(m_blocks[i]);
				//is_colide = chunk->getObjectsInArea(BottomLeftFront, TopRightFront, TopLeftBack);
			}
		}
		return is_colide;
	}
}