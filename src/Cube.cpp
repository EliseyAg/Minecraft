#include "Cube.hpp"
#include "Resources/ResourceManager.hpp"
#include "Renderer/ShaderProgram.hpp"

#include <iostream>

namespace Game
{
	Cube::Cube(std::shared_ptr<Texture2D> pTexture,
			   std::string initialSubTexture,
			   std::shared_ptr<ShaderProgram> pShaderProgram,
			   glm::vec3& position,
			   glm::vec3& size)
			   : m_pTexture(std::move(pTexture))
			   , m_pShaderProgram(std::move(pShaderProgram))
			   , m_position(std::move(position))
			   , m_size(std::move(size))
	{
		std::vector<std::string> subTexturesNames = {
													 "Grass_Top",
													 "Grass_Left",
													 "Grass_Bottom"
		};

		auto pTop = ResourceManager::loadAnimatedPolygon(   "Top",    "BlockTextureAtlas", "PolygonShader", m_size.x, m_size.z, "Grass_Top"   );
		auto pBottom = ResourceManager::loadAnimatedPolygon("Bottom", "BlockTextureAtlas", "PolygonShader", m_size.x, m_size.z, "Grass_Bottom");
		auto pFront = ResourceManager::loadAnimatedPolygon( "Front",  "BlockTextureAtlas", "PolygonShader", m_size.x, m_size.y, "Grass_Left"  );
		auto pBack = ResourceManager::loadAnimatedPolygon(  "Back",   "BlockTextureAtlas", "PolygonShader", m_size.x, m_size.y, "Grass_Left"  );
		auto pRight = ResourceManager::loadAnimatedPolygon( "Right",  "BlockTextureAtlas", "PolygonShader", m_size.z, m_size.y, "Grass_Left"  );
		auto pLeft = ResourceManager::loadAnimatedPolygon(  "Left",   "BlockTextureAtlas", "PolygonShader", m_size.z, m_size.y, "Grass_Left"  );

		m_polygones_positions[0] = glm::vec3(0,  m_size.y / 2, 0);
		m_polygones_positions[1] = glm::vec3(0, -m_size.y / 2, 0);
		m_polygones_positions[2] = glm::vec3(0, 0,  m_size.z / 2);
		m_polygones_positions[3] = glm::vec3(0, 0, -m_size.z / 2);
		m_polygones_positions[4] = glm::vec3( m_size.x / 2, 0, 0);
		m_polygones_positions[5] = glm::vec3(-m_size.x / 2, 0, 0);

		pTop->setPosition(m_polygones_positions[0]);
		pTop->setRotation(glm::vec4(90, 0, 0, 0));
		pBottom->setPosition(m_polygones_positions[1]);
		pBottom->setRotation(glm::vec4(90, 0, 0, 0));
		pFront->setPosition(m_polygones_positions[2]);
		pFront->setRotation(glm::vec4(0, 0, 0, 0));
		pBack->setPosition(m_polygones_positions[3]);
		pBack->setRotation(glm::vec4(0, 0, 0, 0));
		pRight->setPosition(m_polygones_positions[4]);
		pRight->setRotation(glm::vec4(0, 90, 0, 0));
		pLeft->setPosition(m_polygones_positions[5]);
		pLeft->setRotation(glm::vec4(0, 90, 0, 0));
	}

	void Cube::render(glm::vec3& camera_position)
	{
		//camera_position = camera_position;
		arr[0] = std::pair<std::string, float>("Top",    ((m_polygones_positions[0].x - camera_position.x) * (m_polygones_positions[0].y - camera_position.y) * (m_polygones_positions[0].z - camera_position.z)) / 3);
		arr[1] = std::pair<std::string, float>("Bottom", ((m_polygones_positions[1].x - camera_position.x) * (m_polygones_positions[1].y - camera_position.y) * (m_polygones_positions[1].z - camera_position.z)) / 3);
		arr[2] = std::pair<std::string, float>("Front",  ((m_polygones_positions[2].x - camera_position.x) * (m_polygones_positions[2].y - camera_position.y) * (m_polygones_positions[2].z - camera_position.z)) / 3);
		arr[3] = std::pair<std::string, float>("Back",   ((m_polygones_positions[3].x - camera_position.x) * (m_polygones_positions[3].y - camera_position.y) * (m_polygones_positions[3].z - camera_position.z)) / 3);
		arr[4] = std::pair<std::string, float>("Right",  ((m_polygones_positions[4].x - camera_position.x) * (m_polygones_positions[4].y - camera_position.y) * (m_polygones_positions[4].z - camera_position.z)) / 3);
		arr[5] = std::pair<std::string, float>("Left",   ((m_polygones_positions[5].x - camera_position.x) * (m_polygones_positions[5].y - camera_position.y) * (m_polygones_positions[5].z - camera_position.z)) / 3);

		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 5; j++) {
				if (arr[j].second < arr[j + 1].second && arr[j].second > 0) {
					std::pair<std::string, float> mem = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = mem;
				}
				if (arr[j].second > arr[j + 1].second && arr[j].second < 0) {
					std::pair<std::string, float> mem = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = mem;
				}
			}
		}

		for (int k = 0; k < 6; k++) {
			ResourceManager::getAnimatedPolygon(arr[k].first)->render();
		}
	}
}