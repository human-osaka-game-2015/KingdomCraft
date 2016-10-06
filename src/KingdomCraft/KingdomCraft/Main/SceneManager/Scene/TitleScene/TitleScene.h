#ifndef TITLESCENE_H
#define TITLESCENE_H
#include "..//Scene.h"
enum SceneID;
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