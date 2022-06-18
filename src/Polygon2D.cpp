#include <iostream>
#include "Polygon2D.hpp"

#include <../external/glm/glm/mat4x4.hpp>
#include <../external/glm/glm/gtc/matrix_transform.hpp>

#define PI 3.14

namespace Game 
{
	Polygon2D::Polygon2D(std::shared_ptr<Renderer::Texture2D> pTexture,
						 std::string initialSubTexture,
						 std::shared_ptr<Renderer::ShaderProgram> pShaderProgram,
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
			subTexture.rightTopUV.x,   subTexture.rightTopUV.y,
			subTexture.rightTopUV.x,   subTexture.leftBottomUV.y,
		};

		const GLuint indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_vertexCoordsBuffer.init(vertexCoords, 3 * 4 * sizeof(GLfloat));
		Renderer::VertexBufferLayout vertexCoordsLayout;
		vertexCoordsLayout.addElementLayoutFloat(3, false);
		m_vertexArray.addBuffer(m_vertexCoordsBuffer, vertexCoordsLayout);

		m_textureCoordsBuffer.init(textureCoords, 2 * 4 * sizeof(GLfloat));
		Renderer::VertexBufferLayout textureCoordsLayout;
		textureCoordsLayout.addElementLayoutFloat(2, false);
		m_vertexArray.addBuffer(m_textureCoordsBuffer, textureCoordsLayout);

		m_indexBuffer.init(indices, 6 * sizeof(GLuint));

		m_vertexArray.unbind();
		m_indexBuffer.unbind();
	}

	Polygon2D::~Polygon2D() {
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

		m_vertexArray.bind();
		m_pShaderProgram->setMatrix4("modelMat", model);

		glActiveTexture(GL_TEXTURE0);
		m_pTexture->bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		m_vertexArray.unbind();
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