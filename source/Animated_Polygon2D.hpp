#pragma once

#include "Polygon2D.hpp"

#include <map>
#include <vector>
#include <string>

namespace Game
{
	class Animated_Polygon2D : public Polygon2D
	{
	public:
		Animated_Polygon2D(std::shared_ptr<Texture2D> pTexture,
						   std::string initialSubTexture,
						   std::shared_ptr<ShaderProgram> pShaderProgram,
						   glm::vec2& position = glm::vec2(0.f),
						   glm::vec2& size = glm::vec2(1.f),
						   float rotation = 0.f);

		void insertState(std::string state, std::vector<std::pair<std::string, uint64_t>> subTextureDuration);

		void render() const override;

		void setState(const std::string& newState);
		void update(const uint64_t delta);
		
	private:
		std::map <std::string, std::vector<std::pair<std::string, uint64_t>>> m_statesMap;
		size_t m_currentFrame = 0;
		uint64_t m_currentAnimationTime = 0;
		std::map <std::string, std::vector<std::pair<std::string, uint64_t>>>::const_iterator m_pCurrentAnimationDurations;
		mutable bool m_dirty = false;
	};
}