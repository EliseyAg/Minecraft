#include "Player.hpp"
#include "../Game/Application.hpp"
#include "../Game/Renderer/ChunkRenderer.hpp"

#include <iostream>
#include <cmath>

namespace Player
{
    double angle(const glm::vec3& a, const glm::vec3& b)
    {
        double sc_mult = a.x * b.x + a.y * b.y + a.z * b.z;
        double len_a = sqrt((a.x) * (a.x) + (a.y) * (a.y) + (a.z) * (a.z));
        double len_b = sqrt((b.x) * (b.x) + (b.y) * (b.y) + (b.z) * (b.z));
        return glm::degrees(glm::acos(sc_mult / (len_a * len_b)));
    }

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
        if (Game::Game::m_mouse_buttons_pressed[static_cast<size_t>(Game::MouseButton::MOUSE_BUTTON_RIGHT)])
        {
            ray.setPosition(m_position);
            ray.setDirection(m_rotation);
            glm::vec3 r_p = ray.getPosition();
            if (Renderer::ChunkRenderer::getObjectsInArea(r_p, r_p, r_p))
            {
                r_p = Renderer::ChunkRenderer::getObjectsInArea();
                //Renderer::ChunkRenderer::deleteBlock(r_p);
            }
        }
        if (Game::Game::m_mouse_buttons_pressed[static_cast<size_t>(Game::MouseButton::MOUSE_BUTTON_LEFT)])
        {
            ray.setPosition(m_position);
            ray.setDirection(m_rotation);
            glm::vec3 r_p = ray.getPosition();
            if (Renderer::ChunkRenderer::getObjectsInArea(r_p, r_p, r_p))
            {
                glm::vec3 b = glm::vec3(0.f);
                glm::vec3 ir_p = Renderer::ChunkRenderer::getObjectsInArea();
                float min_a = 360;
                float a;
                a = angle(r_p, glm::vec3(0.f, 1.f, 0.f) + ir_p);
                if (a < min_a)
                {
                    min_a = a;
                    b = glm::vec3(0.f, 1.f, 0.f);
                }
                a = angle(r_p, glm::vec3(0.f, -1.f, 0.f) + ir_p);
                if (a < min_a)
                {
                    min_a = a;
                    b = glm::vec3(0.f, -1.f, 0.f);
                }
                a = angle(r_p, glm::vec3(1.f, 0.f, 0.f) + ir_p);
                if (a < min_a)
                {
                    min_a = a;
                    b = glm::vec3(1.f, 0.f, 0.f);
                }
                a = angle(r_p, glm::vec3(-1.f, 0.f, 0.f) + ir_p);
                if (a < min_a)
                {
                    min_a = a;
                    b = glm::vec3(-1.f, 0.f, 0.f);
                }
                a = angle(r_p, glm::vec3(0.f, 0.f, 1.f) + ir_p);
                if (a < min_a)
                {
                    min_a = a;
                    b = glm::vec3(0.f, 0.f, 1.f);
                }
                a = angle(r_p, glm::vec3(0.f, 0.f, -1.f) + ir_p);
                if (a < min_a)
                {
                    min_a = a;
                    b = glm::vec3(0.f, 0.f, -1.f);
                }
                std::cout << ir_p.x << " " << ir_p.y << " " << ir_p.z << std::endl;
                //Renderer::ChunkRenderer::placeBlock(b + ir_p, current_item_type);
            }
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_1)])
        {
            current_item_type = "Grass";
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_2)])
        {
            current_item_type = "Dirt";
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_3)])
        {
            current_item_type = "Coblestone";
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_4)])
        {
            current_item_type = "Wood";
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_5)])
        {
            current_item_type = "Leaves";
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_6)])
        {
            current_item_type = "Grass";
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_7)])
        {
            current_item_type = "Grass";
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_8)])
        {
            current_item_type = "Grass";
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_9)])
        {
            current_item_type = "Grass";
        }

        rotation_delta += glm::vec3(verticalAngleRad * 180 / 3.14, horizontalAngleRad * 180 / 3.14, 0);
        camera.add_movement_and_rotation(movement_delta, rotation_delta);
        m_position = camera.get_camera_position();
        m_rotation = camera.get_camera_rotation();
	}
}