#include "ResourceManager.hpp"

#include <sstream>
#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_JPEG
#define STBI_ONLY_PNG
#include "../external/stb_image/stb_image.h"

namespace Game {
	ResourceManager::ShaderProgramsMap ResourceManager::m_shaderPrograms;
	ResourceManager::TexturesMap ResourceManager::m_textures;
	ResourceManager::PolygonesMap ResourceManager::m_polygones;
	ResourceManager::Animated_PolygonesMap ResourceManager::m_animated_polygones;
	std::string ResourceManager::m_path;


	void ResourceManager::unloadAllResources()
	{
		m_shaderPrograms.clear();
		m_textures.clear();
		m_polygones.clear();
		m_animated_polygones.clear();
	}

	void ResourceManager::setExecutablePath(const std::string& executablePath)
	{
		size_t found = executablePath.find_last_of("/\\");
		m_path = executablePath.substr(0, found);
	}

	std::string ResourceManager::getFileString(const std::string& relativeFilePath)
	{
		std::ifstream f;
		f.open(m_path + "/" + relativeFilePath.c_str(), std::ios::in | std::ios::binary);
		if (!f.is_open()) {
			std::cerr << "Failed to open file: " << relativeFilePath << std::endl;
			return std::string{};
		}

		std::stringstream buffer;
		buffer << f.rdbuf();
		return buffer.str();
	}

	std::vector<std::shared_ptr<std::pair<std::string, glm::vec3>>> ResourceManager::loadWorld(std::vector<std::shared_ptr<std::pair<std::string, glm::vec3>>> blocks, const std::string& filePath)
	{
		const std::string fileString = getFileString(filePath);
		int a = 0;
		blocks.clear();
		for (int i = 0; i < 25; i++)
		{
			std::string block_name = fileString.substr(a, fileString.find(',', a) - a);
			a = fileString.find(',', a) + 1;
			int x = atoi(fileString.substr(a, fileString.find(',', a) - a).c_str());
			a = fileString.find(',', a) + 1;
			int y = atoi(fileString.substr(a, fileString.find(',', a) - a).c_str());
			a = fileString.find(',', a) + 1;
			int z = atoi(fileString.substr(a, fileString.find(',', a) - a).c_str());
			blocks.push_back(std::make_shared<std::pair<std::string, glm::vec3>>(std::make_pair(block_name, glm::vec3(x, y, z))));
			a = fileString.find(',', a) + 3;
		}
		return blocks;
	}

