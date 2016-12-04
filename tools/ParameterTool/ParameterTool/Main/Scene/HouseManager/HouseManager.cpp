#include "HouseManager.h"
#include "House\House.h"
#include "HouseBuildManager\HouseBuildManager.h"
#include "..\FieldMessenger\FieldMessenger.h"


HouseManager::HouseManager(FieldMessenger* _pFieldMessenger, HINSTANCE _hInst) :
m_pFieldMessenger(_pFieldMessenger),
m_hInstance(_hInst)
{
	m_pHouseBuildManager = new HouseBuildManager(m_pFieldMessenger, m_hInstance);
}

HouseManager::~HouseManager()
{
	delete m_pHouseBuildManager;
}

void HouseManager::Control()
{
	switch (m_pHouseBuildManager->GetState())
	{
	case HouseBuildManager::NONE_STATE:
		m_pHouseBuildManager->NoneStateControl();

		for (unsigned int i = 0; i < m_pHouse.size(); i++)
		{
			m_pHouse[i]->Control();
		}

		break;
	case HouseBuildManager::BUILD_STATE:
		if (m_pHouseBuildManager->BuildStateControl())
		{
			m_pHouse.push_back(m_pHouseBuildManager->HouseBuild());
		}

		break;
	case HouseBuildManager::DESTROY_STATE:
		if (m_pHouseBuildManager->DestroyStateControl())
		{
			int NumX, NumY;
			m_pHouseBuildManager->GetNum(&NumX, &NumY);

			for (unsigned int i = 0; i < m_pHouse.size(); i++)
			{
				if (m_pHouse[i]->NumCheck(NumX, NumY))
				{
					delete m_pHouse[i];
					m_pHouse.erase(m_pHouse.begin() + i);
				}
			}
		}

		break;
	}

}

void HouseManager::Draw()
{
	m_pHouseBuildManager->Draw();

	for (unsigned int i = 0; i < m_pHouse.size(); i++)
	{
		m_pHouse[i]->Draw();
	}
}
