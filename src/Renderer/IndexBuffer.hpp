#pragma once
#include "VertexBuffer.hpp"

#include <glad/glad.h>

namespace Game {

    class IndexBuffer {
    public:
        IndexBuffer();
        ~IndexBuffer();

        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer& operator=(const IndexBuffer&) = delete;
        IndexBuffer& operator=(IndexBuffer&& indexBuffer) noexcept;
        IndexBuffer(IndexBuffer&& indexBuffer) noexcept;

        void init(const void* data, const unsigned int size);
        void bind() const;
        void unbind() const;

    private:
        GLuint m_id;
    };

}