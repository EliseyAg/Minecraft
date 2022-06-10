#include <iostream>
#include <memory>
#include "Application.hpp"
#include "Resources/ResourceManager.hpp"

#include <glm/vec2.hpp>

class MyApp : public Game::Application
{
    void on_update() override {
    }
};

int main(int argc, char** argv)
{
    auto myApp = std::make_unique<MyApp>();

    int returnCode = myApp->start(640, 480, "Minecraft", argv);

    return returnCode;
}