#include "Polygon2D.hpp"

#include <../external/glm/glm/mat4x4.hpp>
#include <../external/glm/glm/gtc/matrix_transform.hpp>

namespace Game 
{
	Polygon2D::Polygon2D(std::shared_ptr<Texture2D> pTexture,
						 std::string initialSubTexture,
						 std::shared_ptr<ShaderProgram> pShaderProgram,
						 glm::vec2& position,
						 glm::vec2& size,
						 float rotation)
						 : m_pTexture(std::move(pTexture))
						 , m_pShaderProgram(std::move(pShaderProgram))
						 , m_position(std::move(position))
						 , m_size(std::move(size))
						 , m_rotation(std::move(rotation))
	{
		const GLfloat vertexCoords[] = {
			// 2--3    1
			// | /   / |
			// 1    3--2

			// X  Y
			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,

			1.f, 1.f,
			1.f, 0.f,
			0.f, 0.f
		};

		auto subTexture = m_pTexture->getSubTexture(std::move(initialSubTexture));

		const GLfloat textureCoords[] = {
			// U  V
			subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
			subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
			subTexture.rightTopUV.x, subTexture.rightTopUV.y,

			subTexture.rightTopUV.x, subTexture.rightTopUV.y,
			subTexture.rightTopUV.x, subTexture.leftBottomUV.y,
			subTexture.leftBottomUV.x, subTexture.leftBottomUV.y
		};

		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		glGenBuffers(1, &m_vertexCoords_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexCoords_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCoords), &vertexCoords, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

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
		model = glm::rotate(model, glm::radians(m_rotation), glm::vec3(0.f, 0.f, 1.f));
		model = glm::translate(model, glm::vec3(-0.5f * m_size.x, 0.5f * m_size.y, 0.f));
		model = glm::scale(model, glm::vec3(m_size, 1.f));

		glBindVertexArray(m_vao);
		m_pShaderProgram->setMatrix4("modelMat", model);

		glActiveTexture(GL_TEXTURE0);
		m_pTexture->bind();

		glDrawArrays(GL_TRIANGLES, 0, 6);
		GLenum ErrorCheckValue = glGetError();
		glBindVertexArray(0);
	}

	void Polygon2D::setPosition(const glm::vec2& position) {
		m_position = position;
	}

	void Polygon2D::setSize(const glm::vec2& size) {
		m_size = size;
	}
	void Polygon2D::setRotation(const float rotation)
	{
		m_rotation = rotation;
	}
}