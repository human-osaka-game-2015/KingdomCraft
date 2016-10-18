#include "ResourceManager.h"

template<typename T>
ResourceManager<T>::ResourceManager()
{
}

template<typename T>
ResourceManager<T>::~ResourceManager()
{
}

template<typename T>
void ResourceManager<T>::AddResource(T* _pResource)
{
	m_pResource.push_back(_pResource);
}
