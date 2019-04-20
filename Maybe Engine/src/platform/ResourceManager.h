#pragma once

#include <vector>
#include <map>

#include "..\graphics\Texture.h"

namespace mb { namespace platform {

	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

		void AddTexture(const char* path, const unsigned int ID);
		void AddTexture(const char* path, const std::string tag);

		graphics::Texture* GetTexture(const unsigned int& ID);
		graphics::Texture* GetTexture(const std::string& tag);

		void DeleteTexture(const unsigned int& ID);
		void DeleteTexture(const std::string& tag);
	private:
		std::vector<graphics::Texture*> m_Textures;
		std::map<unsigned int, unsigned int> m_TextureIndexIDMap;
		std::map<std::string, unsigned int> m_TextureIndexTagMap;
	};

} }