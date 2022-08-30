#include "Application.hpp"
#include "../Window/Window.hpp"
#include "../RenderEngine/OpenGL/ShaderProgram.hpp"
#include "../RenderEngine/OpenGL/Texture2D.hpp"
#include "../RenderEngine/OpenGL/Renderer.hpp"
#include "../RenderEngine/OpenGL/Polygon2D.hpp"
#include "../RenderEngine/OpenGL/Animated_Polygon2D.hpp"
#include "Renderer/ChunkRenderer.hpp"
#include "../Events/Keys.hpp"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <chrono>

namespace Game {
    glm::ivec2 g_windowSize(512, 512);

    Game m_game(g_windowSize);

    bool Game::m_keys_pressed[static_cast<size_t>(KeyCode::KEY_LAST)] = {};
    bool Game::m_mouse_buttons_pressed[static_cast<size_t>(MouseButton::MOUSE_BUTTON_LAST)] = {};

    Application::Application() {

    }

    Application::~Application() {

    }

    void Application::openMenu()
    {
        m_game.m_eCurrentGameState = Game::EGameState::StartScreen;
    }

    int Application::start(unsigned int window_width, unsigned int window_height, const char* title, char** argv) {
        m_pWindow = std::make_unique<Window>(title, window_width, window_height);
        ResourceManager::setExecutablePath(argv[0]);

        m_event_dispatcher.add_event_listener<EventKeyPressed>(
            [&](EventKeyPressed& event)
            {
                Game::m_keys_pressed[static_cast<size_t>(event.key_code)] = true;
            }
        );

        m_event_dispatcher.add_event_listener<EventKeyReleased>(
            [&](EventKeyReleased& event)
            {
                Game::m_keys_pressed[static_cast<size_t>(event.key_code)] = false;
            }
        );

        m_event_dispatcher.add_event_listener<EventWindowClose>(
            [&](EventWindowClose& event)
            {
                m_bCloseWindow = true;
            }
        );

        m_event_dispatcher.add_event_listener<EventMouseMoved>(
            [&](EventMouseMoved& event)
            {
                horizontalAngleRad = 0.005f * (m_pWindow->get_width()  / 2 - event.x);
                verticalAngleRad   = 0.005f * (m_pWindow->get_height() / 2 - event.y);
                xpos = (m_pWindow->get_width()  / 2 - event.x);
                ypos = (m_pWindow->get_height() / 2 - event.y);
                if (isLockCursor)
                {
                    m_pWindow->LockCursor();
                }
            }
        );

        m_event_dispatcher.add_event_listener<EventMouseButtonPressed>(
            [&](EventMouseButtonPressed& event)
            {
                Game::m_mouse_buttons_pressed[static_cast<size_t>(event.mouse_button)] = true;
            });

        m_event_dispatcher.add_event_listener<EventMouseButtonReleased>(
            [&](EventMouseButtonReleased& event)
            {
                Game::m_mouse_buttons_pressed[static_cast<size_t>(event.mouse_button)] = false;
            });

        m_pWindow->set_event_callback(
            [&](BaseEvent& event)
            {
                m_event_dispatcher.dispatch(event);
            }
        );

        ResourceManager::setExecutablePath(argv[0]);
        Physics::PhysicsEngine::init();
        m_game.init();

        auto lastTime = std::chrono::high_resolution_clock::now();

        RenderEngine::Renderer::setClearColor(0, 0.5, 1, 0);
        RenderEngine::Renderer::setDepth(true);

        player.set_position(glm::vec3(0.f, 2.f, 0.f));

        Physics::PhysicsEngine::addDynamicGameObject(&player);

        while (!m_bCloseWindow)
        {
            auto currentTime = std::chrono::high_resolution_clock::now();
            uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
            lastTime = currentTime;
            m_game.update(duration, xpos, ypos);
            Physics::PhysicsEngine::update(duration);

            if (m_game.m_eCurrentGameState == Game::EGameState::StartScreen)
            {
                perspective_camera = false;
                isLockCursor = false;
                player.set_position(glm::vec3(0.f, 2.f, 0.f));
                player.set_rotation(glm::vec3(0.f, 0.f, 0.f));
            }
            else if (m_game.m_eCurrentGameState == Game::EGameState::Game)
            {
                perspective_camera = true;
                isLockCursor = true;
                on_update(duration);
                player.update(horizontalAngleRad, verticalAngleRad);
            }

            RenderEngine::Renderer::clear();
            player.set_projection_mode(perspective_camera ? Player::Camera::ProjectionMode::Perspective : Player::Camera::ProjectionMode::Orthographic);
            m_game.render(player.get_projection_matrix() * player.get_view_matrix());

            m_pWindow->on_update();
        }
        ResourceManager::unloadAllResources();

        m_pWindow = nullptr;

        return 0;
    }

