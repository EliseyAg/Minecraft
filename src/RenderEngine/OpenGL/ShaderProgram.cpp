#include "ShaderProgram.hpp"

#include <iostream>
#include <string>

#include <glad/glad.h>

namespace RenderEngine
{
    bool create_shader(const std::string& source, const GLenum shader_type, GLuint &shader_id)
    {
        shader_id = glCreateShader(shader_type);
        const char* code = source.c_str();
        glShaderSource(shader_id, 1, &code, nullptr);
        glCompileShader(shader_id);

        GLint success;
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[1024];
            glGetShaderInfoLog(shader_id, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER: Compile-time error:\n" << infoLog << std::endl;
            return false;
        }
        return true;
    }


    ShaderProgram::ShaderProgram(const std::string& vertex_shader_src, const std::string& fragment_shader_src)
    {
        GLuint vertex_shader_id = 0;
        if (!create_shader(vertex_shader_src, GL_VERTEX_SHADER, vertex_shader_id))
        {
            glDeleteShader(vertex_shader_id);
            return;
        }

        GLuint fragment_shader_id = 0;
        if (!create_shader(fragment_shader_src, GL_FRAGMENT_SHADER, fragment_shader_id))
        {
            glDeleteShader(vertex_shader_id);
            glDeleteShader(fragment_shader_id);
            return;
        }

        m_id = glCreateProgram();
        glAttachShader(m_id, vertex_shader_id);
        glAttachShader(m_id, fragment_shader_id);
        glLinkProgram(m_id);

        GLint success;
        glGetProgramiv(m_id, GL_LINK_STATUS, &success);
        if (success == GL_FALSE)
        {
            GLchar info_log[1024];
            glGetProgramInfoLog(m_id, 1024, nullptr, info_log);
            glDeleteProgram(m_id);
            m_id = 0;
            glDeleteShader(vertex_shader_id);
            glDeleteShader(fragment_shader_id);
            return;
        }
        else
        {
            m_isCompiled = true;
        }

        glDetachShader(m_id, vertex_shader_id);
        glDetachShader(m_id, fragment_shader_id);
        glDeleteShader(vertex_shader_id);
        glDeleteShader(fragment_shader_id);
    }

    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(m_id);
    }

    void ShaderProgram::bind() const
    {
        glUseProgram(m_id);
    }

    void ShaderProgram::unbind()
    {
        glUseProgram(0);
    }

    ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram)
    {
        glDeleteProgram(m_id);
        m_id = shaderProgram.m_id;
        m_isCompiled = shaderProgram.m_isCompiled;

        shaderProgram.m_id = 0;
        shaderProgram.m_isCompiled = false;
        return *this;
    }

    ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram)
    {
        m_id = shaderProgram.m_id;
        m_isCompiled = shaderProgram.m_isCompiled;

        shaderProgram.m_id = 0;
        shaderProgram.m_isCompiled = false;
    }

    void ShaderProgram::setInt(const std::string& name, const GLint value)
    {
        glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
    }

    void ShaderProgram::setVec3(const std::string& name, const glm::vec3& value)
    {
        glUniform3f(glGetUniformLocation(m_id, name.c_str()), value.x, value.y, value.z);
    }


    void ShaderProgram::setMatrix4(const char* name, const glm::mat4& matrix) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_id, name), 1, GL_FALSE, glm::value_ptr(matrix));
    }
}