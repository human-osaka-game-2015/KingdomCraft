#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <vector>

template <typename T>
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void AddResource(T* _pResource);

private:
	std::vector<T*> m_pResource;

};

#endif