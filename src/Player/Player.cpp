#include "Player.hpp"
#include "../Game/Application.hpp"

namespace Player
{
	Player::Player(const glm::vec3& position,
		           const glm::vec3& rotation,
		           const Camera::ProjectionMode projection_mode)
		           : m_position(position)
		           , m_rotation(rotation)
	{
		camera.set_projection_mode(projection_mode);
	}

	void Player::set_position(const glm::vec3& position) 
	{
		m_position = position;
		camera.set_position(m_position);
	}

	void Player::set_rotation(const glm::vec3& rotation)
	{
		m_rotation = rotation;
		camera.set_rotation(m_rotation);
	}

	void Player::set_position_rotation(const glm::vec3& position, const glm::vec3& rotation)
	{
		m_position = position;
		m_rotation = rotation;
		camera.set_position(m_position);
		camera.set_rotation(m_rotation);
	}

	void Player::update(float horizontalAngleRad, float verticalAngleRad)
	{
        glm::vec3 movement_delta{ 0, 0, 0 };
        glm::vec3 rotation_delta{ 0, 0, 0 };

        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_W)])
        {
            movement_delta.x +=  0.05f;
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_S)])
        {
            movement_delta.x += -0.05f;
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_A)])
        {
            movement_delta.y += -0.05f;
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_D)])
        {
            movement_delta.y +=  0.05f;
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_E)])
        {
            movement_delta.z +=  0.05f;
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_Q)])
        {
            movement_delta.z += -0.05f;
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_UP)])
        {
            rotation_delta.x +=  0.5f;
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_DOWN)])
        {
            rotation_delta.x += -0.5f;
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_RIGHT)])
        {
            rotation_delta.y += -0.5f;
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_LEFT)])
        {
            rotation_delta.y +=  0.5f;
        }
        rotation_delta += glm::vec3(verticalAngleRad * 180 / 3.14, horizontalAngleRad * 180 / 3.14, 0);
        camera.add_movement_and_rotation(movement_delta, rotation_delta);
	}
}