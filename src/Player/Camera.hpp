#pragma once

#include <glm/vec3.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <vector>

namespace Physics
{
	class AABB;
}

namespace Player
{
	class Camera {
	public:
		enum class ProjectionMode
		{
			Perspective,
			Orthographic
		};

		Camera(const glm::vec3& position = { 0, 0, 0 },
			   const glm::vec3& rotation = { 0, 0, 0 },
			   const ProjectionMode projection_mode = ProjectionMode::Perspective);

		void set_position(const glm::vec3& position);
		void set_rotation(const glm::vec3& rotation);
		void set_position_rotation(const glm::vec3& position, const glm::vec3& rotation);
		void set_projection_mode(const ProjectionMode projection_mode);
		const glm::mat4& get_view_matrix();
		const glm::mat4& get_projection_matrix() const { return m_projection_matrix; }

		void move_forward(const float delta);
		void move_right(const float delta);
		void move_up(const float delta);

		glm::vec3& get_camera_position() { return m_position; }
		glm::vec3& get_camera_rotation() { return m_rotation; }

		glm::vec3& get_direction() { return m_direction; }
		glm::vec3& get_right() { return m_right; }
		glm::vec3& get_up() { return m_up; }

		void add_movement_and_rotation(const glm::vec3& movement_delta,
			const glm::vec3& rotation_delta);

		const glm::vec3& getCurrentVelocity() const {	return m_velocity; }

		const std::vector<Physics::AABB>& getColiders() const { return m_coliders; };

	private:
		void update_view_matrix();
		void update_projection_matrix();

		glm::vec3 m_position;
		glm::vec3 m_rotation;
		ProjectionMode m_projection_mode;

		glm::vec3 m_direction;
		glm::vec3 m_right;
		glm::vec3 m_up;

		static constexpr glm::vec3 s_world_up{ 0.f, 1.f, 0.f };
		static constexpr glm::vec3 s_world_right{ 1.f, 0.f, 0.f };
		static constexpr glm::vec3 s_world_forward{ 0.f, 0.f, -1.f };

		glm::mat4 m_view_matrix;
		glm::mat4 m_projection_matrix;

		glm::vec3 m_velocity;

		bool m_update_view_matrix = false;

		std::vector<Physics::AABB> m_coliders;
	};
}