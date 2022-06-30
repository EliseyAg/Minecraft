#include <iostream>
#include <memory>
#include "Game/Application.hpp"
#include "Resources/ResourceManager.hpp"
#include "Events/Input.hpp"

#include <glm/vec2.hpp>

#define PI 3.14

class MyApp : public Game::Application
{
    void on_update() override {
        if (Game::Input::IsKeyPressed(Game::KeyCode::KEY_W))
        {
            camera_position[2] +=  cos((camera_rotation[1] * PI) / 180) * -0.005f;
            camera_position[0] +=  sin((camera_rotation[1] * PI) / 180) * -0.005f;
        }                                                                    
        if (Game::Input::IsKeyPressed(Game::KeyCode::KEY_S))                 
        {                                                                    
            camera_position[2] +=  cos((camera_rotation[1] * PI) / 180) *  0.005f;
            camera_position[0] +=  sin((camera_rotation[1] * PI) / 180) *  0.005f;
        }                                                                    
        if (Game::Input::IsKeyPressed(Game::KeyCode::KEY_A))                 
        {                                                                    
            camera_position[2] += -sin((camera_rotation[1] * PI) / 180) * -0.005f;
            camera_position[0] +=  cos((camera_rotation[1] * PI) / 180) * -0.005f;
        }                                                                    
        if (Game::Input::IsKeyPressed(Game::KeyCode::KEY_D))                 
        {                                                                    
            camera_position[2] += -sin((camera_rotation[1] * PI) / 180) *  0.005f;
            camera_position[0] +=  cos((camera_rotation[1] * PI) / 180) *  0.005f;
        }
        if (Game::Input::IsKeyPressed(Game::KeyCode::KEY_E))
        {
            camera_position[1] += 0.005f;
        }
        if (Game::Input::IsKeyPressed(Game::KeyCode::KEY_Q))
        {
            camera_position[1] -= 0.005f;
        }

        if (Game::Input::IsKeyPressed(Game::KeyCode::KEY_UP))
        {
            camera_rotation[0] += 0.25f;
        }
        if (Game::Input::IsKeyPressed(Game::KeyCode::KEY_DOWN))
        {
            camera_rotation[0] -= 0.25f;
        }
        if (Game::Input::IsKeyPressed(Game::KeyCode::KEY_RIGHT))
        {
            camera_rotation[1] -= 0.25f;
        }
        if (Game::Input::IsKeyPressed(Game::KeyCode::KEY_LEFT))
        {
            camera_rotation[1] += 0.25f;
        }
        if (Game::Input::IsKeyPressed(Game::KeyCode::KEY_R))
        {
            camera_position[0] = 0.f;
            camera_position[1] = 0.f;
            camera_position[2] = 0.f;
        }
        Game::Input::setFalse();
        std::cout << "x: " << camera_position[0] << " z: " << camera_position[2] << std::endl;
    }
};

int main(int argc, char** argv)
{
    auto myApp = std::make_unique<MyApp>();
    int returnCode = myApp->start(512, 512, "Minecraft", argv);

    return returnCode;
}