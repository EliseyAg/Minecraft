#pragma once
#include "glm/vec2.hpp"
#include "glm/mat4x4.hpp"
#include <memory>
#include <string>

namespace RenderEngine
{
	class Texture2D;
	class ShaderProgram;
}

namespace Game
{
	class Polygon2D;

	class Button2D
	{
	public:
		Button2D(std::shared_ptr<RenderEngine::Texture2D> pTexture, std::string initialSubTexture, std::shared_ptr<RenderEngine::ShaderProgram> pShaderProgram, glm::vec2& position = glm::vec2(0.f, 10.f), glm::vec2& size = glm::vec2(0.5f, 0.125f));

		virtual void render();
		virtual void setPosition(glm::vec2& position);
		virtual void setTexture(std::string TextureName);

		bool isPressed(double x_pos, double y_pos);
	private:
		glm::vec2 m_position;
		glm::vec2 m_size;
		glm::vec2 m_size_colider = glm::vec2(512, 160);
		std::unique_ptr<Polygon2D> m_pButton;
	};
}