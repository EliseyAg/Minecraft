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
		block = std::make_unique<Cube>(m_pTexture, initialSubTexture, m_pShaderProgram, m_position, m_size, m_rotation);
	}

	void Block::render(glm::vec3 cam_pos)
	{
		block->render(cam_pos);
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
}