#include "Animated_Polygon2D.hpp"

#include <iostream>

namespace Game 
{
	Animated_Polygon2D::Animated_Polygon2D(std::shared_ptr<Texture2D> pTexture,
										   std::string initialSubTexture,
										   std::shared_ptr<ShaderProgram> pShaderProgram,
										   glm::vec3& position,
										   glm::vec2& size,
										   glm::vec4& rotation)
										   : Polygon2D(std::move(pTexture), std::move(initialSubTexture), std::move(pShaderProgram), std::move(position), std::move(size), std::move(rotation))
	{
		m_pCurrentAnimationDurations = m_statesMap.end();
	}

	void Animated_Polygon2D::insertState(std::string state, std::vector<std::pair<std::string, uint64_t>> subTextureDuration) {
		m_statesMap.emplace(std::move(state), std::move(subTextureDuration));
	}

	void Animated_Polygon2D::setState(const std::string& newState) {
		auto it = m_statesMap.find(newState);
		if (it == m_statesMap.end())
		{
			std::cout << "Can't find animation state: " << newState << std::endl;
			return;
		}

		if (it != m_pCurrentAnimationDurations)
		{
			m_currentAnimationTime = 0;
			m_currentFrame = 0;
			m_pCurrentAnimationDurations = it;
			m_dirty = true;
		}
	}

	void Animated_Polygon2D::update(const uint64_t delta) {
		if (m_pCurrentAnimationDurations != m_statesMap.end())
		{
			m_currentAnimationTime += delta;
			while (m_currentAnimationTime >= m_pCurrentAnimationDurations->second[m_currentFrame].second)
			{
				m_currentAnimationTime -= m_pCurrentAnimationDurations->second[m_currentFrame].second;
				++m_currentFrame;
				m_dirty = true;
				if (m_currentFrame == m_pCurrentAnimationDurations->second.size())
				{
					m_currentFrame = 0;
				}
			}
		}
	}

	void Animated_Polygon2D::render() const {
		if (m_dirty)
		{
			auto subTexture = m_pTexture->getSubTexture(m_pCurrentAnimationDurations->second[m_currentFrame].first);

			const GLfloat textureCoords[] = {
				// U  V
				subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
				subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
				subTexture.rightTopUV.x, subTexture.rightTopUV.y,
				subTexture.rightTopUV.x, subTexture.leftBottomUV.y,
			};

			m_textureCoordsBuffer.update(textureCoords, 2 * 4 * sizeof(GLfloat));
			m_dirty = false;
		}
		Polygon2D::render();
	}
}