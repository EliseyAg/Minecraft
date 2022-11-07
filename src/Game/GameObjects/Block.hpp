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
			glm::vec3& position = glm::vec3(0.f),
			glm::vec3& size = glm::vec3(1.f),
			glm::vec4& rotation = glm::vec4(0.f));
		void render(const glm::vec3& camera_position);
		void update(const uint64_t delta);

		void setPosition(glm::vec3 position);
		void setType(std::string type);
		void setPolygones(bool polygones[6]);

		std::shared_ptr<Cube> getCube() const { return block; }
	private:
		std::shared_ptr<Cube> block;
		std::shared_ptr<RenderEngine::Texture2D> m_pTexture;
		glm::vec3 m_position;
		glm::vec3 m_size;
		glm::vec4 m_rotation;
		std::vector<std::pair<std::string, std::vector<std::string>>> types = {
			{"Grass", {"Grass_Top",
					  "Grass_Left",
					  "Dirt"}},
			{"Dirt", {"Dirt",
					  "Dirt",
					  "Dirt"}},
			{"Coblestone", {"Coblestone",
						    "Coblestone",
						    "Coblestone"}},
			{"Wood", {"Wood_Top",
					  "Wood_Left",
					  "Wood_Top"}},
		    {"Leaves", {"Leaves",
		                "Leaves",
		                "Leaves"}},
		};
		std::string m_type;
	};
}