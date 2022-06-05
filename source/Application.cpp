#include "Application.hpp"
#include "Window.hpp"
#include "Event.hpp"

#include <iostream>

namespace Game {

    Application::Application() {

    }

    Application::~Application() {

    }

    int Application::start(unsigned int window_width, unsigned int window_height, const char* title, char** argv) {
        m_pWindow = std::make_unique<Window>(title, window_width, window_height, argv);

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

        while (!m_bCloseWindow)
        {
            m_pWindow->on_update();
            on_update();
        }
        m_pWindow = nullptr;

        return 0;
    }
}