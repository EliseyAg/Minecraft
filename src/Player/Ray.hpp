#pragma once

#include <glm/vec3.hpp>

namespace Player
{
	class Ray
	{
	public:
		Ray() = default;

		void setPosition (glm::vec3 position)  { ro = position; }
		void setDirection(glm::vec3 direction) { rd = direction; }

		glm::vec3& getPosition();
	private:
		glm::vec3 ro;
		glm::vec3 rd;

		int MAX_DIST = 4;
	};
}