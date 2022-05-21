#pragma once

#include <string>

namespace Game {

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
        bool isCompiled() const { return m_isCompiled; }

    private:
        bool m_isCompiled = false;
        unsigned int m_id = 0;
    };

}