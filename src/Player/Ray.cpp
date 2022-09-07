#include "Ray.hpp"
#include "../Game/Renderer/ChunkRenderer.hpp"

#include <cmath>
#include <glm/trigonometric.hpp>

namespace Player
{
	glm::vec3& Ray::getPosition()
	{
		glm::vec3 pos = ro;
		float yaw = glm::radians(rd.y + 90.f);
		float pitch = glm::radians(rd.x);
		for (double l = 0; l < MAX_DIST; l++)
		{
			pos.x += glm::cos(yaw);
			pos.z -= glm::sin(yaw);
			pos.y += glm::tan(pitch);
			if (Renderer::ChunkRenderer::getObjectsInArea(pos, pos, pos))
			{
				return pos;
			}
		}
		return pos;
	}
}