#pragma once

#include "Event.hpp"
#include "Resources/ResourceManager.hpp"

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

        virtual void on_update() {};

    private:
        std::unique_ptr<class Window> m_pWindow;

        EventDispatcher m_event_dispatcher;
        bool m_bCloseWindow = false;
    };

    class Game {
    public:
        Game(const glm::ivec2& windowSize);
        ~Game();

        void render();
        void update(const uint64_t delta);
        bool init();

    private:
        std::array<bool, 349> m_keys;

        enum class EGameState {
            Active,
            Pause
        };

        glm::ivec2 m_windowSize;
        EGameState m_eCurrentGameState;
    };

}