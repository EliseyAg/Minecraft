#include <iostream>
#include <memory>
#include "Game/Application.hpp"
#include "Resources/ResourceManager.hpp"

#include <glm/vec2.hpp>

#define PI 3.14

class MyApp : public Game::Application
{
    void on_update() override
    {
        bool move_camera = false;
        glm::vec3 movement_delta{ 0, 0, 0 };
        glm::vec3 rotation_delta{ 0, 0, 0 };

        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_W)])
        {
            movement_delta.x +=  0.05f;
            move_camera = true;
        }                                                                    
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_S)])
        {                                                                    
            movement_delta.x += -0.05f;
            move_camera = true;
        }                                                                    
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_A)])
        {                                                                    
            movement_delta.y += -0.05f;
            move_camera = true;
        }                                                                    
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_D)])
        {                                                                    
            movement_delta.y +=  0.05f;
            move_camera = true;
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_E)])
        {
            movement_delta.z +=  0.05f;
            move_camera = true;
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_Q)])
        {
            movement_delta.z += -0.05f;
            move_camera = true;
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_UP)])
        {
            rotation_delta.x += -0.5f;
            move_camera = true;
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_DOWN)])
        {
            rotation_delta.x +=  0.5f;
            move_camera = true;
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_RIGHT)])
        {
            rotation_delta.y += -0.5f;
            move_camera = true;
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_LEFT)])
        {
            rotation_delta.y +=  0.5f;
            move_camera = true;
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_P)])
        {
            rotation_delta.z += -0.5f;
            move_camera = true;
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_O)])
        {
            rotation_delta.z +=  0.5f;
            move_camera = true;
        }
        if (move_camera)
        {
            camera.add_movement_and_rotatition(movement_delta, rotation_delta);
        }
    }
};

int main(int argc, char** argv)
{
    auto myApp = std::make_unique<MyApp>();
    int returnCode = myApp->start(512, 512, "Minecraft", argv);

    return returnCode;
}