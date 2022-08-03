#include "Cube.hpp"
#include "../../Resources/ResourceManager.hpp"
#include "../../RenderEngine/OpenGL/ShaderProgram.hpp"

#include <iostream>

namespace Game
{
	Cube::Cube(std::shared_ptr<RenderEngine::Texture2D> pTexture,
			   const std::vector<std::string>& initialSubTexture,
			   std::shared_ptr<RenderEngine::ShaderProgram> pShaderProgram,
			   glm::vec3& position,
			   glm::vec3& size,
			   glm::vec4& rotation)
			   : m_pTexture(std::move(pTexture))
			   , m_pShaderProgram(std::move(pShaderProgram))
			   , m_position(std::move(position))
			   , m_size(std::move(size))
			   , m_rotation(std::move(rotation))
	{

		auto m_pPol = ResourceManager::loadAnimatedPolygon(   "Polygon",    "BlockTextureAtlas", "PolygonShader", m_size.x, m_size.z, initialSubTexture[0]);
	}

	void Cube::render(glm::vec3& camera_position)
	{
		m_polygones_positions[0] = glm::vec3(0, m_size.y / 2, 0) + m_position;
		m_polygones_positions[1] = glm::vec3(0, -m_size.y / 2, 0) + m_position;
		m_polygones_positions[2] = glm::vec3(0, 0, m_size.z / 2) + m_position;
		m_polygones_positions[3] = glm::vec3(0, 0, -m_size.z / 2) + m_position;
		m_polygones_positions[4] = glm::vec3(m_size.x / 2, 0, 0) + m_position;
		m_polygones_positions[5] = glm::vec3(-m_size.x / 2, 0, 0) + m_position;
		m_polygones_rotations[0] = glm::vec3( 90,  0,   0);
		m_polygones_rotations[1] = glm::vec3(-90,  0,   0);
		m_polygones_rotations[2] = glm::vec3( 0,   0,   0);
		m_polygones_rotations[3] = glm::vec3( 0, 180,   0);
		m_polygones_rotations[4] = glm::vec3( 0,  90,   0);
		m_polygones_rotations[5] = glm::vec3( 0, -90,   0);

		arr[0] = std::pair<int, float>(0, ((m_polygones_positions[0].x - camera_position.x) * (m_polygones_positions[0].y - camera_position.y) * (m_polygones_positions[0].z - camera_position.z)) / 3);
		arr[1] = std::pair<int, float>(1, ((m_polygones_positions[1].x - camera_position.x) * (m_polygones_positions[1].y - camera_position.y) * (m_polygones_positions[1].z - camera_position.z)) / 3);
		arr[2] = std::pair<int, float>(2, ((m_polygones_positions[2].x - camera_position.x) * (m_polygones_positions[2].y - camera_position.y) * (m_polygones_positions[2].z - camera_position.z)) / 3);
		arr[3] = std::pair<int, float>(3, ((m_polygones_positions[3].x - camera_position.x) * (m_polygones_positions[3].y - camera_position.y) * (m_polygones_positions[3].z - camera_position.z)) / 3);
		arr[4] = std::pair<int, float>(4, ((m_polygones_positions[4].x - camera_position.x) * (m_polygones_positions[4].y - camera_position.y) * (m_polygones_positions[4].z - camera_position.z)) / 3);
		arr[5] = std::pair<int, float>(5, ((m_polygones_positions[5].x - camera_position.x) * (m_polygones_positions[5].y - camera_position.y) * (m_polygones_positions[5].z - camera_position.z)) / 3);

		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 5; j++) {
				if (arr[j].second < arr[j + 1].second && arr[j].second > 0) {
					std::pair<int, float> mem = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = mem;
				}
				if (arr[j].second > arr[j + 1].second && arr[j].second < 0) {
					std::pair<int, float> mem = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = mem;
				}
			}
		}

		for (int k = 0; k < 6; k++) {
			if (!m_polygones[arr[k].first])
			{
				ResourceManager::getAnimatedPolygon("Polygon")->setPosition(m_polygones_positions[arr[k].first]);
				ResourceManager::getAnimatedPolygon("Polygon")->setRotation(glm::vec4(m_polygones_rotations[arr[k].first], 0));
				ResourceManager::getAnimatedPolygon("Polygon")->setTexture(m_SubTextures[arr[k].first]);
				ResourceManager::getAnimatedPolygon("Polygon")->render();
			}
		}
	}

	void Cube::update(uint64_t delta)
	{
		ResourceManager::getAnimatedPolygon("Polygon")->update(delta);
	}

	void Cube::setPosition(const glm::vec3 position)
	{
		m_position = position;
	}

	void Cube::setSize(const glm::vec3 size)
	{
		m_size = size;
	}

	void Cube::setTexture(std::vector<std::string>& SubTextures)
	{
		m_SubTextures.clear();
		m_SubTextures.push_back(SubTextures[0]);
		m_SubTextures.push_back(SubTextures[2]);
		m_SubTextures.push_back(SubTextures[1]);
		m_SubTextures.push_back(SubTextures[1]);
		m_SubTextures.push_back(SubTextures[1]);
		m_SubTextures.push_back(SubTextures[1]);
	}

	void Cube::setPolygones(bool polygones[6])
	{
		for (int i = 0; i < 6; i++)
		{
			m_polygones[i] = polygones[i];
		}
	}
}