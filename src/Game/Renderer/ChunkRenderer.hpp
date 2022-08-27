#pragma once
#include "../GameObjects/Chunk.hpp"
#include "../GameObjects/Cube.hpp"
#include "../../Resources/ResourceManager.hpp"
#include "glm/vec2.hpp"

#include <memory>
#include <vector>

namespace Renderer
{
	class ChunkRenderer
	{
	public:
		static void setTextureAtlas(std::shared_ptr<RenderEngine::Texture2D> pTexture);
		static void setShaderProgram(std::shared_ptr<RenderEngine::ShaderProgram> pShaderProgram);

		~ChunkRenderer() = delete;
		ChunkRenderer() = delete;
		ChunkRenderer(const ChunkRenderer&) = delete;
		ChunkRenderer(ChunkRenderer&&) = delete;
		ChunkRenderer& operator=(const ChunkRenderer&) = delete;
		ChunkRenderer& operator=(ChunkRenderer&&) = delete;

		static void render();
		static void generate_world();
		static void saveworld();
		static void loadworld();

		static bool getObjectsInArea(const glm::vec3& BottomLeftFront, const glm::vec3& TopRightFront, const glm::vec3& TopLeftBack);

	private:
		static std::vector<std::vector<Game::Chunk::s_blocks_polygones>> blocks_polygones;
		static std::vector<glm::vec2> chunks_coords;
		static std::unique_ptr<Game::Chunk> chunk;
		static std::vector<std::vector<std::shared_ptr<std::pair<std::string, glm::vec3>>>> m_blocks;
		static std::vector<std::vector<std::shared_ptr<std::pair<std::string, glm::vec3>>>> blocks;

		static std::shared_ptr<RenderEngine::Texture2D> m_pTexture;
		static std::shared_ptr<RenderEngine::ShaderProgram> m_pShaderProgram;
	};
}