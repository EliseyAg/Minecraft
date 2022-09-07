#pragma once
#include "../../RenderEngine/OpenGL/Polygon2D.hpp"
#include "../../Physics/PhysicsEngine.hpp"

#include "glm/vec3.hpp"
#include <string>
#include <vector>

namespace Physics
{
	class AABB;
}

namespace Game
{
	class Cube
	{
	public:
		Cube(std::shared_ptr<RenderEngine::Texture2D> pTexture,
			 const std::vector<std::string>& initialSubTexture,
			 std::shared_ptr<RenderEngine::ShaderProgram> pShaderProgram,
			 glm::vec3& position = glm::vec3(0.f),
			 glm::vec3& size = glm::vec3(0.99f),
			 glm::vec4& rotation = glm::vec4(0.f));

		void render();
		void update(uint64_t delta);

		void setPosition(const glm::vec3 position);
		void setSize(const glm::vec3 size);
		void setTexture(std::vector<std::string>& SubTextures);
		void setPolygones(bool polygones[6]);

		const std::vector<Physics::AABB>& getColiders() const { return m_coliders; };
	private:
		std::shared_ptr<RenderEngine::Texture2D> m_pTexture;
		std::shared_ptr<RenderEngine::ShaderProgram> m_pShaderProgram;
		glm::vec3 m_position;
		glm::vec3 m_size;
		glm::vec4 m_rotation;
		glm::vec3 m_polygones_positions[6];
		glm::vec3 m_polygones_rotations[6];
		bool m_polygones[6];
		glm::vec3 m_normals[6];
		std::vector<std::string> m_SubTextures;
		std::vector<Physics::AABB> m_coliders;
	};
}