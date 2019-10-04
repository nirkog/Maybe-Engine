#include "System.h"

namespace mb { namespace platform {

	void System::Add(std::vector<unsigned int> ids, unsigned int entityID)
	{
		for (unsigned int i = 0; i < m_EntityIds.size(); i++)
			if (entityID == m_EntityIds[i]) return;

		std::vector<unsigned int> componentIds = m_Components.GetComponentIds();

		if (ids.size() >= componentIds.size())
		{
			for (unsigned int i = 0; i < componentIds.size(); i++)
			{
				bool found = true;
				for (unsigned int j = 0; j < ids.size(); j++)
				{
					if (componentIds[i] == ids[j]) break;
					else if (j == ids.size() - 1) found = false;
				}

				if (!found) return;
			}

			m_EntityIds.push_back(entityID);
			OnInitEntity(entityID);
		}
	}

}}
