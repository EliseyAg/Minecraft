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

		auto pTop = ResourceManager::loadAnimatedPolygon(   "Top",    "BlockTextureAtlas", "PolygonShader", m_size.x, m_size.z, initialSubTexture[0]);
		auto pBottom = ResourceManager::loadAnimatedPolygon("Bottom", "BlockTextureAtlas", "PolygonShader", m_size.x, m_size.z, initialSubTexture[2]);
		auto pFront = ResourceManager::loadAnimatedPolygon( "Front",  "BlockTextureAtlas", "PolygonShader", m_size.x, m_size.y, initialSubTexture[1]);
		auto pBack = ResourceManager::loadAnimatedPolygon(  "Back",   "BlockTextureAtlas", "PolygonShader", m_size.x, m_size.y, initialSubTexture[1]);
		auto pRight = ResourceManager::loadAnimatedPolygon( "Right",  "BlockTextureAtlas", "PolygonShader", m_size.z, m_size.y, initialSubTexture[1]);
		auto pLeft = ResourceManager::loadAnimatedPolygon(  "Left",   "BlockTextureAtlas", "PolygonShader", m_size.z, m_size.y, initialSubTexture[1]);
	}

	void Cube::render(glm::vec3& camera_position)
	{
		m_polygones_positions[0] = glm::vec3(0, m_size.y / 2, 0) + m_position;
		m_polygones_positions[1] = glm::vec3(0, -m_size.y / 2, 0) + m_position;
		m_polygones_positions[2] = glm::vec3(0, 0, m_size.z / 2) + m_position;
		m_polygones_positions[3] = glm::vec3(0, 0, -m_size.z / 2) + m_position;
		m_polygones_positions[4] = glm::vec3(m_size.x / 2, 0, 0) + m_position;
		m_polygones_positions[5] = glm::vec3(-m_size.x / 2, 0, 0) + m_position;

		ResourceManager::getAnimatedPolygon("Top")->setPosition(m_polygones_positions[0]);
		ResourceManager::getAnimatedPolygon("Top")->setRotation(glm::vec4(90, 0, 0, 0) + m_rotation);
		ResourceManager::getAnimatedPolygon("Bottom")->setPosition(m_polygones_positions[1]);
		ResourceManager::getAnimatedPolygon("Bottom")->setRotation(glm::vec4(90, 0, 0, 0) + m_rotation);
		ResourceManager::getAnimatedPolygon("Front")->setPosition(m_polygones_positions[2]);
		ResourceManager::getAnimatedPolygon("Front")->setRotation(glm::vec4(0, 0, 0, 0) + m_rotation);
		ResourceManager::getAnimatedPolygon("Back")->setPosition(m_polygones_positions[3]);
		ResourceManager::getAnimatedPolygon("Back")->setRotation(glm::vec4(0, 0, 0, 0) + m_rotation);
		ResourceManager::getAnimatedPolygon("Right")->setPosition(m_polygones_positions[4]);
		ResourceManager::getAnimatedPolygon("Right")->setRotation(glm::vec4(0, 90, 0, 0) + m_rotation);
		ResourceManager::getAnimatedPolygon("Left")->setPosition(m_polygones_positions[5]);
		ResourceManager::getAnimatedPolygon("Left")->setRotation(glm::vec4(0, 90, 0, 0) + m_rotation);
		int _arr[6];
		_arr[0] = 0;
		_arr[1] = 1;
		_arr[2] = 2;
		_arr[3] = 3;
		_arr[4] = 4;
		_arr[5] = 5;
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
					int _mem = _arr[j];
					arr[j] = arr[j + 1];
					_arr[j] = _arr[j + 1];
					arr[j + 1] = mem;
					_arr[j + 1] = _mem;
				}
				if (arr[j].second > arr[j + 1].second && arr[j].second < 0) {
					std::pair<std::string, float> mem = arr[j];
					int _mem = _arr[j];
					arr[j] = arr[j + 1];
					_arr[j] = _arr[j + 1];
					arr[j + 1] = mem;
					_arr[j + 1] = _mem;
				}
			}
		}

		for (int k = 0; k < 6; k++) {
			int _k = _arr[k];
			if (!m_polygones[_k])
			{
				ResourceManager::getAnimatedPolygon(arr[k].first)->render();
			}
		}
	}

	void Cube::update(uint64_t delta)
	{
		ResourceManager::getAnimatedPolygon("Top"   )->update(delta);
		ResourceManager::getAnimatedPolygon("Bottom")->update(delta);
		ResourceManager::getAnimatedPolygon("Front" )->update(delta);
		ResourceManager::getAnimatedPolygon("Back"  )->update(delta);
		ResourceManager::getAnimatedPolygon("Right" )->update(delta);
		ResourceManager::getAnimatedPolygon("Left"  )->update(delta);
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
		ResourceManager::getAnimatedPolygon("Top"   )->setTexture(SubTextures[0]);
		ResourceManager::getAnimatedPolygon("Bottom")->setTexture(SubTextures[2]);
		ResourceManager::getAnimatedPolygon("Front" )->setTexture(SubTextures[1]);
		ResourceManager::getAnimatedPolygon("Back"  )->setTexture(SubTextures[1]);
		ResourceManager::getAnimatedPolygon("Right" )->setTexture(SubTextures[1]);
		ResourceManager::getAnimatedPolygon("Left"  )->setTexture(SubTextures[1]);
	}

	void Cube::setPolygones(bool polygones[6])
	{
		for (int i = 0; i < 6; i++)
		{
			m_polygones[i] = polygones[i];
		}
	}
}