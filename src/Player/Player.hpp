#pragma once

#include "Camera.hpp"

#include <glm/vec3.hpp>
#include <glm/ext/matrix_float4x4.hpp>

namespace Player
{
	class Player
	{
	public:
		Player(const glm::vec3& position = { 0, 0, 0 },
		       const glm::vec3& rotation = { 0, 0, 0 },
			   const Camera::ProjectionMode projection_mode = Camera::ProjectionMode::Perspective);

		void set_position(const glm::vec3& position);
		void set_rotation(const glm::vec3& rotation);
		void set_position_rotation(const glm::vec3& position, const glm::vec3& rotation);
		void set_projection_mode(const Camera::ProjectionMode projection_mode) { camera.set_projection_mode(projection_mode); }
		const glm::mat4& get_view_matrix() { return camera.get_view_matrix(); }
		const glm::mat4& get_projection_matrix() const { return camera.get_projection_matrix(); }

		glm::vec3& get_camera_position() { return camera.get_camera_position(); }
		glm::vec3& get_camera_rotation() { return camera.get_camera_rotation(); }

		glm::vec3& get_direction() { return camera.get_direction(); }
		glm::vec3& get_right()     { return camera.get_right();     }
		glm::vec3& get_up()        { return camera.get_up();        }

		const glm::vec3& getCurrentVelocity() const { return camera.getCurrentVelocity(); }

		const std::vector<Physics::AABB>& getColiders() const { return camera.getColiders(); };

		void update(float horizontalAngleRad, float verticalAngleRad);
	private:
		Camera camera;

		glm::vec3 m_position;
		glm::vec3 m_rotation;
	};
}