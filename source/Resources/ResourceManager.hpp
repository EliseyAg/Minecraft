#pragma once

#include <string>
#include <memory>
#include <map>

#include <Renderer/ShaderProgram.hpp>

namespace Game {
	class ResourceManager {
	public:
		ResourceManager(const std::string& executablePath);
		~ResourceManager() = default;

		ResourceManager(const ResourceManager&) = delete;
		ResourceManager(ResourceManager&&) = delete;
		ResourceManager& operator=(const ResourceManager&) = delete;
		ResourceManager& operator=(ResourceManager&&) = delete;

		std::shared_ptr<ShaderProgram> loadShader(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
		std::shared_ptr<ShaderProgram> getShader(const std::string& shaderName);
		void loadTexture(const std::string& textureName, const std::string& texturePath);
	private:
		std::string getFileString(const std::string& relativeFilePath);

		typedef std::map<const std::string, std::shared_ptr<ShaderProgram>> ShaderProgramsMap;
		ShaderProgramsMap m_shaderPrograms;

		std::string m_path;
	};
}