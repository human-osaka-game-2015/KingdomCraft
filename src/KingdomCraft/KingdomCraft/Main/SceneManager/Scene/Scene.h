#ifndef SCENE_H
#define SCENE_H
#include "..//..//..//stdafx.h"
class Scene
{
public:
	Scene(SceneID _sceneID);
	~Scene();
	virtual void Draw() = 0;
	virtual SceneID Control();
	SceneID GetSceneID(){ return m_sceneID; }
protected:
	SceneID m_sceneID;
};
#endif