#include "Chunk.hpp"

namespace Game
{
	Chunk::Chunk(std::shared_ptr<RenderEngine::Texture2D> pTexture,
				 std::shared_ptr<RenderEngine::ShaderProgram> pShaderProgram)
	{
		std::vector<std::string> subTexturesNames = {
													 "Grass_Top",
													 "Grass_Left",
													 "Dirt"
		};
		block = std::make_unique<Block>(pTexture, subTexturesNames, pShaderProgram);
	}

	void Chunk::render()
	{
		for (int i = 0; i < 100000; i++)
		{
			block->setPosition(block_coords[i]);
		}
	}
}