#include "Chunk.hpp"

#include <iostream>
#include <cmath>

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 16
#define CHUNK_HEIGHT 64

namespace Game
{
	Chunk::Chunk(std::shared_ptr<RenderEngine::Texture2D> pTexture)
		: m_pTexture(pTexture)
	{
		std::vector<std::string> GrassBlock = {
													 "Grass_Top",
													 "Grass_Left",
													 "Dirt"
		};
		block = std::make_shared<Block>(pTexture, GrassBlock);
		m_position = glm::vec2(0.f);
	}

	void Chunk::render(const glm::vec3& camera_position)
	{
		int i = 0;
		for (int x = 0; x < CHUNK_SIZE_X; x++)
		{
			for (int z = 0; z < CHUNK_SIZE_Y; z++)
			{
				for (int y = 0; y < CHUNK_HEIGHT; y++)
				{
					if (m_blocks[i] != "Air")
					{
						block->setPosition(glm::vec3(x, y, z) + glm::vec3(m_position.x * CHUNK_SIZE_X, 0, m_position.y * CHUNK_SIZE_Y));
						block->setType(m_blocks[i]);
						block->setPolygones(m_blocks_polygones[i].m_blocks_polygones);
						block->render(camera_position);
					}
					i++;
				}
			}
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

	void Chunk::setBlocksPositions(std::vector<std::string> blocks)
	{
		m_blocks = blocks;
	}

	void Chunk::setBlocksPolygones(std::vector<s_blocks_polygones> blocks_polygones)
	{
		m_blocks_polygones = blocks_polygones;
	}

	bool Chunk::getObjectsInArea(const glm::vec3& BottomLeftFront, const glm::vec3& TopRightFront, const glm::vec3& TopLeftBack)
	{
		bool f = false;
		for (int i = 0; i < size(m_blocks); i++)
		{
			if (m_blocks[i] != "Air")
			{
				block->setPosition(glm::vec3(0));
				if (block->getCube()->getColiders()[0].BottomLeftFront.x <= BottomLeftFront.x && block->getCube()->getColiders()[0].TopRightFront.x >= BottomLeftFront.x &&
					block->getCube()->getColiders()[0].BottomLeftFront.y <= BottomLeftFront.y && block->getCube()->getColiders()[0].TopLeftBack.y >= BottomLeftFront.y &&
					block->getCube()->getColiders()[0].BottomLeftFront.z <= BottomLeftFront.z && block->getCube()->getColiders()[0].TopLeftBack.z >= BottomLeftFront.z)
				{
					f = true;
					std::cout << "Colide BottomLeftFront" << std::endl;
					block_position_colide = glm::vec3(0);
					break;
				}
				else if (block->getCube()->getColiders()[0].BottomLeftFront.x <= TopRightFront.x && block->getCube()->getColiders()[0].TopRightFront.x >= TopRightFront.x &&
					block->getCube()->getColiders()[0].BottomLeftFront.y <= TopRightFront.y && block->getCube()->getColiders()[0].TopLeftBack.y >= TopRightFront.y &&
					block->getCube()->getColiders()[0].BottomLeftFront.z <= TopRightFront.z && block->getCube()->getColiders()[0].TopLeftBack.z >= TopRightFront.z)
				{
					f = true;
					std::cout << "Colide TopRightFront" << std::endl;
					block_position_colide = glm::vec3(0);
					break;
				}
				else if (block->getCube()->getColiders()[0].BottomLeftFront.x <= TopLeftBack.x && block->getCube()->getColiders()[0].TopRightFront.x >= TopLeftBack.x &&
					block->getCube()->getColiders()[0].BottomLeftFront.y <= TopLeftBack.y && block->getCube()->getColiders()[0].TopLeftBack.y >= TopLeftBack.y &&
					block->getCube()->getColiders()[0].BottomLeftFront.z <= TopLeftBack.z && block->getCube()->getColiders()[0].TopLeftBack.z >= TopLeftBack.z)
				{
					f = true;
					std::cout << "Colide TopLeftBack" << std::endl;
					block_position_colide = glm::vec3(0);
					break;
				}
			}
		}
		return f;
	}
}