#include "Chunk.hpp"

#include <iostream>
#include <cmath>

namespace Game
{
	Chunk::Chunk(std::shared_ptr<RenderEngine::Texture2D> pTexture,
				 std::shared_ptr<RenderEngine::ShaderProgram> pShaderProgram)
		: m_pTexture(pTexture)
		, m_pShaderProgram(pShaderProgram)
	{
		std::vector<std::string> GrassBlock = {
													 "Grass_Top",
													 "Grass_Left",
													 "Dirt"
		};
		block = std::make_shared<Block>(pTexture, GrassBlock, pShaderProgram);
		m_position = glm::vec2(0.f);
	}

	void Chunk::render()
	{
		for (int i = 0; i < size(m_blocks); i++)
		{
			block->setPosition(m_blocks[i]->second);
			block->setType(m_blocks[i]->first);
			block->setPolygones(m_blocks_polygones[i].m_blocks_polygones);
			block->render();
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

	bool Chunk::getObjectsInArea(const glm::vec3& BottomLeftFront, const glm::vec3& TopRightFront, const glm::vec3& TopLeftBack)
	{
		bool f = false;
		for (int i = 0; i < size(m_blocks); i++)
		{
			block->setPosition(m_blocks[i]->second);
			if      (block->getCube()->getColiders()[0].BottomLeftFront.x <= BottomLeftFront.x && block->getCube()->getColiders()[0].TopRightFront.x >= BottomLeftFront.x &&
				     block->getCube()->getColiders()[0].BottomLeftFront.y <= BottomLeftFront.y && block->getCube()->getColiders()[0].TopLeftBack.y   >= BottomLeftFront.y &&
				     block->getCube()->getColiders()[0].BottomLeftFront.z <= BottomLeftFront.z && block->getCube()->getColiders()[0].TopLeftBack.z   >= BottomLeftFront.z)
			{
				f = true;
				std::cout << "Colide BottomLeftFront" << std::endl;
				block_position_colide = m_blocks[i]->second;
				break;
			}
			else if (block->getCube()->getColiders()[0].BottomLeftFront.x <= TopRightFront.x && block->getCube()->getColiders()[0].TopRightFront.x >= TopRightFront.x &&
				     block->getCube()->getColiders()[0].BottomLeftFront.y <= TopRightFront.y && block->getCube()->getColiders()[0].TopLeftBack.y >= TopRightFront.y &&
				     block->getCube()->getColiders()[0].BottomLeftFront.z <= TopRightFront.z && block->getCube()->getColiders()[0].TopLeftBack.z >= TopRightFront.z)
			{
				f = true;
				std::cout << "Colide TopRightFront" << std::endl;
				block_position_colide = m_blocks[i]->second;
				break;
			}
			else if (block->getCube()->getColiders()[0].BottomLeftFront.x <= TopLeftBack.x && block->getCube()->getColiders()[0].TopRightFront.x >= TopLeftBack.x &&
				     block->getCube()->getColiders()[0].BottomLeftFront.y <= TopLeftBack.y && block->getCube()->getColiders()[0].TopLeftBack.y >= TopLeftBack.y &&
				     block->getCube()->getColiders()[0].BottomLeftFront.z <= TopLeftBack.z && block->getCube()->getColiders()[0].TopLeftBack.z >= TopLeftBack.z)
			{
				f = true;
				std::cout << "Colide TopLeftBack" << std::endl;
				block_position_colide = m_blocks[i]->second;
				break;
			}
		}
		return f;
	}
}