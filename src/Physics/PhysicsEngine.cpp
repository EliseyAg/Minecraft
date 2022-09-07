#include "PhysicsEngine.hpp"
#include "../Game/GameObjects/Cube.hpp"
#include "../Player/Player.hpp"
#include "../Game/Renderer/ChunkRenderer.hpp"

namespace Physics
{
	std::unordered_set<Player::Player*> PhysicsEngine::m_dynamicObjects;

	void PhysicsEngine::init()
	{

	}

	void PhysicsEngine::shutdown()
	{
		m_dynamicObjects.clear();
	}

	void PhysicsEngine::update(const double delta)
	{
		for (auto& currentObject : m_dynamicObjects)
		{
			if (currentObject->getCurrentVelocity() != glm::vec3(0.f))
			{
				const auto newPosition = currentObject->get_camera_position()
					+ (currentObject->get_direction() * static_cast<float>(currentObject->getCurrentVelocity().x * delta / 10000000))
					+ (currentObject->get_right() * static_cast<float>(currentObject->getCurrentVelocity().y * delta / 10000000))
					+ (currentObject->get_up() * static_cast<float>(currentObject->getCurrentVelocity().z * delta / 10000000));
				const auto& colliders = currentObject->getColiders();
				if(!Renderer::ChunkRenderer::getObjectsInArea(newPosition + currentObject->getColiders()[0].BottomLeftFront, 
															  newPosition + currentObject->getColiders()[0].TopLeftBack, 
															  newPosition + currentObject->getColiders()[0].TopRightFront))
					currentObject->get_camera_position() = newPosition;
			}
		}
	}

	void PhysicsEngine::addDynamicGameObject(Player::Player* pGameObject)
	{
		m_dynamicObjects.insert(std::move(pGameObject));
	}
}