#include "Block.hpp"

namespace Game
{
	Block::Block(std::shared_ptr<RenderEngine::Texture2D> pTexture,
				 const std::vector<std::string>& initialSubTexture,
				 std::shared_ptr<RenderEngine::ShaderProgram> pShaderProgram,
				 glm::vec3& position,
				 glm::vec3& size,
				 glm::vec4& rotation)
				 : m_pTexture(std::move(pTexture))
				 , m_pShaderProgram(std::move(pShaderProgram))
				 , m_position(std::move(position))
				 , m_size(std::move(size))
				 , m_rotation(std::move(rotation))
	{
		block = std::make_shared<Cube>(m_pTexture, initialSubTexture, m_pShaderProgram, m_position, m_size, m_rotation);
	}

	void Block::render()
	{
		block->render();
	}

	void Block::update(const uint64_t delta)
	{
		block->update(delta);
	}

	void Block::setPosition(glm::vec3 position)
	{
		m_position = position;
		block->setPosition(position);
	}

	void Block::setType(std::string type)
	{
		m_type = type;
		for (int i = 0; i < size(types); i++)
		{
			if (types[i].first == m_type)
			{
				block->setTexture(types[i].second);
				return;
			}
		}
		m_type = types[0].first;
		block->setTexture(types[0].second);
		
	}

	void Block::setPolygones(bool polygones[6])
	{
		block->setPolygones(polygones);
	}
}