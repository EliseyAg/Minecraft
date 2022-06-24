#pragma once
#include "glm/vec2.hpp"
#include "Block.hpp"

namespace Game
{
	class Chunk
	{
	public:
		Chunk(std::shared_ptr<RenderEngine::Texture2D> pTexture,
			  std::shared_ptr<RenderEngine::ShaderProgram> pShaderProgram);

		void render();
	private:
		glm::vec2 m_position;
		std::unique_ptr<Block> block;
		glm::vec3 block_coords[100000];
	};
}