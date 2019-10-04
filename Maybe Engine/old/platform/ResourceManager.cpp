#include "ResourceManager.h"

#include "..\utils\Log.h"

namespace mb { namespace platform {

	ResourceManager::ResourceManager()
	{

	}

	ResourceManager::~ResourceManager()
	{
		m_Textures.Destroy();
		m_Sounds.Destroy();
	}

	void ResourceManager::AddTexture(const char* path, const unsigned int ID)
	{
		Add<graphics::Texture>(m_Textures, ID, path);
	}

	graphics::Texture* ResourceManager::GetTexture(const unsigned int ID)
	{
		return Get<graphics::Texture>(m_Textures, ID);
	}

	void ResourceManager::DeleteTexture(const unsigned int ID)
	{
		Delete<graphics::Texture>(m_Textures, ID);
	}

	void ResourceManager::AddSound(const char* path, const unsigned int ID)
	{
		Add<audio::Sound>(m_Sounds, ID, path);
	}

	audio::Sound* ResourceManager::GetSound(const unsigned int ID)
	{
		return Get<audio::Sound>(m_Sounds, ID);
	}

	void ResourceManager::DeleteSound(const unsigned int ID)
	{
		Delete<audio::Sound>(m_Sounds, ID);
	}

} }