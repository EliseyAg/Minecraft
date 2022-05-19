#include <iostream>
#include <memory>
#include "Application.hpp"

class MyApp : public Game::Application
{
    virtual void on_update() override
    {
        //std::cout << "Update frame: " << frame++ << std::endl;
    }

    int frame = 0;
};

int main()
{
    auto myApp = std::make_unique<MyApp>();

    int returnCode = myApp->start(1200, 600, "Minecraft");

    std::cin.get();
    return returnCode;
}