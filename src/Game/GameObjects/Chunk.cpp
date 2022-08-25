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
			block->setPolygones(m_blocks_polygones[i].blocks_polygones);
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

	std::vector<std::shared_ptr<Cube>> Chunk::getObjectsInArea(const glm::vec3& BottomLeftFront, const glm::vec3& TopRightFront, const glm::vec3& TopLeftBack)
	{
		std::vector<std::shared_ptr<Cube>> output;

		std::shared_ptr<Cube> cube;
		std::vector<std::string> v = { "Grass" };
		cube = std::make_shared<Cube>(m_pTexture, v, m_pShaderProgram);

		size_t startXY_x = static_cast<size_t>(floor(BottomLeftFront.x));
		size_t endXY_x   = static_cast<size_t>(ceil (TopRightFront.x  ));

		size_t startXY_y = static_cast<size_t>(floor(TopRightFront.y  ));
		size_t endXY_y   = static_cast<size_t>(ceil (BottomLeftFront.y));

		size_t startYZ_y = static_cast<size_t>(floor(BottomLeftFront.y));
		size_t endYZ_y   = static_cast<size_t>(ceil (TopLeftBack.y    ));

		size_t startYZ_z = static_cast<size_t>(floor(TopLeftBack.z    ));
		size_t endYZ_z   = static_cast<size_t>(ceil (BottomLeftFront.z));

		size_t startXZ_x = static_cast<size_t>(floor(TopRightFront.x));
		size_t endXZ_x   = static_cast<size_t>(ceil (TopLeftBack.x  ));

		size_t startXZ_z = static_cast<size_t>(floor(TopLeftBack.z  ));
		size_t endXZ_z   = static_cast<size_t>(ceil (TopRightFront.z));

		for (size_t currentColumn = startXZ_x; currentColumn < endXZ_x; ++currentColumn)
		{
			for (size_t currentRow = startXZ_z; currentRow < endXZ_z; ++currentRow)
			{
				cube->setPosition(m_blocks[(currentRow + currentColumn * 16) * 8]->second);
				auto& currentObject = cube;
				output.push_back(currentObject);
			}
		}

		std::cout << output.size() << std::endl;

		return output;
	}
}