	std::shared_ptr<RenderEngine::ShaderProgram> ResourceManager::loadShader(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
	{
		const std::string vertexString = getFileString(vertexPath);
		if (vertexString.empty()) {
			std::cerr << "No vertex shader!" << std::endl;
			return nullptr;
		}

		const std::string fragmentString = getFileString(fragmentPath);
		if (fragmentString.empty()) {
			std::cerr << "No fragment shader!" << std::endl;
			return nullptr;
		}

		const std::shared_ptr<RenderEngine::ShaderProgram> newShader = std::make_shared<RenderEngine::ShaderProgram>(vertexString, fragmentString);
		auto p1 = std::make_pair(shaderName, newShader);
		m_shaderPrograms.emplace(p1);
		if (newShader->isCompiled()) {
			return newShader;
		}

		std::cerr << "Can`t load shader program:\n"
			<< "Vertex: " << vertexPath << "\n"
			<< "Fragment:" << fragmentPath << std::endl;

		return nullptr;
	}

	std::shared_ptr<RenderEngine::ShaderProgram> ResourceManager::getShader(const std::string& shaderName)
	{
		ShaderProgramsMap::const_iterator it = m_shaderPrograms.find(shaderName);
		if (it != m_shaderPrograms.end())
			return it->second;
		std::cerr << "Can`t find the shader program: " << shaderName << std::endl;
		return nullptr;
	}

	std::shared_ptr<RenderEngine::Texture2D>  ResourceManager::loadTexture(const std::string& textureName, const std::string& texturePath)
	{
		int channels = 0;
		int width = 0;
		int height = 0;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* pixels = stbi_load(std::string(m_path + "/" + texturePath).c_str(), &width, &height, &channels, 0);

		if (!pixels)
		{
			std::cerr << "Can't load image: " << m_path + "/" + texturePath << std::endl << stbi_failure_reason() << std::endl;
			return nullptr;
		}

		std::shared_ptr<RenderEngine::Texture2D> newTexture = std::make_shared<RenderEngine::Texture2D>(width,
																									height,
																									pixels,
																									channels,
																									GL_NEAREST,
																									GL_CLAMP_TO_EDGE);
		m_textures.insert(std::make_pair(textureName, newTexture));
		stbi_image_free(pixels);
		return newTexture;
	}

	std::shared_ptr<RenderEngine::Texture2D> ResourceManager::getTexture(const std::string& textureName)
	{
		TexturesMap::const_iterator it = m_textures.find(textureName);
		if (it != m_textures.end())
			return it->second;
		std::cerr << "Can`t find the texture: " << textureName << std::endl;
		return nullptr;
	}

	std::shared_ptr<Polygon2D> ResourceManager::loadPolygon(const std::string& PolygonName,
															const std::string& textureName,
															const std::string& shaderName,
															const unsigned int PolygonWidth,
															const unsigned int PolygonHeight,
															const std::string& subTextureName)
	{
		auto pTexture = getTexture(textureName);
		if (!pTexture)
		{
			std::cerr << "Can't find the texture: " << textureName << " for the Polygon: " << PolygonName << std::endl;
		}

		auto pShader = getShader(shaderName);
		if (!pShader)
		{
			std::cerr << "Can't find the shader: " << shaderName << " for the Polygon: " << PolygonName << std::endl;
		}

		std::shared_ptr<Polygon2D> newPolygon = std::make_shared<Polygon2D>(pTexture,
			subTextureName,
			pShader,
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec2(PolygonWidth, PolygonHeight));
		m_polygones.insert(std::make_pair(PolygonName, newPolygon));

		return newPolygon;
	}

	std::shared_ptr<Polygon2D> ResourceManager::getPolygon(const std::string& PolygonName)
	{
		PolygonesMap::const_iterator it = m_polygones.find(PolygonName);
		if (it != m_polygones.end())
		{
			return it->second;
		}
		std::cerr << "Can't find the Polygon: " << PolygonName << std::endl;
		return nullptr;
	}

	std::shared_ptr<Animated_Polygon2D> ResourceManager::loadAnimatedPolygon(const std::string& PolygonName, const std::string& textureName, const std::string& shaderName, const unsigned int polygonWidth, const unsigned int polygonHeight, const std::string& subTextureName) {
		auto pTexture = getTexture(textureName);
		if (!pTexture)
		{
			std::cerr << "Can't find the texture: " << textureName << " for the Polygon: " << PolygonName << std::endl;
		}

		auto pShader = getShader(shaderName);
		if (!pShader)
		{
			std::cerr << "Can't find the shader: " << shaderName << " for the Polygon: " << PolygonName << std::endl;
		}

		std::shared_ptr<Animated_Polygon2D> newPolygon = std::make_shared<Animated_Polygon2D>(pTexture,
			subTextureName,
			pShader,
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec2(polygonWidth, polygonHeight),
			glm::vec4(0.f, 0.f, 0.f, 0.f));
		m_animated_polygones.insert(std::make_pair(PolygonName, newPolygon));

		return newPolygon;
	}

	std::shared_ptr<Animated_Polygon2D> ResourceManager::getAnimatedPolygon(const std::string& PolygonName) {
		Animated_PolygonesMap::const_iterator it = m_animated_polygones.find(PolygonName);
		if (it != m_animated_polygones.end())
		{
			return it->second;
		}
		std::cerr << "Can't find animated Polygon: " << PolygonName << std::endl;
		return nullptr;
	}

	std::shared_ptr<RenderEngine::Texture2D> ResourceManager::loadTextureAtlas(std::string textureName, std::string texturePath, std::vector<std::string> subTextures, const unsigned int subTextureWidth, const unsigned int subTextureHeight) {
		auto pTexture = loadTexture(std::move(textureName), std::move(texturePath));
		if (pTexture)
		{
			const unsigned int textureWidth = pTexture->width();
			const unsigned int textureHeight = pTexture->height();
			unsigned int currentTextureOffsetX = 0;
			unsigned int currentTextureOffsetY = textureHeight;
			for (auto& currentSubTextureName : subTextures) {
				glm::vec2 leftBottomUV(static_cast<float>(currentTextureOffsetX + 0.01f) / textureWidth, static_cast<float>(currentTextureOffsetY - subTextureHeight + 0.01f) / textureHeight);
				glm::vec2 rightTopUV(static_cast<float>(currentTextureOffsetX + subTextureWidth - 0.01f) / textureWidth, static_cast<float>(currentTextureOffsetY - 0.01f) / textureHeight);
				pTexture->addSubTexture(std::move(currentSubTextureName), leftBottomUV, rightTopUV);

				currentTextureOffsetX += subTextureWidth;
				if (currentTextureOffsetX >= textureWidth)
				{
					currentTextureOffsetX = 0;
					currentTextureOffsetY -= subTextureHeight;
				}
			}
		}
		return pTexture;
	}
}