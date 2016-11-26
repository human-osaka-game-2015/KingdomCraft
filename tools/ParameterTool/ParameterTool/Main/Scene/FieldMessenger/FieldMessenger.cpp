#include "FieldMessenger.h"
#include "..\FieldManager\FieldManager.h"


FieldMessenger::FieldMessenger(FieldManager* _pFieldManager) :
m_pFieldManager(_pFieldManager)
{
}

FieldMessenger::~FieldMessenger()
{
}

bool FieldMessenger::HouseBuildMessage(const D3DXVECTOR2* _pBuildPos)
{
	return m_pFieldManager->HouseBuild(_pBuildPos);
}

bool FieldMessenger::HouseDestroyMessage(const D3DXVECTOR2* _pDestroyPos)
{
	return m_pFieldManager->HouseDestroy(_pDestroyPos);
}
