#pragma once

#include "Event.hpp"
#include "Renderer/ShaderProgram.hpp"
#include "Renderer/Texture2D.hpp"
#include "Polygon2D.hpp"
#include "Animated_Polygon2D.hpp"

#include <string>
#include <memory>

struct GLFWwindow;

namespace Game {

    class Window
    {
    public:
        using EventCallbackFn = std::function<void(BaseEvent&)>;

        Window(std::string title, const unsigned int width, const unsigned int height, char** argv);
        ~Window();

        Window(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) = delete;
        void on_update();
        unsigned int get_width() const { return m_data.width; }
        unsigned int get_height() const { return m_data.height; }
        void set_event_callback(const EventCallbackFn& callback)
        {
            m_data.eventCallbackFn = callback;
        }
    private:
        struct WindowData
        {
            std::string title;
            unsigned int width;
            unsigned int height;
            EventCallbackFn eventCallbackFn;
        };
        int init(char** argv);
        void shutdown();
        std::shared_ptr<ShaderProgram> pDefaultShaderProgram;
        std::shared_ptr<ShaderProgram> pPolygonShaderProgram;
        std::shared_ptr<Texture2D> tex;
        std::shared_ptr<Polygon2D> pPolygon;
        std::shared_ptr<Animated_Polygon2D> pAnimatedPolygon;
        GLFWwindow* m_pWindow = nullptr;
        WindowData m_data;
        GLuint vao;
    };
}