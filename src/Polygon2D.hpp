#pragma once

#include <glad/glad.h>
#include <../external/glm/glm/vec2.hpp>

#include "Renderer/Texture2D.hpp"
#include "Renderer/ShaderProgram.hpp"
#include "Renderer/VertexBuffer.hpp"
#include "Renderer/IndexBuffer.hpp"
#include "Renderer/VertexArray.hpp"

#include <memory>
#include <string>

namespace Game
{
	class Polygon2D
	{
	public:
		Polygon2D(std::shared_ptr<Renderer::Texture2D> pTexture,
				  std::string initialSubTexture,
				  std::shared_ptr<Renderer::ShaderProgram> pShaderProgram,
				  glm::vec3& position = glm::vec3(0.f),
				  glm::vec2& size = glm::vec2(1.f),
				  glm::vec4& rotation = glm::vec4(0.f));

		~Polygon2D();

		Polygon2D(const Polygon2D&) = delete;
		Polygon2D& operator=(const Polygon2D&) = delete;

		virtual void render() const;
		void setPosition(const glm::vec3& position);
		void setSize(const glm::vec2& size);
		void setRotation(const glm::vec4& rotation);
	protected:
		std::shared_ptr<Renderer::Texture2D> m_pTexture;
		std::shared_ptr<Renderer::ShaderProgram> m_pShaderProgram;
		glm::vec3 m_position;
		glm::vec2 m_size;
		glm::vec4 m_rotation;

		Renderer::VertexArray m_vertexArray;
		Renderer::VertexBuffer m_vertexCoordsBuffer;
		Renderer::VertexBuffer m_textureCoordsBuffer;
		Renderer::IndexBuffer m_indexBuffer;
	};
}