#pragma once

#include <glad/glad.h>
#include <../external/glm/glm/vec2.hpp>

#include "Renderer/Texture2D.hpp"
#include "Renderer/ShaderProgram.hpp"

#include <memory>
#include <string>

namespace Game
{
	class Polygon2D
	{
	public:
		Polygon2D(const std::shared_ptr<Texture2D> pTexture,
				  const std::string initialSubTexture,
				  const std::shared_ptr<ShaderProgram> pShaderProgram,
				  const glm::vec2& position = glm::vec2(0.f),
				  const glm::vec2& size = glm::vec2(1.f),
				  const float rotation = 0.f);

		~Polygon2D();

		Polygon2D(const Polygon2D&) = delete;
		Polygon2D& operator=(const Polygon2D&) = delete;

		void render() const;
		void setPosition(const glm::vec2& position);
		void setSize(const glm::vec2& size);
		void setRotation(const float rotation);
	private:
		std::shared_ptr<Texture2D> m_pTexture;
		std::shared_ptr<ShaderProgram> m_pShaderProgram;
		glm::vec2 m_position;
		glm::vec2 m_size;
		float m_rotation;
		GLuint m_vao;
		GLuint m_vertexCoords_vbo;
		GLuint m_textureCoords_vbo;
	};
}