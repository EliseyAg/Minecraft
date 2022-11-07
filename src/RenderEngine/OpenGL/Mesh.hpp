#pragma once
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"

namespace Rendering
{
	class Renderer;

	class Mesh
	{
	public:
		Mesh();
		~Mesh();

	private:
		size_t vertices;
		Rendering::VertexArray m_vertexArray;
		Rendering::VertexBuffer m_vertexCoordsBuffer;
		Rendering::VertexBuffer m_textureCoordsBuffer;
	};
}
