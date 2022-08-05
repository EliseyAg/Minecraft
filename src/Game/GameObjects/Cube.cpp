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

		for (int k = 0; k < 6; k++) {
			if (!m_polygones[k])
			{
				ResourceManager::getAnimatedPolygon("Polygon")->setPosition(m_polygones_positions[k]);
				ResourceManager::getAnimatedPolygon("Polygon")->setRotation(glm::vec4(m_polygones_rotations[k], 0));
				ResourceManager::getAnimatedPolygon("Polygon")->setTexture(m_SubTextures[k]);
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