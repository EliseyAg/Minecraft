#pragma once
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"

namespace Renderer
{
	class Renderer;

	class Mesh
	{
	public:
		Mesh();
		~Mesh();

	private:
		size_t vertices;
		Renderer::VertexArray m_vertexArray;
		Renderer::VertexBuffer m_vertexCoordsBuffer;
		Renderer::VertexBuffer m_textureCoordsBuffer;
	};
}
