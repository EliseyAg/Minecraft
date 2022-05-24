#include "Polygon2D.hpp"

#include <../external/glm/glm/mat4x4.hpp>
#include <../external/glm/glm/gtc/matrix_transform.hpp>

namespace Game 
{
	Polygon2D::Polygon2D(const std::shared_ptr<Texture2D> pTexture, const std::shared_ptr<ShaderProgram> pShaderProgram, const glm::vec2& position, const glm::vec2& size) 
		: m_pTexture(std::move(pTexture))
		, m_pShaderProgram(std::move(pShaderProgram))
		, m_size(size)
	{
		GLfloat vertexCoords[] = {
		   -0.5f, -0.5f,
			0.5f, -0.5f,
		   -0.5f,  0.5f,
			0.5f,  0.5f,
			0.5f, -0.5f,
		   -0.5f,  0.5f,
		};

		GLfloat textureCoords[] = {
		   0.0f, 0.0f,
		   1.0f, 0.0f,
		   0.0f, 1.0f,
		   1.0f, 1.0f,
		   1.0f, 0.0f,
		   0.0f, 1.0f
		};

		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		glGenBuffers(1, &m_vertexCoords_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexCoords_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCoords), &vertexCoords, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glGenBuffers(1, &m_textureCoords_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_textureCoords_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords), &textureCoords, GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	Polygon2D::~Polygon2D() {
		glDeleteBuffers(1, &m_vertexCoords_vbo);
		glDeleteBuffers(1, &m_textureCoords_vbo);
		glDeleteVertexArrays(1, &m_vao);
	}

	void Polygon2D::render() const {
		m_pShaderProgram->bind();

		glm::mat4 model(1.f);

		model = glm::translate(model, glm::vec3(m_position, 0.f));
		model = glm::translate(model, glm::vec3(0.5f * m_size.x, 0.5f * m_size.y, 0.f));
		model = glm::translate(model, glm::vec3(-0.5f * m_size.x, 0.5f * m_size.y, 0.f));
		model = glm::scale(model, glm::vec3(m_size, 1.f));

		glBindVertexArray(m_vao);
		m_pShaderProgram->setMatrix4("model_matrix", model);

		glActiveTexture(GL_TEXTURE0);
		m_pTexture->bind();

		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}

	void Polygon2D::setPosition(const glm::vec2& position) {
		m_position = position;
	}

	void Polygon2D::setSize(const glm::vec2& size) {
		m_size = size;
	}
}