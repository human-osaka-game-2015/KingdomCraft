#ifndef FIELDMESSENGER_H
#define FIELDMESSENGER_H
#include <d3dx9.h>

class FieldManager;

class FieldMessenger
{
public:
	FieldMessenger(FieldManager* _pFieldManager);
	~FieldMessenger();
	bool HouseBuildMessage(const D3DXVECTOR2* _pBuildPos);
	bool HouseDestroyMessage(const D3DXVECTOR2* _pDestroyPos);

private:
	FieldManager* m_pFieldManager;

};


#endif // !FIELDMESSENGER_H
