#pragma once

#include "../Events/Event.hpp"
#include "../Resources/ResourceManager.hpp"
#include "GameStates/StartScreen.hpp"
#include "GameObjects/Button2D.hpp"
#include "../Physics/PhysicsEngine.hpp"
#include "../Player/Player.hpp"

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

        virtual void on_update(uint64_t duration) {};
        virtual void CloseWindow() { m_bCloseWindow = true; };

        void openMenu();

        bool perspective_camera = false;
        Player::Player player;

        bool isLockCursor = true;

    private:
        std::unique_ptr<class Window> m_pWindow;

        float horizontalAngleRad = 0;
        float verticalAngleRad   = 0;

        EventDispatcher m_event_dispatcher;
        bool m_bCloseWindow = false;

        int xpos;
        int ypos;
    };

    class Game {
    public:
        Game(const glm::ivec2& windowSize);
        ~Game();

        void render(glm::mat4 projectionMat, const glm::vec3& camera_position, const glm::vec3& camera_rotation);
        void update(const uint64_t delta, double x_pos, double y_pos);
        bool init();

        static bool m_keys_pressed[static_cast<size_t>(KeyCode::KEY_LAST)];
        static bool m_mouse_buttons_pressed[static_cast<size_t>(MouseButton::MOUSE_BUTTON_LAST)];

        enum class EGameState {
            Game,
            StartScreen,
            Menu,
            Pause
        };

        EGameState m_eCurrentGameState;
    private:
        glm::ivec2 m_windowSize;

        std::unique_ptr<GameStates::StartScreen> m_pStartScreen;
        std::unique_ptr<Button2D> m_pButton2D;
    };

}