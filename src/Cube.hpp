#pragma once
#include "Animated_Polygon2D.hpp"

#include "glm/vec3.hpp"
#include "string"
namespace Game
{
	class Cube
	{
	public:
		Cube(std::shared_ptr<Texture2D> pTexture,
			 std::string initialSubTexture,
			 std::shared_ptr<ShaderProgram> pShaderProgram,
			 glm::vec3& position = glm::vec3(0.f),
			 glm::vec3& size = glm::vec3(8.f));
		void render(glm::vec3& camera_position);

		std::pair<std::string, float> arr[6];
	private:
		std::shared_ptr<Texture2D> m_pTexture;
		std::shared_ptr<ShaderProgram> m_pShaderProgram;
		glm::vec3 m_position;
		glm::vec3 m_size;
		glm::vec3 m_polygones_positions[6];
	};
}