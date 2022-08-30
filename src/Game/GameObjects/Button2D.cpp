#include "Button2D.hpp"
#include "../../RenderEngine/OpenGL/Polygon2D.hpp"
#include "../../RenderEngine/OpenGL/Texture2D.hpp"
#include "../../RenderEngine/OpenGL/ShaderProgram.hpp"

#include <iostream>

namespace Game
{
	Button2D::Button2D(std::shared_ptr<RenderEngine::Texture2D> pTexture, std::string initialSubTexture, std::shared_ptr<RenderEngine::ShaderProgram> pShaderProgram, glm::vec2& position, glm::vec2& size)
		: m_position(position)
		, m_size(size)
	{
		m_pButton = std::make_unique<Polygon2D>(pTexture, initialSubTexture, pShaderProgram, glm::vec3(m_position.x, m_position.y, -0.4f), m_size);
	}

	void Button2D::render()
	{
		m_pButton->render(glm::vec3(0.f));
	}

	void Button2D::setPosition(glm::vec2& position)
	{
		m_position = position;
		m_pButton->setPosition(glm::vec3(m_position.x, m_position.y, -0.4f));
	}

	void Button2D::setTexture(std::string TextureName)
	{
		m_pButton->setTexture(TextureName);
	}

	bool Button2D::isPressed(double x_pos, double y_pos)
	{
		if (x_pos >= m_position.x     - m_size_colider.x / 2 && x_pos <= m_position.x     + m_size_colider.x / 2 &&
			y_pos >= m_position.y - 2 - m_size_colider.y / 2 && y_pos <= m_position.y - 2 + m_size_colider.y / 2)
		{
			return true;
		}
		return false;
	}
}