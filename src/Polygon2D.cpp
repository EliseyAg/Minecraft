#include <iostream>
#include "Polygon2D.hpp"

#include <../external/glm/glm/mat4x4.hpp>
#include <../external/glm/glm/gtc/matrix_transform.hpp>

#define PI 3.14

namespace Game 
{
	Polygon2D::Polygon2D(std::shared_ptr<Texture2D> pTexture,
						 std::string initialSubTexture,
						 std::shared_ptr<ShaderProgram> pShaderProgram,
						 glm::vec3& position,
						 glm::vec2& size,
						 glm::vec4& rotation)
						 : m_pTexture(std::move(pTexture))
						 , m_pShaderProgram(std::move(pShaderProgram))
						 , m_position(std::move(position))
						 , m_size(std::move(size))
						 , m_rotation(std::move(rotation))
	{
		const GLfloat vertexCoords[] = {
			// 1---2
			// | / |
			// 0---3

			// X  Y
			0.f, 0.f, 0.f,
			0.f, 1.f, 0.f,
			1.f, 1.f, 0.f,
			1.f, 0.f, 0.f
		};

		auto subTexture = m_pTexture->getSubTexture(std::move(initialSubTexture));

		const GLfloat textureCoords[] = {
			// U  V
			subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
			subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
			subTexture.rightTopUV.x, subTexture.rightTopUV.y,
			subTexture.rightTopUV.x, subTexture.leftBottomUV.y,
		};

		const GLuint indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		m_vertexCoordsBuffer.init(vertexCoords, 3 * 4 * sizeof(GLfloat));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		m_textureCoordsBuffer.init(textureCoords, 2 * 4 * sizeof(GLfloat));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		m_indexBuffer.init(indices, 6 * sizeof(GLuint));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	Polygon2D::~Polygon2D() {
		glDeleteVertexArrays(1, &m_vao);
	}

	void Polygon2D::render() const {
		m_pShaderProgram->bind();

		glm::mat4 model(1.f);

		glm::vec4 rotation = m_rotation;

		model = glm::translate(model, glm::vec3(m_position));
		rotation.w = glm::max(glm::max(glm::abs(rotation.x), glm::abs(rotation.y)), glm::abs(rotation.z));
		if (rotation.w)
			model = glm::rotate(model, glm::radians(rotation.w),
				glm::vec3(
					glm::radians(rotation.x / rotation.w),
					glm::radians(rotation.y / rotation.w),
					glm::radians(rotation.z / rotation.w)
				)
			);
		model = glm::translate(model, glm::vec3(-0.5f * m_size.x, -0.5f * m_size.y, 0.f));
		model = glm::scale(model, glm::vec3(m_size, 1.f));

		glBindVertexArray(m_vao);
		m_pShaderProgram->setMatrix4("modelMat", model);

		glActiveTexture(GL_TEXTURE0);
		m_pTexture->bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glBindVertexArray(0);
	}

	void Polygon2D::setPosition(const glm::vec3& position) {
		m_position = position;
	}

	void Polygon2D::setSize(const glm::vec2& size) {
		m_size = size;
	}
	void Polygon2D::setRotation(const glm::vec4& rotation)
	{
		m_rotation = rotation;
	}
}