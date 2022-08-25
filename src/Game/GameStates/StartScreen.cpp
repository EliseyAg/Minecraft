#include "StartScreen.hpp"

namespace GameStates
{
	StartScreen::StartScreen(std::shared_ptr<RenderEngine::Texture2D> pTexture, std::string initialSubTexture, std::shared_ptr<RenderEngine::ShaderProgram> pShaderProgram)
	{
		m_pScreen = std::make_unique<Game::Polygon2D>(pTexture, initialSubTexture, pShaderProgram, glm::vec3(0, 2, -0.5), glm::vec2(1.f));
	}

	void StartScreen::render() const
	{
		m_pScreen->render();
	}
}