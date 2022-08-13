#pragma once

#include "../../RenderEngine/OpenGL/Polygon2D.hpp"
#include "../../RenderEngine/OpenGL/Texture2D.hpp"
#include "../../RenderEngine/OpenGL/ShaderProgram.hpp"

#include <glm/vec3.hpp>
#include <memory>
#include <string>

namespace GameStates
{
	class StartScreen
	{
	public:
		StartScreen(std::shared_ptr<RenderEngine::Texture2D> pTexture, std::string initialSubTexture, std::shared_ptr<RenderEngine::ShaderProgram> pShaderProgram);

		virtual void render() const;
	private:
		std::unique_ptr<Game::Polygon2D> m_pScreen;
	};
}