    Game::Game(const glm::ivec2& windowSize)
        : m_eCurrentGameState(EGameState::StartScreen)
        , m_windowSize(windowSize)
    {
    }

    Game::~Game()
    {

    }

    bool Game::init()
    {
        auto pPolygonShaderProgram = ResourceManager::loadShader("PolygonShader", "res/shaders/vPolygon.txt", "res/shaders/fPolygon.txt");
        if (!pPolygonShaderProgram)
        {
            std::cerr << "Can't create shader program: " << "PolygonShader" << std::endl;
            return false;
        }

        std::vector<std::string> BlocksSubTexturesNames = {
                                                     "Grass_Top",
                                                     "Grass_Left",
                                                     "Dirt",
                                                     "Coblestone",
                                                     "Wood_Top",
                                                     "Wood_Left"
        };

        std::vector<std::string> StartScreenSubTexturesNames = {
                                                     "StartScreen"
        };

        std::vector<std::string> ButtonsSubTexturesNames = {
                                                     "New_Game"
        };

        auto pTextureAtlas = ResourceManager::loadTextureAtlas("BlockTextureAtlas", "res/textures/Blocks.png", std::move(BlocksSubTexturesNames), 64, 64);
        auto pStartScreenTextureAtlas = ResourceManager::loadTextureAtlas("StartScreenTextureAtlas", "res/textures/StartScreen.png", std::move(StartScreenSubTexturesNames), 1900, 1600);
        auto pButtonsTextureAtlas = ResourceManager::loadTextureAtlas("ButtonsTextureAtlas", "res/textures/Buttons.png", std::move(ButtonsSubTexturesNames), 1200, 300);

        m_pStartScreen = std::make_unique<GameStates::StartScreen>(pStartScreenTextureAtlas, "StartScreen", pPolygonShaderProgram);
        m_pButton2D = std::make_unique<Button2D>(pButtonsTextureAtlas, "New_Game", pPolygonShaderProgram);
        Renderer::ChunkRenderer::setTextureAtlas(pTextureAtlas);
        Renderer::ChunkRenderer::setShaderProgram(pPolygonShaderProgram);
        Renderer::ChunkRenderer::generate_world();

        pPolygonShaderProgram->bind();
        pPolygonShaderProgram->setInt("tex", 0);

        return true;
    }

    void Game::render(glm::mat4 projectionMat)
    {
        ResourceManager::getShader("PolygonShader")->setMatrix4("projectionMat", projectionMat);
        ResourceManager::getShader("PolygonShader")->bind();
        switch (m_eCurrentGameState)
        {
            case EGameState::StartScreen:
            {
                m_pStartScreen->render();
                m_pButton2D->render();
                break;
            }
            case EGameState::Game:
            {
                Renderer::ChunkRenderer::render();
                break;
            }
        }
    }

    void Game::update(const uint64_t delta, double x_pos, double y_pos)
    {
        switch (m_eCurrentGameState)
        {
            case EGameState::StartScreen:
            {
                if (m_pButton2D->isPressed(x_pos, y_pos) && Game::Game::m_mouse_buttons_pressed[static_cast<size_t>(MouseButton::MOUSE_BUTTON_LEFT)])
                {
                    m_eCurrentGameState = EGameState::Game;
                }
                break;
            }
            case EGameState::Game:
            {
                //ChunkRenderer->update();
                break;
            }
        }
    }
}