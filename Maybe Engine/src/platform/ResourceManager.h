#pragma once

#include <map>

#include "..\graphics\Texture.h"
#include "..\audio\Sound.h"

namespace mb { namespace platform {

	template <typename T>
	struct ResourceStorage
	{
		std::vector<T*> data;
		std::map<unsigned int, unsigned int> idMap;

		void Destroy()
		{
			for (unsigned int i = 0; i < data.size(); i++)
			{
				delete data[i];
			}
		}
	};

	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

		void AddTexture(const char* path, const unsigned int ID);
		void DeleteTexture(const unsigned int ID);
		graphics::Texture* GetTexture(const unsigned int ID);

		void AddSound(const char* path, const unsigned int ID);
		void LoadSound(const unsigned int ID) { GetSound(ID)->Load(); }
		void DeleteSound(const unsigned int ID);
		audio::Sound* GetSound(const unsigned int ID);
	private:
		template<typename T, typename ...Param>
		void Add(ResourceStorage<T>& resourceStorage, const unsigned int ID, const Param& ...initParams)
		{
			if (resourceStorage.idMap.find(ID) != resourceStorage.idMap.end())
			{
				utils::Log::Warn("Trying to add a texture with an existing id, ignoring the request! (id {})", ID);
				return;
			}

			T* resource = new T(initParams...);

			resourceStorage.data.push_back(resource);
			resourceStorage.idMap.insert({ ID, resourceStorage.data.size() - 1 });
		}

		template<typename T>
		T* Get(ResourceStorage<T>& resourceStorage, const unsigned int ID)
		{
			std::map<unsigned int, unsigned int>::iterator it;

			it = resourceStorage.idMap.find(ID);
			if (it == resourceStorage.idMap.end())
			{
				utils::Log::Warn("Trying to fetch a texture with a non-existing id, ignoring the request! (id {})", ID);
				return nullptr;
			}

			return resourceStorage.data[it->second];
		}

		template<typename T>
		void Delete(ResourceStorage<T>& resourceStorage, const unsigned int& ID)
		{
			std::map<unsigned int, unsigned int>::iterator it;

			it = resourceStorage.idMap.find(ID);
			if (it == resourceStorage.idMap.end())
			{
				utils::Log::Warn("Trying to delete a texture with a non-existing id, ignoring the request! (id {})", ID);
				return;
			}

			const unsigned int deletedIndex = it->second;

			resourceStorage.data.erase(resourceStorage.data.begin() + deletedIndex);
			resourceStorage.idMap.erase(it);

			for (auto& pair : resourceStorage.idMap)
			{
				const unsigned int index = pair.second;

				if (index > deletedIndex)
					pair.second--;
			}
		}
	private:
		ResourceStorage<graphics::Texture> m_Textures;
		ResourceStorage<audio::Sound> m_Sounds;
	};

} }