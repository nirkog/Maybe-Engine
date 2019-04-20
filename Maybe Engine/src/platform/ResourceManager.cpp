#include "ResourceManager.h"

#include "..\utils\Log.h"

namespace mb { namespace platform {

	ResourceManager::ResourceManager()
	{

	}

	ResourceManager::~ResourceManager()
	{
		for (unsigned int i = 0; i < m_Textures.size(); i++)
		{
			delete m_Textures[i];
		}
	}

	void ResourceManager::AddTexture(const char* path, const unsigned int ID)
	{
		if (m_TextureIndexIDMap.find(ID) != m_TextureIndexIDMap.end())
		{
			utils::Log::Warn("Trying to add a texture with an existing id, ignoring the request! (id {})", ID);
			return;
		}

		graphics::Texture* texture = new graphics::Texture(path);

		m_Textures.push_back(texture);
		m_TextureIndexIDMap.insert({ ID, m_Textures.size() - 1 });
	}

	void ResourceManager::AddTexture(const char* path, const std::string tag)
	{
		if (m_TextureIndexTagMap.find(tag) != m_TextureIndexTagMap.end())
		{
			utils::Log::Warn("Trying to add a texture with an existing tag, ignoring the request!");
			return;
		}

		graphics::Texture* texture = new graphics::Texture(path);

		m_Textures.push_back(texture);
		m_TextureIndexTagMap.insert({ tag, m_Textures.size() - 1 });
	}

	graphics::Texture* ResourceManager::GetTexture(const unsigned int& ID)
	{
		std::map<unsigned int, unsigned int>::iterator it;

		it = m_TextureIndexIDMap.find(ID);
		if (it == m_TextureIndexIDMap.end())
		{
			utils::Log::Warn("Trying to fetch a texture with a non-existing id, ignoring the request! (id {})", ID);
			return nullptr;
		}

		return m_Textures[it->second];
	}

	graphics::Texture* ResourceManager::GetTexture(const std::string& tag)
	{
		std::map<std::string, unsigned int>::iterator it;
		
		it = m_TextureIndexTagMap.find(tag);
		if (it == m_TextureIndexTagMap.end())
		{
			utils::Log::Warn("Trying to fetch a texture with a non-existing tag, ignoring the request!");
			return nullptr;
		}

		return m_Textures[it->second];
	}

	void ResourceManager::DeleteTexture(const unsigned int& ID)
	{
		std::map<unsigned int, unsigned int>::iterator it;

		it = m_TextureIndexIDMap.find(ID);
		if (it == m_TextureIndexIDMap.end())
		{
			utils::Log::Warn("Trying to delete a texture with a non-existing id, ignoring the request! (id {})", ID);
			return;
		}

		const unsigned int deletedIndex = it->second;

		m_Textures.erase(m_Textures.begin() + deletedIndex);
		m_TextureIndexIDMap.erase(it);

		for (auto& pair : m_TextureIndexIDMap)
		{
			const unsigned int index = pair.second;

			if (index > deletedIndex)
				pair.second--;
		}
	}

	void ResourceManager::DeleteTexture(const std::string& tag)
	{
		std::map<std::string, unsigned int>::iterator it;

		it = m_TextureIndexTagMap.find(tag);
		if (it == m_TextureIndexTagMap.end())
		{
			utils::Log::Warn("Trying to delete a texture with a non-existing tag, ignoring the request!");
			return;
		}

		const unsigned int deletedIndex = it->second;

		m_Textures.erase(m_Textures.begin() + deletedIndex);
		m_TextureIndexTagMap.erase(it);

		for (auto& pair : m_TextureIndexTagMap)
		{
			const unsigned int index = pair.second;

			if (index > deletedIndex)
				pair.second--;
		}
	}
} }