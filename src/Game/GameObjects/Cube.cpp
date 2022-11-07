#include "Cube.hpp"
#include "../../Resources/ResourceManager.hpp"
#include "../../RenderEngine/OpenGL/ShaderProgram.hpp"
#include "../../Physics/PhysicsEngine.hpp"


#include <iostream>

namespace Game
{
	double angle(const glm::vec3& a, const glm::vec3& b)
	{
		double sc_mult = a.x * b.x + a.y * b.y + a.z * b.z;
		double len_a = sqrt((a.x) * (a.x) + (a.y) * (a.y) + (a.z) * (a.z));
		double len_b = sqrt((b.x) * (b.x) + (b.y) * (b.y) + (b.z) * (b.z));
		return glm::degrees(glm::acos(sc_mult / (len_a * len_b)));
	}

	Cube::Cube(std::shared_ptr<RenderEngine::Texture2D> pTexture,
			   const std::vector<std::string>& initialSubTexture,
			   glm::vec3& position,
			   glm::vec3& size,
			   glm::vec4& rotation)
			   : m_pTexture(std::move(pTexture))
			   , m_position(std::move(position))
			   , m_size(std::move(size))
			   , m_rotation(std::move(rotation))
	{

		auto m_pPol = ResourceManager::loadPolygon(   "Polygon",    "BlockTextureAtlas", "PolygonShader", m_size.x, m_size.z, initialSubTexture[0]);
		m_coliders.emplace_back(glm::vec3(-m_size.x / 2, -m_size.y / 2, -m_size.z / 2) + m_position, glm::vec3( m_size.x / 2,  m_size.y / 2, -m_size.z / 2) + m_position, glm::vec3(-m_size.x / 2,  m_size.y / 2,  m_size.z / 2) + m_position);
	}

	void Cube::render(const glm::vec3& camera_position)
	{
		m_polygones_rotations[0] = glm::vec3( 90,  0,   0);
		m_polygones_rotations[1] = glm::vec3(-90,  0,   0);
		m_polygones_rotations[2] = glm::vec3( 0,   0,   0);
		m_polygones_rotations[3] = glm::vec3( 0, 180,   0);
		m_polygones_rotations[4] = glm::vec3( 0,  90,   0);
		m_polygones_rotations[5] = glm::vec3( 0, -90,   0); 
		m_normals[0] = glm::vec3( 0,  1,  0);
		m_normals[1] = glm::vec3( 0, -1,  0);
		m_normals[2] = glm::vec3( 0,  0,  1);
		m_normals[3] = glm::vec3( 0,  0, -1);
		m_normals[4] = glm::vec3( 1,  0,  0);
		m_normals[5] = glm::vec3(-1,  0,  0);

		for (int k = 0; k < 6; k++) {
			if (!m_polygones[k] && angle(m_normals[k] + m_position, camera_position) < 90)
			{
				ResourceManager::getPolygon("Polygon")->setPosition(m_polygones_positions[k]);
				ResourceManager::getPolygon("Polygon")->setRotation(glm::vec4(m_polygones_rotations[k], 0));
				ResourceManager::getPolygon("Polygon")->setTexture(m_SubTextures[k]);
				ResourceManager::getPolygon("Polygon")->render(m_normals[k]);
			}
		}
	}

	void Cube::update(uint64_t delta)
	{
		
	}

	void Cube::setPosition(const glm::vec3 position)
	{
		m_position = position;
		m_polygones_positions[0] = glm::vec3(0, m_size.y / 2, 0) + m_position;
		m_polygones_positions[1] = glm::vec3(0, -m_size.y / 2, 0) + m_position;
		m_polygones_positions[2] = glm::vec3(0, 0, m_size.z / 2) + m_position;
		m_polygones_positions[3] = glm::vec3(0, 0, -m_size.z / 2) + m_position;
		m_polygones_positions[4] = glm::vec3(m_size.x / 2, 0, 0) + m_position;
		m_polygones_positions[5] = glm::vec3(-m_size.x / 2, 0, 0) + m_position;

		m_coliders[0].BottomLeftFront = (glm::vec3(-m_size.x / 2, -m_size.y / 2, -m_size.z / 2) + m_position);
		m_coliders[0].TopRightFront = (glm::vec3(m_size.x / 2, m_size.y / 2, -m_size.z / 2) + m_position);
		m_coliders[0].TopLeftBack = (glm::vec3(-m_size.x / 2, m_size.y / 2, m_size.z / 2) + m_position);
	}

	void Cube::setSize(const glm::vec3 size)
	{
		m_size = size;
		m_polygones_positions[0] = glm::vec3(0, m_size.y / 2, 0) + m_position;
		m_polygones_positions[1] = glm::vec3(0, -m_size.y / 2, 0) + m_position;
		m_polygones_positions[2] = glm::vec3(0, 0, m_size.z / 2) + m_position;
		m_polygones_positions[3] = glm::vec3(0, 0, -m_size.z / 2) + m_position;
		m_polygones_positions[4] = glm::vec3(m_size.x / 2, 0, 0) + m_position;
		m_polygones_positions[5] = glm::vec3(-m_size.x / 2, 0, 0) + m_position;

		m_coliders[0].BottomLeftFront = (glm::vec3(-m_size.x / 2, -m_size.y / 2, -m_size.z / 2) + m_position);
		m_coliders[0].TopRightFront = (glm::vec3(m_size.x / 2, m_size.y / 2, -m_size.z / 2) + m_position);
		m_coliders[0].TopLeftBack = (glm::vec3(-m_size.x / 2, m_size.y / 2, m_size.z / 2) + m_position);
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