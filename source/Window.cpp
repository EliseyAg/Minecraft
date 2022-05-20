#include "Window.hpp"
#include "Event.hpp"
#include "Renderer/ShaderProgram.hpp"
#include "Renderer/IndexBuffer.hpp"
#include "Renderer/VertexBuffer.hpp"
#include "Renderer/VertexArray.hpp"

#include <iostream>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Game {

    static bool s_GLFW_initialized = false;

    GLfloat positions_colors[] = {
       -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
       -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f
    };

    GLuint indices[] = {
        0, 1, 2, 3, 2, 1
    };

    const char* vertex_shader =
    R"(
        #version 460
        layout(location = 0) in vec3 vertex_position;
        layout(location = 1) in vec3 vertex_color;
        out vec3 color;
        void main() {
           color = vertex_color;
           gl_Position = vec4(vertex_position, 1.0);
        }
    )";

    const char* fragment_shader =
    R"(
        #version 460
        in vec3 color;
        out vec4 frag_color;
        void main() {
           frag_color = vec4(color, 1.0);
        }
    )";

    std::unique_ptr<ShaderProgram> p_shader_program;
    std::unique_ptr<VertexBuffer> p_positions_colors_vbo;
    std::unique_ptr<IndexBuffer> p_index_buffer;
    std::unique_ptr<VertexArray> p_vao;

    Window::Window(std::string title, const unsigned int width, const unsigned int height)
        : m_data({ std::move(title), width, height })
    {
        int resultCode = init();
    }

    Window::~Window()
    {
        shutdown();
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
            std::cout << "Can't create window {0} with size {1}x{2}", m_data.title, m_data.width, m_data.height, "\n";
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
                glViewport(0, 0, width, height);
            }
        );

        p_shader_program = std::make_unique<ShaderProgram>(vertex_shader, fragment_shader);
        if (!p_shader_program->isCompiled())
        {
            return false;
        }

        BufferLayout buffer_layout_2vec3
        {
            ShaderDataType::Float3,
            ShaderDataType::Float3
        };

        p_vao = std::make_unique<VertexArray>();
        p_positions_colors_vbo = std::make_unique<VertexBuffer>(positions_colors, sizeof(positions_colors), buffer_layout_2vec3);
        p_index_buffer = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(GLuint));

        p_vao->add_vertex_buffer(*p_positions_colors_vbo);
        p_vao->set_index_buffer(*p_index_buffer);

        return 0;
    }

    void Window::shutdown()
    {
        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
    }

    void Window::on_update()
    {
        glClearColor(0, 0.5, 1, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        p_shader_program->bind();
        p_vao->bind();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(p_vao->get_indices_count()), GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();
    }

}