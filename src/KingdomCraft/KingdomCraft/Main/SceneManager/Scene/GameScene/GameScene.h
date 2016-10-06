#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "..//Scene.h"
enum SceneID;
class GameScene :
	public Scene
{
public:
	GameScene();
	~GameScene();
	SceneID Control();
	void Draw();
};
#endif