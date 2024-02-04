#pragma once
#include "MyTools.h"
#include "Player.h"
#include "EnemyA.h"
#include "EnemyB.h"
#include "EnemyC.h"

class Scene :
	public MyTools
{
public:
	// メンバ変数
	// ゲームのシーン
	inline static enum SceneIndex {
		Loading,				// ゲーム内容の初期化などに使う
		Title,					// タイトル
		Rule,					// 説明、ルール
		Game,					// プレイ
		Clear,					// クリア
		GameOver				// ゲームオーバー
	}_sceneIndex;

	// プレイヤー
	Player* _playerObj;

	// エネミー
	static const int _enemyNum = 3;
	Enemy* _enemyObj[_enemyNum];

	// シーン遷移
	bool _isEnter;
	float _t;

	// メンバ関数
	Scene();
	void Initial();
	void SceneLoading(char keys[], char preKeys[], bool isDebug);
	void SceneTitle(char keys[], char preKeys[], bool isDebug);
	void SceneRule(char keys[], char preKeys[], bool isDebug);
	void SceneGame(char keys[], char preKeys[], bool isDebug);
	void SceneClear(char keys[], char preKeys[], bool isDebug);
	void SceneGameOver(char keys[], char preKeys[], bool isDebug);

};

