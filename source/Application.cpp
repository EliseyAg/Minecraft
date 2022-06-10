#include "Application.hpp"
#include "Window.hpp"
#include "Event.hpp"
#include "Renderer/ShaderProgram.hpp"
#include "Renderer/Texture2D.hpp"
#include "Polygon2D.hpp"
#include "Animated_Polygon2D.hpp"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <chrono>

namespace Game {
    glm::ivec2 g_windowSize(640, 480);

    Game m_game(g_windowSize);

    Application::Application() {

    }

    Application::~Application() {

    }

    int Application::start(unsigned int window_width, unsigned int window_height, const char* title, char** argv) {
        m_pWindow = std::make_unique<Window>(title, window_width, window_height, argv);
        ResourceManager::setExecutablePath(argv[0]);

        m_event_dispatcher.add_event_listener<EventWindowClose>(
            [&](EventWindowClose& event)
            {
                m_bCloseWindow = true;
            });

        m_pWindow->set_event_callback(
            [&](BaseEvent& event)
            {
                m_event_dispatcher.dispatch(event);
            }
        );

        ResourceManager::setExecutablePath(argv[0]);
        m_game.init();

        auto lastTime = std::chrono::high_resolution_clock::now();

        while (!m_bCloseWindow)
        {
            auto currentTime = std::chrono::high_resolution_clock::now();
            uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
            lastTime = currentTime;
            m_game.update(duration);

            glClearColor(0, 0.5, 1, 0);
            glClear(GL_COLOR_BUFFER_BIT);
            m_game.render();

            m_pWindow->on_update();
            on_update();
        }
        ResourceManager::unloadAllResources();

        m_pWindow = nullptr;

        return 0;
    }

    Game::Game(const glm::ivec2& windowSize)
        : m_eCurrentGameState(EGameState::Active)
        , m_windowSize(windowSize)
    {
        m_keys.fill(false);
    }

    Game::~Game()
    {

    }

    bool Game::init()
    {
        auto pDefaultShaderProgram = ResourceManager::loadShader("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
        if (!pDefaultShaderProgram)
        {
            std::cerr << "Can't create shader program: " << "DefaultShader" << std::endl;
            return false;
        }

        auto pPolygonShaderProgram = ResourceManager::loadShader("PolygonShader", "res/shaders/vPolygon.txt", "res/shaders/fPolygon.txt");
        if (!pPolygonShaderProgram)
        {
            std::cerr << "Can't create shader program: " << "PolygonShader" << std::endl;
            return false;
        }

        auto tex = ResourceManager::loadTexture("DefaultTexture", "res/textures/Blocks.png");

        std::vector<std::string> subTexturesNames = {
                                                     "Grass_Top",
                                                     "Grass_Left",
                                                     "Grass_Bottom"
        };

        auto pTextureAtlas = ResourceManager::loadTextureAtlas("DefaultTextureAtlas", "res/textures/Blocks.png", std::move(subTexturesNames), 64, 64);

        auto pAnimatedPolygon = ResourceManager::loadAnimatedPolygon("NewAnimatedPolygon", "DefaultTextureAtlas", "PolygonShader", 100, 100, "Grass_Top");
        pAnimatedPolygon->setSize(glm::vec2(100, 100));
        pAnimatedPolygon->setPosition(glm::vec2(100, 100));
        std::vector<std::pair<std::string, uint64_t>> grassState;
        grassState.emplace_back(std::make_pair<std::string, uint64_t>("Grass_Top", 1000000000));
        grassState.emplace_back(std::make_pair<std::string, uint64_t>("Grass_Left", 1000000000));
        grassState.emplace_back(std::make_pair<std::string, uint64_t>("Grass_Bottom", 1000000000));

        pAnimatedPolygon->insertState("grassState", std::move(grassState));

        pAnimatedPolygon->setState("grassState");

        pDefaultShaderProgram->bind();
        pDefaultShaderProgram->setInt("tex", 0);

        glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f);

        pDefaultShaderProgram->setMatrix4("projectionMat", projectionMatrix);

        pPolygonShaderProgram->bind();
        pPolygonShaderProgram->setInt("tex", 0);
        pPolygonShaderProgram->setMatrix4("projectionMat", projectionMatrix);

        return true;
    }

    void Game::render()
    {
        ResourceManager::getAnimatedPolygon("NewAnimatedPolygon")->render();
    }

    void Game::update(const uint64_t delta)
    {
        ResourceManager::getAnimatedPolygon("NewAnimatedPolygon")->update(delta);
    }
}