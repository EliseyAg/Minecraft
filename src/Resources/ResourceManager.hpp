#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>

#include <../src/RenderEngine/OpenGL/ShaderProgram.hpp>
#include <../src/RenderEngine/OpenGL/Texture2D.hpp>
#include <../src/RenderEngine/OpenGL/Animated_Polygon2D.hpp>
#include <../src/RenderEngine/OpenGL/Polygon2D.hpp>

namespace Game {
	class ResourceManager {
	public:
		static void setExecutablePath(const std::string& executablePath);
		static void unloadAllResources();

		~ResourceManager() = delete;
		ResourceManager() = delete;
		ResourceManager(const ResourceManager&) = delete;
		ResourceManager(ResourceManager&&) = delete;
		ResourceManager& operator=(const ResourceManager&) = delete;
		ResourceManager& operator=(ResourceManager&&) = delete;

		static std::vector<std::shared_ptr<std::pair<std::string, glm::vec3>>> loadWorld(std::vector<std::shared_ptr<std::pair<std::string, glm::vec3>>> blocks, const std::string& filePath);

		static std::shared_ptr<RenderEngine::ShaderProgram> loadShader(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
		static std::shared_ptr<RenderEngine::ShaderProgram> getShader(const std::string& shaderName);
		static std::shared_ptr<RenderEngine::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
		static std::shared_ptr<RenderEngine::Texture2D> getTexture(const std::string& textureName);
		static std::shared_ptr<Polygon2D> loadPolygon(const std::string& PolygonName, const std::string& textureName, const std::string& shaderName, const unsigned int polygonWidth, const unsigned int polygonHeight, const std::string& subTextureName = "default");
		static std::shared_ptr<Polygon2D> getPolygon(const std::string& PolygonName);
		static std::shared_ptr<Animated_Polygon2D> loadAnimatedPolygon(const std::string& PolygonName, const std::string& textureName, const std::string& shaderName, const unsigned int polygonWidth, const unsigned int polygonHeight, const std::string& subTextureName);
		static std::shared_ptr<Animated_Polygon2D> getAnimatedPolygon(const std::string& PolygonName);
		static std::shared_ptr<RenderEngine::Texture2D> loadTextureAtlas(std::string textureName, std::string texturePath, std::vector<std::string> subTextures, const unsigned int width, const unsigned int height);

	private:
		static std::string getFileString(const std::string& relativeFilePath);

		using  ShaderProgramsMap = std::map<const std::string, const std::shared_ptr<RenderEngine::ShaderProgram>>;
		static ShaderProgramsMap m_shaderPrograms;

		using TexturesMap = std::map<const std::string, std::shared_ptr<RenderEngine::Texture2D>>;
		static TexturesMap m_textures;

		using PolygonesMap = std::map<const std::string, std::shared_ptr<Polygon2D>>;
		static PolygonesMap m_polygones;

		using Animated_PolygonesMap = std::map<const std::string, std::shared_ptr<Animated_Polygon2D>>;
		static Animated_PolygonesMap m_animated_polygones;

		static std::string m_path;
	};
}