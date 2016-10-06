#include "Scene.h"

Scene::Scene(SceneID _sceneID) :
m_sceneID(_sceneID)
{
}


Scene::~Scene()
{
}

SceneID Scene::Control()
{
	return m_sceneID;
}