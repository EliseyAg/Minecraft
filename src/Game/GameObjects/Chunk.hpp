#pragma once
#include "glm/vec2.hpp"
#include "Block.hpp"
#include <vector>
#include <string>

namespace Game
{
	class Chunk
	{
	public:
		Chunk(std::shared_ptr<RenderEngine::Texture2D> pTexture,
			  std::shared_ptr<RenderEngine::ShaderProgram> pShaderProgram);

		void render(glm::vec3& camera_position);
		void update(const uint64_t delta);
	private:
		glm::vec2 m_position;
		std::unique_ptr<Block> block;
		std::vector<std::pair<std::string, glm::vec3>> blocks;
	};
}