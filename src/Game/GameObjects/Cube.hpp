#pragma once
#include "../../RenderEngine/OpenGL/Animated_Polygon2D.hpp"

#include "glm/vec3.hpp"
#include "string"
#include "vector"

namespace Game
{
	class Cube
	{
	public:
		Cube(std::shared_ptr<RenderEngine::Texture2D> pTexture,
			 const std::vector<std::string>& initialSubTexture,
			 std::shared_ptr<RenderEngine::ShaderProgram> pShaderProgram,
			 glm::vec3& position = glm::vec3(0.f),
			 glm::vec3& size = glm::vec3(1.f),
			 glm::vec4& rotation = glm::vec4(0.f));
		void render(glm::vec3& camera_position);
		void update(uint64_t delta);
		void setPosition(const glm::vec3 position);
		void setSize(const glm::vec3 size);
		void setTexture(std::vector<std::string>& SubTextures);
		void setPolygones(bool polygones[6]);

		std::pair<std::string, float> arr[6];
	private:
		std::shared_ptr<RenderEngine::Texture2D> m_pTexture;
		std::shared_ptr<RenderEngine::ShaderProgram> m_pShaderProgram;
		glm::vec3 m_position;
		glm::vec3 m_size;
		glm::vec4 m_rotation;
		glm::vec3 m_polygones_positions[6];
		bool m_polygones[6];
	};
}