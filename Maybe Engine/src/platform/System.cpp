#include "System.h"

namespace mb { namespace platform {

	void System::Add(std::vector<unsigned int> ids, unsigned int entityID)
	{
		for (unsigned int i = 0; i < m_EntityIds.size(); i++)
			if (entityID == m_EntityIds[i]) return;

		if (ids.size() >= m_ComponentIds.size())
		{
			for (unsigned int i = 0; i < m_ComponentIds.size(); i++)
			{
				bool found = true;
				for (unsigned int j = 0; j < ids.size(); j++)
				{
					if (m_ComponentIds[i] == ids[j]) break;
					else if (j == ids.size() - 1) found = false;
				}

				if (!found) return;
			}

			m_EntityIds.push_back(entityID);
			OnInitEntity(entityID);

			m_EntityCount++;
		}
	}

}}
