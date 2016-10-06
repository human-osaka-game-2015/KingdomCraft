// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once
#include <vector>
#include <Windows.h>

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
