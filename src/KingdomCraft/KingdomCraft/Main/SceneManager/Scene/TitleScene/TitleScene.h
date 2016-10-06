#ifndef TITLESCENE_H
#define TITLESCENE_H
#include "..//Scene.h"
#include "..//..//..//..//stdafx.h"

class TitleScene :
	public Scene
{
public:
	TitleScene();
	~TitleScene();
	SceneID Control();
	void Draw();
};
#endif