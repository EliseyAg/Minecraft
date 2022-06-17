#include "Application.hpp"
#include "Window.hpp"
#include "Renderer/ShaderProgram.hpp"
#include "Renderer/Texture2D.hpp"
#include "Polygon2D.hpp"
#include "Events/Input.hpp"
#include "Animated_Polygon2D.hpp"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <chrono>

namespace Game {
    glm::ivec2 g_windowSize(512, 512);

    Game m_game(g_windowSize);

    std::unique_ptr<Cube> cube;

    Application::Application() {

    }

    Application::~Application() {

    }

    int Application::start(unsigned int window_width, unsigned int window_height, const char* title, char** argv) {
        m_pWindow = std::make_unique<Window>(title, window_width, window_height, argv);
        ResourceManager::setExecutablePath(argv[0]);

        m_event_dispatcher.add_event_listener<EventKeyPressed>(
            [&](EventKeyPressed& event)
            {
                if (event.key_code <= KeyCode::KEY_Z)
                {
                    if (event.repeated)
                    {
                        //std::cout << "Key pressed, repeated: " << static_cast<char>(event.key_code) << std::endl;
                    }
                    else
                    {
                        //std::cout << "Key pressed: " << static_cast<char>(event.key_code) << std::endl;
                    }
                }
                Input::PressKey(event.key_code);
            });

        m_event_dispatcher.add_event_listener<EventKeyReleased>(
            [&](EventKeyReleased& event)
            {
                if (event.key_code <= KeyCode::KEY_Z)
                {
                    //std::cout << "Key released: " << static_cast<char>(event.key_code) << std::endl;
                }
                Input::ReleaseKey(event.key_code);
            });

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
            camera.set_position_rotation(glm::vec3(camera_position[0], camera_position[1], camera_position[2]),
                                         glm::vec3(camera_rotation[0], camera_rotation[1], camera_rotation[2]));
            camera.set_projection_mode(perspective_camera ? Player::Camera::ProjectionMode::Perspective : Player::Camera::ProjectionMode::Orthographic);
            m_game.render(camera.get_projection_matrix() * camera.get_view_matrix(), glm::vec3(camera_position[0], camera_position[1], camera_position[2]));

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

        auto pAnimatedPolygon1 = ResourceManager::loadAnimatedPolygon("NewAnimatedPolygon1", "DefaultTextureAtlas", "PolygonShader", 4, 4, "Grass_Top");
        auto pAnimatedPolygon2 = ResourceManager::loadAnimatedPolygon("NewAnimatedPolygon2", "DefaultTextureAtlas", "PolygonShader", 4, 4, "Grass_Left");
        pAnimatedPolygon1->setPosition(glm::vec3(0, 0, 0));
        pAnimatedPolygon1->setRotation(glm::vec4(90, 0, 0, 0));
        pAnimatedPolygon2->setPosition(glm::vec3(0, 0, 0));
        pAnimatedPolygon2->setRotation(glm::vec4(0, 0, 0, 0));
        std::vector<std::pair<std::string, uint64_t>> grassState11;
        grassState11.emplace_back(std::make_pair<std::string, uint64_t>("Grass_Top", 1000000000));

        std::vector<std::pair<std::string, uint64_t>> grassState12;
        grassState12.emplace_back(std::make_pair<std::string, uint64_t>("Grass_Top", 1000000000));
        grassState12.emplace_back(std::make_pair<std::string, uint64_t>("Grass_Left", 1000000000));
        grassState12.emplace_back(std::make_pair<std::string, uint64_t>("Grass_Bottom", 1000000000));

        std::vector<std::pair<std::string, uint64_t>> grassState21;
        grassState21.emplace_back(std::make_pair<std::string, uint64_t>("Grass_Left", 1000000000));

        std::vector<std::pair<std::string, uint64_t>> grassState22;
        grassState22.emplace_back(std::make_pair<std::string, uint64_t>("Grass_Top", 1000000000));
        grassState22.emplace_back(std::make_pair<std::string, uint64_t>("Grass_Left", 1000000000));
        grassState22.emplace_back(std::make_pair<std::string, uint64_t>("Grass_Bottom", 1000000000));

        pAnimatedPolygon1->insertState("grassState11", std::move(grassState11));
        pAnimatedPolygon1->insertState("grassState12", std::move(grassState12));

        pAnimatedPolygon1->setState("grassState11");

        pAnimatedPolygon2->insertState("grassState21", std::move(grassState21));
        pAnimatedPolygon2->insertState("grassState22", std::move(grassState22));

        pAnimatedPolygon2->setState("grassState21");

        cube = std::make_unique<Cube>(pTextureAtlas, "Grass_Top", pPolygonShaderProgram, glm::vec3(0, 0, 0), glm::vec3(4, 4, 4));

        pDefaultShaderProgram->bind();
        pDefaultShaderProgram->setInt("tex", 0);

        pPolygonShaderProgram->bind();
        pPolygonShaderProgram->setInt("tex", 0);

        return true;
    }

    void Game::render(glm::mat4 projectionMat, glm::vec3& camera_position)
    {
        ResourceManager::getShader("PolygonShader")->setMatrix4("projectionMat", projectionMat);
        ResourceManager::getShader("PolygonShader")->bind();
        cube->render(camera_position);
    }

    void Game::update(const uint64_t delta)
    {
        ResourceManager::getAnimatedPolygon("NewAnimatedPolygon1")->update(delta);
        ResourceManager::getAnimatedPolygon("NewAnimatedPolygon2")->update(delta);
    }
}