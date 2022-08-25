#pragma once
#include "glm/vec3.hpp"
#include <unordered_set>
#include <memory>

namespace Player
{
	class Camera;
}

namespace Physics
{
	class AABB
	{
	public:
		AABB(const glm::vec3 _BottomLeftFront, const glm::vec3 _TopRightFront, const glm::vec3 _TopLeftBack) 
			: BottomLeftFront(_BottomLeftFront)
			, TopRightFront(_TopRightFront)
			, TopLeftBack(_TopLeftBack)
		{}

		glm::vec3 BottomLeftFront;
		glm::vec3 TopRightFront;
		glm::vec3 TopLeftBack;
		

	};

	class PhysicsEngine
	{
	public:
		~PhysicsEngine() = delete;
		PhysicsEngine() = delete;
		PhysicsEngine(const PhysicsEngine&) = delete;
		PhysicsEngine(PhysicsEngine&&) = delete;
		PhysicsEngine& operator=(const PhysicsEngine&) = delete;
		PhysicsEngine& operator=(PhysicsEngine&&) = delete;

		static void init();
		static void shutdown();

		static void update(const double delta);
		static void addDynamicGameObject(Player::Camera* pGameObject);

	private:
		static std::unordered_set<Player::Camera*> m_dynamicObjects;
	};
}