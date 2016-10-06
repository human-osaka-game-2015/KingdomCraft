#ifndef SCENE_H
#define SCENE_H
enum SceneID;
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

enum SceneID
{
	SCENE_LOGO,
	SCENE_OPENING,
	SCENE_TITLE,
	SCENE_GAME,			// 初めからを選択してゲームに入ったとき
	SCENE_CONTINUE_GAME,	// 続きからを選択してゲームに入ったとき
	SCENE_RESULT,
	SCENE_ENDING,
	FIN
};
#endif