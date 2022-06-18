#pragma once

#include <string>

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Renderer {

    class ShaderProgram
    {
    public:
        ShaderProgram(const std::string& vertex_shader_src, const std::string& fragment_shader_src);
        ShaderProgram(ShaderProgram&&);
        ShaderProgram& operator=(ShaderProgram&&);
        ~ShaderProgram();

        ShaderProgram() = delete;
        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;

        void bind() const;
        static void unbind();
        void setInt(const std::string& name, const GLint value);
        bool isCompiled() const { return m_isCompiled; }
        void setMatrix4(const char* name, const glm::mat4& matrix) const;

    private:
        bool m_isCompiled = false;
        unsigned int m_id = 0;
    };

}
