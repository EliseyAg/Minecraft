#pragma once
#include "Cube.hpp"

#include "glm/vec2.hpp"
#include <string>
#include <memory>

namespace Game
{
	class Block
	{
	public:
		Block(std::shared_ptr<RenderEngine::Texture2D> pTexture,
			  const std::vector<std::string>& initialSubTexture,
			  std::shared_ptr<RenderEngine::ShaderProgram> pShaderProgram,
			  glm::vec3& position = glm::vec3(0.f),
			  glm::vec3& size = glm::vec3(1.f),
			  glm::vec4& rotation = glm::vec4(0.f));
		void render(glm::vec3 cam_pos);
		void update(const uint64_t delta);

		void setPosition(glm::vec3 position);
	private:
		std::unique_ptr<Cube> block;
		std::shared_ptr<RenderEngine::Texture2D> m_pTexture;
		std::shared_ptr<RenderEngine::ShaderProgram> m_pShaderProgram;
		glm::vec3 m_position;
		glm::vec3 m_size;
		glm::vec4 m_rotation;
		std::string m_type;
	};
}