#include "Window.hpp"
#include "Event.hpp"
#include "Renderer/ShaderProgram.hpp"
#include "Renderer/IndexBuffer.hpp"
#include "Renderer/VertexBuffer.hpp"
#include "Renderer/VertexArray.hpp"
#include "Resources/ResourceManager.hpp"
#include "Renderer/Texture2D.hpp"

#include <iostream>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <../external/glm/glm/mat3x3.hpp> 

namespace Game {

    static bool s_GLFW_initialized = false;

    GLuint indices[] = {
        0, 1, 2, 3, 2, 1
    };

    GLfloat points[] = {
       -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
       -0.5f,  0.5f, 0.0f,
        0.5f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
       -0.5f,  0.5f, 0.0f
    };

    GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    GLfloat texture_points[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 1.0f
    };

    std::unique_ptr<ResourceManager> p_resourceManager;
    std::unique_ptr<VertexBuffer> p_positions_colors_vbo;
    std::unique_ptr<VertexBuffer> p_texture_points_vbo;
    std::unique_ptr<IndexBuffer> p_index_buffer;
    std::unique_ptr<VertexArray> p_vao;

    Window::Window(std::string title, const unsigned int width, const unsigned int height, char** argv)
        : m_data({ std::move(title), width, height })
    {
        int resultCode = init(argv);
    }

    Window::~Window()
    {
        shutdown();
    }

    int Window::init(char** argv)
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

        p_resourceManager = std::make_unique<ResourceManager>(argv[0]);
        pDefaultShaderProgram = p_resourceManager->loadShader("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
        if (!pDefaultShaderProgram) {
            std::cerr << "Can`t create shader program: " << "DefaultShader" << std::endl;
            return -5;
        }

        BufferLayout buffer_layout_2vec3
        {
            ShaderDataType::Float3,
            ShaderDataType::Float3
        };
        BufferLayout buffer_layout_1vec2
        {
            ShaderDataType::Float2
        };
        tex = p_resourceManager->loadTexture("Test_64x64", "res/textures/Test_64x64.png");

        /*p_vao = std::make_unique<VertexArray>();
        p_positions_colors_vbo = std::make_unique<VertexBuffer>(positions_colors, sizeof(positions_colors), buffer_layout_2vec3);
        p_texture_points_vbo = std::make_unique<VertexBuffer>(texture_points, sizeof(texture_points), buffer_layout_1vec2);
        p_index_buffer = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(GLuint));

        p_vao->add_vertex_buffer(*p_positions_colors_vbo);
        p_vao->add_vertex_buffer(*p_texture_points_vbo);
        p_vao->set_index_buffer(*p_index_buffer);*/
        GLuint points_vbo = 0;
        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

        GLuint colors_vbo = 0;
        glGenBuffers(1, &colors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        GLuint points_texture_vbo = 0;
        glGenBuffers(1, &points_texture_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_texture_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(texture_points), texture_points, GL_STATIC_DRAW);

        vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, points_texture_vbo);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        pDefaultShaderProgram->bind();
        pDefaultShaderProgram->setInt("tex", 0);

        glm::mat3 mat_1(4, 0, 0, 2, 8, 1, 0, 1, 0);
        glm::mat3 mat_2(4, 2, 9, 2, 0, 4, 1, 4, 2);

        glm::mat3 result_mat = mat_1 * mat_2;

        std::cout << result_mat[0][0]; std::cout << result_mat[1][0]; std::cout << result_mat[2][0]; std::cout << std::endl;
        std::cout << result_mat[0][1]; std::cout << result_mat[1][1]; std::cout << result_mat[2][1]; std::cout << std::endl;
        std::cout << result_mat[0][2]; std::cout << result_mat[1][2]; std::cout << result_mat[2][2]; std::cout << std::endl;

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

        pDefaultShaderProgram->bind();
        //p_vao->bind();
        glBindVertexArray(vao);
        tex->bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        //glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(p_vao->get_indices_count()), GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();
    }

}