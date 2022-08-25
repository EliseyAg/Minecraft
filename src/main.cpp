#include <iostream>
#include <memory>
#include <chrono>

#include "Game/Application.hpp"
#include <glm/vec2.hpp>

class MyApp : public Game::Application
{
    int frame = 1;
    void on_update(uint64_t duration, float horizontalAngleRad, float verticalAngleRad) override
    {
        glm::vec3 movement_delta{ 0, 0, 0 };
        glm::vec3 rotation_delta{ 0, 0, 0 };

        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_W)])
        {
            movement_delta.x +=  0.05f * duration / 10000000;
        }                                                                    
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_S)])
        {                                                                    
            movement_delta.x += -0.05f * duration / 10000000;
        }                                                                    
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_A)])
        {                                                                    
            movement_delta.y += -0.05f * duration / 10000000;
        }                                                                    
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_D)])
        {                                                                    
            movement_delta.y +=  0.05f * duration / 10000000;
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_E)])
        {
            movement_delta.z +=  0.05f * duration / 10000000;
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_Q)])
        {
            movement_delta.z += -0.05f * duration / 10000000;
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_UP)])
        {
            rotation_delta.x += -0.5f * duration / 10000000;
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_DOWN)])
        {
            rotation_delta.x +=  0.5f * duration / 10000000;
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_RIGHT)])
        {
            rotation_delta.y += -0.5f * duration / 10000000;
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_LEFT)])
        {
            rotation_delta.y +=  0.5f * duration / 10000000;
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_L)])
        {
            isLockCursor = !isLockCursor;
        }
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_ESCAPE)])
        {
            CloseWindow();
        }
        rotation_delta = glm::vec3(verticalAngleRad * 180 / 3.14, horizontalAngleRad * 180 / 3.14, 0);
        camera.add_movement_and_rotation(movement_delta, rotation_delta);
        std::cout << "Coords:" << "x: " << camera.get_camera_position().x << " z: " << camera.get_camera_position().z << " FPS: " << 1000000000 / duration << std::endl;
        frame++;
    }
};

int main(int argc, char** argv)
{
    auto myApp = std::make_unique<MyApp>();
    int returnCode = myApp->start(1024, 1024, "Minecraft", argv);

    return returnCode;
}