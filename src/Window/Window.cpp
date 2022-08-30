#include "Window.hpp"
#include "../RenderEngine/OpenGL/Renderer.hpp"

#include <iostream>
#include <memory>

#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>  
#include <glm/gtc/matrix_transform.hpp>

namespace Game {

    static bool s_GLFW_initialized = false;

    Window::Window(std::string title, const unsigned int width, const unsigned int height)
        : m_data({ std::move(title), width, height })
    {
        int resultCode = init();
    }

    Window::~Window()
    {
        shutdown();
    }

    void Window::LockCursor()
    {
        glfwSetCursorPos(m_pWindow, m_data.width / 2, m_data.height / 2);
    }

    int Window::init()
    {
        if (!s_GLFW_initialized)
        {
            if (!glfwInit())
            {
                return -1;
            }
            s_GLFW_initialized = true;
        }

        m_pWindow = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);
        if (!m_pWindow)
        {
            std::cout << "Can't create window\n";
            glfwTerminate();
            return -2;
        }
        glfwMakeContextCurrent(m_pWindow);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD", "\n";
            return -3;
        }

        glfwSetWindowUserPointer(m_pWindow, &m_data);

        glfwSetKeyCallback(m_pWindow,
            [](GLFWwindow* pWindow, int key, int scancode, int action, int mods)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));
                switch (action)
                {
                case GLFW_PRESS:
                {
                    EventKeyPressed event(static_cast<KeyCode>(key), false);
                    data.eventCallbackFn(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    EventKeyReleased event(static_cast<KeyCode>(key));
                    data.eventCallbackFn(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    EventKeyPressed event(static_cast<KeyCode>(key), true);
                    data.eventCallbackFn(event);
                    break;
                }
                }
            }
        );

        glfwSetWindowSizeCallback(m_pWindow,
            [](GLFWwindow* pWindow, int width, int height)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));
                data.width = width;
                data.height = height;

                EventWindowResize event(width, height);
                data.eventCallbackFn(event);
            }
        );

        glfwSetCursorPosCallback(m_pWindow,
            [](GLFWwindow* pWindow, double x, double y)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));

                EventMouseMoved event(x, y);
                data.eventCallbackFn(event);
            }
        );

        glfwSetWindowCloseCallback(m_pWindow,
            [](GLFWwindow* pWindow)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));

                EventWindowClose event;
                data.eventCallbackFn(event);
            }
        );

        glfwSetFramebufferSizeCallback(m_pWindow,
            [](GLFWwindow* pWindow, int width, int height)
            {
                const float aspect_ratio = 1.f / 1.f;
                unsigned int viewPortWidth = width;
                unsigned int viewPortHeight = height;
                unsigned int viewPortLeftOffset = 0;
                unsigned int viewPortBottomOffset = 0;

                if (static_cast<float>(width) / height > aspect_ratio)
                {
                    viewPortWidth = static_cast<unsigned int>(height * aspect_ratio);
                    viewPortLeftOffset = (width - viewPortWidth) / 2;
                }
                else
                {
                    viewPortHeight = static_cast<unsigned int>(width / aspect_ratio);
                    viewPortBottomOffset = (height - viewPortHeight) / 2;
                }

                RenderEngine::Renderer::setViewport(viewPortWidth, viewPortHeight, viewPortLeftOffset, viewPortBottomOffset);
            }
        );

        glfwSetMouseButtonCallback(m_pWindow,
            [](GLFWwindow* pWindow, int button, int action, int mods)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));
                double x_pos;
                double y_pos;
                glfwGetCursorPos(pWindow, &x_pos, &y_pos);
                switch (action)
                {
                case GLFW_PRESS:
                {
                    EventMouseButtonPressed event(static_cast<MouseButton>(button), x_pos, y_pos);
                    data.eventCallbackFn(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    EventMouseButtonReleased event(static_cast<MouseButton>(button), x_pos, y_pos);
                    data.eventCallbackFn(event);
                    break;
                }
                }
            }
        );

        return 0;
    }

    void Window::shutdown()
    {
        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
    }

    void Window::on_update()
    {
        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();
    }
}