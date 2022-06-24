#include "Renderer.hpp"

namespace RenderEngine {
	void Renderer::draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const ShaderProgram& shader)
	{
		shader.bind();
		vertexArray.bind();
		indexBuffer.bind();

		glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::setClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void Renderer::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::setViewport(unsigned int width, unsigned int height, unsigned int leftOffset, unsigned int BottomOffset)
	{
		glViewport(leftOffset, BottomOffset, width, height);
	}
}