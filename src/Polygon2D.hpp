#pragma once

#include <glad/glad.h>
#include <../external/glm/glm/vec2.hpp>

#include "RenderEngine/OpenGL/Texture2D.hpp"
#include "RenderEngine/OpenGL/ShaderProgram.hpp"
#include "RenderEngine/OpenGL/VertexBuffer.hpp"
#include "RenderEngine/OpenGL/IndexBuffer.hpp"
#include "RenderEngine/OpenGL/VertexArray.hpp"
#include "RenderEngine/OpenGL/Renderer.hpp"

#include <memory>
#include <string>

namespace Game
{
	class Polygon2D
	{
	public:
		Polygon2D(std::shared_ptr<RenderEngine::Texture2D> pTexture,
				  std::string initialSubTexture,
				  std::shared_ptr<RenderEngine::ShaderProgram> pShaderProgram,
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
		std::shared_ptr<RenderEngine::Texture2D> m_pTexture;
		std::shared_ptr<RenderEngine::ShaderProgram> m_pShaderProgram;
		glm::vec3 m_position;
		glm::vec2 m_size;
		glm::vec4 m_rotation;

		RenderEngine::VertexArray m_vertexArray;
		RenderEngine::VertexBuffer m_vertexCoordsBuffer;
		RenderEngine::VertexBuffer m_textureCoordsBuffer;
		RenderEngine::IndexBuffer m_indexBuffer;
	};
}