#include <iostream>
#include <memory>
#include <chrono>

#include "Game/Application.hpp"
#include <glm/vec2.hpp>

class MyApp : public Game::Application
{
    int frame = 1;
    void on_update(uint64_t duration) override
    {
        if (Game::Game::m_keys_pressed[static_cast<size_t>(Game::KeyCode::KEY_ESCAPE)])
        {
            openMenu();
        }
        std::cout << " FPS: " << 1000000000 / duration << std::endl;
        frame++;
  }
};

int main(int argc, char** argv)
{
    auto myApp = std::make_unique<MyApp>();
    int returnCode = myApp->start(1024, 1024, "Minecraft", argv);

    return returnCode;
}