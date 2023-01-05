#pragma once

#include "Camera.hpp"
#include "Ray.hpp"

#include <string>
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
		void set_far_clip_plane(const float far) { camera.set_far_clip_plane(far); }
		void set_near_clip_plane(const float near) { camera.set_near_clip_plane(near); }
		void set_viewport_size(const float width, const float height) { camera.set_viewport_size(width, height); }
		void set_field_of_view(const float fov) { camera.set_field_of_view(fov); }

		const glm::mat4& get_view_matrix() { return camera.get_view_matrix(); }
		const glm::mat4& get_projection_matrix() const { return camera.get_projection_matrix(); }

		glm::vec3& get_position() { return camera.get_position(); }
		glm::vec3& get_rotation() { return camera.get_rotation(); }

		glm::vec3& get_direction() { return camera.get_direction(); }
		glm::vec3& get_right()     { return camera.get_right();     }
		glm::vec3& get_up()        { return camera.get_up();        }

		const float get_far_clip_plane() const { return camera.get_far_clip_plane(); }
		const float get_near_clip_plane() const { return camera.get_near_clip_plane(); }
		const float get_field_of_view() const { return camera.get_field_of_view(); }

		const glm::vec3& getCurrentVelocity() const { return camera.getCurrentVelocity(); }

		const std::vector<Physics::AABB>& getColiders() const { return camera.getColiders(); };

		void update(float horizontalAngleRad, float verticalAngleRad);
	private:
		Camera camera;
		Ray ray;

		glm::vec3 m_position;
		glm::vec3 m_rotation;
		float  m_speed = 0.5f;

		std::string current_item_type = "Grass";
	};
}