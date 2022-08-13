#pragma once

#include "../Events/Event.hpp"
#include "../Resources/ResourceManager.hpp"
#include "../Player/Camera.hpp"
#include "GameStates/StartScreen.hpp"
#include "Renderer/ChunkRenderer.hpp"

#include <memory>
#include <array>
#include <glm/vec2.hpp>

namespace Game {

    class Application
    {
    public:
        Application();
        virtual ~Application();

        Application(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(const Application&) = delete;
        Application& operator=(Application&&) = delete;

        virtual int start(unsigned int window_width, unsigned int window_height, const char* title, char** argv);

        virtual void on_update(uint64_t duration, float horizontalAngleRad, float verticalAngleRad) {};
        virtual void CloseWindow() { m_bCloseWindow = true; };

        bool perspective_camera = true;
        Player::Camera camera{ glm::vec3(0.f, 2.f, 0.f), glm::vec3(0.f, 0.f, 0.f) };

        bool isLockCursor = true;

    private:
        std::unique_ptr<class Window> m_pWindow;

        float horizontalAngleRad = 0;
        float verticalAngleRad   = 0;

        EventDispatcher m_event_dispatcher;
        bool m_bCloseWindow = false;
    };

    class Game {
    public:
        Game(const glm::ivec2& windowSize);
        ~Game();

        void render(glm::mat4 projectionMat);
        void update(const uint64_t delta);
        bool init();

        static bool m_keys_pressed[static_cast<size_t>(KeyCode::KEY_LAST)];
    private:
        enum class EGameState {
            Game,
            StartScreen,
            Menu,
            Pause
        };

        glm::ivec2 m_windowSize;
        EGameState m_eCurrentGameState;

        std::unique_ptr<GameStates::StartScreen> m_pStartScreen;
    };

}