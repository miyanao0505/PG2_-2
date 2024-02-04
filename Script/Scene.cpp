#include "Scene.h"
#include "Novice.h"

// コントラスト
Scene::Scene()
{
	Initial();
}

// 初期化
void Scene::Initial()
{
	_sceneIndex = Title;

	// プレイヤー
	_playerObj = new Player();

	// エネミー
	for (int i = 0; i < _enemyNum; i++)
	{
		Vec2 pos = { float(170 + i * 320), float(240 + i * 40) };
		//Vec2 vel = { 5, 0 };
		float radius = 15;

		if (i % 3 == 0)
		{
			_enemyObj[i] = new EnemyA(pos, { 5, 0 }, radius);
		}
		else if (i % 3 == 1)
		{
			_enemyObj[i] = new EnemyB(pos, { 0, 0 }, radius);
		}
		else
		{
			_enemyObj[i] = new EnemyC(pos, { 5, 50 }, radius);
		}
	}

	// シーン遷移
	_isEnter = false;
	_t = 0;

}

// ローディング
void Scene::SceneLoading(char keys[], char preKeys[], bool isDebug)
{
	/// 
	/// 更新処理ここから
	/// 
	
	if (isDebug)
	{
		if (keys[DIK_RETURN] && !preKeys[DIK_RETURN])
		{

		}
	}
	
	/// 
	/// 更新処理ここまで
	/// 
	
	/// 
	/// 描画処理ここから
	/// 
	
	if (isDebug)
	{

	}
	
	/// 
	/// 描画処理ここまで
	/// 
}

// タイトル
void Scene::SceneTitle(char keys[], char preKeys[], bool isDebug)
{
	/// 
	/// 更新処理ここから
	/// 
	
	if (isDebug)
	{
		
	}

	if (keys[DIK_RETURN] && !preKeys[DIK_RETURN] && !_isEnter)
	{
		_playerObj->Initial();

		for (int i = 0; i < _enemyNum; i++)
		{
			Vec2 pos = { float(170 + i * 320), float(240 + i * 40) };
			float radius = 15;

			if (i % 3 == 0)
			{
				_enemyObj[i]->Initial(pos, { 5, 0 }, radius);
			}
			else if (i % 3 == 1)
			{
				_enemyObj[i]->Initial(pos, { 0, 0 }, radius);
			}
			else
			{
				_enemyObj[i]->Initial(pos, { 5, 50 }, radius);
			}
		}

		_isEnter = true;
		_t = 0;
	}

	if (_isEnter)
	{
		_t += 1 / 60.f;
	}

	if (_t > 1.f)
	{
		_sceneIndex = Game;
		_isEnter = false;

		_t = 0;
	}

	/// 
	/// 更新処理ここまで
	/// 

	/// 
	/// 描画処理ここから
	/// 

	// 背景
	if (isDebug)
	{
		Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x000000FF, kFillModeSolid);
	}

	_playerObj->Show(isDebug);

	for (int i = 0; i < _enemyNum; i++)
	{
		_enemyObj[i]->Show();
	}

	// 
	Novice::DrawBox(0, int(0 - _t * 720), 1280, 720, 0.0f, 0x00000080, kFillModeSolid);
	Novice::ScreenPrintf(585, int(480 - _t * 720), "Push To Enter");

	/// 
	/// 描画処理ここまで
	/// 
}

// ルール
void Scene::SceneRule(char keys[], char preKeys[], bool isDebug)
{
	/// 
	/// 更新処理ここから
	/// 

	if (isDebug)
	{
		if (keys[DIK_RETURN] && !preKeys[DIK_RETURN])
		{
			_sceneIndex = Game;
		}
	}

	/// 
	/// 更新処理ここまで
	/// 

	/// 
	/// 描画処理ここから
	/// 

	// 背景
	if (isDebug)
	{
		Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x008000FF, kFillModeSolid);
	}

	/// 
	/// 描画処理ここまで
	/// 
}

// プレイ
void Scene::SceneGame(char keys[], char preKeys[], bool isDebug)
{
	/// 
	/// 更新処理ここから
	/// 

	if (isDebug)
	{
		if (keys[DIK_RETURN] && !preKeys[DIK_RETURN])
		{
			_sceneIndex = Rule;
		}
	}

	if (keys[DIK_R] && !preKeys[DIK_R])
	{
		_playerObj->Initial();
		
		for (int i = 0; i < _enemyNum; i++)
		{
			Vec2 pos = { float(170 + i * 320), float(240 + i * 40) };
			float radius = 15;

			if (i % 3 == 0)
			{
				_enemyObj[i]->Initial(pos, { 5, 0 }, radius);
			}
			else if (i % 3 == 1)
			{
				_enemyObj[i]->Initial(pos, { 0, 0 }, radius);
			}
			else
			{
				_enemyObj[i]->Initial(pos, { 5, 50 }, radius);
			}
		}
	}

	if(_playerObj->GetIsAlive())
	{
		// プレイヤー
		_playerObj->Move(keys/*, preKeys*/);

		// エネミー
		for (int i = 0; i < _enemyNum; i++)
		{
			_enemyObj[i]->Move();
		}

		// 当たり判定
		// 自機と敵
		for (int i = 0; i < _enemyNum; i++)
		{
			if (_playerObj->GetIsAlive() && _enemyObj[i]->GetIsAlive() &&
				MyTools::CircleToCircleCollision(_playerObj->GetPos(), _playerObj->GetSize(), _enemyObj[i]->GetPos(), _enemyObj[i]->GetSize()))
			{
				// プレイヤーの当たり判定処理
				_playerObj->Collision();

				// 敵の当たり判定処理
				_enemyObj[i]->Collision();
			}
		}
		// 自機の弾と敵
		for (int i = 0; i < _playerObj->GetBulletNum(); i++)
		{
			for (int k = 0; k < _enemyNum; k++)
			{
				if (_playerObj->GetBulletIsAlive(i) && _enemyObj[k]->GetIsAlive() &&
					MyTools::CircleToCircleCollision(_playerObj->GetBulletPos(i), _playerObj->GetBulletSize(i), _enemyObj[k]->GetPos(), _enemyObj[k]->GetSize()))
				{
					// プレイヤーの弾の当たり判定処理
					_playerObj->BulletCollision(i);

					// 敵の当たり判定処理
					_enemyObj[k]->Collision();
				}
			}
		}

		
	}

	if (!_playerObj->GetIsAlive())
	{
		_sceneIndex = GameOver;
	}

	/// 
	/// 更新処理ここまで
	/// 

	/// 
	/// 描画処理ここから
	/// 

	// 背景
	if (isDebug)
	{
		Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x800000FF, kFillModeSolid);
	}

	// 操作方法
	Novice::DrawBox(5, 5, 400, 45, 0.0f, 0x080808BB, kFillModeSolid);
	Novice::DrawBox(5, 5, 400, 45, 0.0f, 0xFFFFFFFF, kFillModeWireFrame);

	Novice::ScreenPrintf(10, 10, "Move : WASD　　Shot : MouseLeftClick");
	Novice::ScreenPrintf(10, 30, "Reset : R");

	// エネミー
	for (int i = 0; i < _enemyNum; i++)
	{
		_enemyObj[i]->Show();
	}

	// プレイヤー
	_playerObj->Show(isDebug);

	/// 
	/// 描画処理ここまで
	/// 
}

// クリア
void Scene::SceneClear(char keys[], char preKeys[], bool isDebug)
{
	/// 
	/// 更新処理ここから
	/// 

	if (isDebug)
	{
		if (keys[DIK_RETURN] && !preKeys[DIK_RETURN])
		{
			_sceneIndex = Title;
		}
	}

	if (keys[DIK_RETURN] && !preKeys[DIK_RETURN] && !_isEnter)
	{
		_isEnter = true;
		_t = 0;
	}

	if (_isEnter)
	{
		_t += 1 / 120.f;
	}

	if (_t > 1.f)
	{
		_sceneIndex = Title;
		_isEnter = false;
	}

	/// 
	/// 更新処理ここまで
	/// 

	/// 
	/// 描画処理ここから
	/// 

	// 背景
	if (isDebug)
	{
		Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x000080FF, kFillModeSolid);
	}

	// 
	Novice::DrawBox(0, int(0 - _t * 720), 1280, 720, 0.0f, 0x00000080, kFillModeSolid);
	Novice::ScreenPrintf(620, int(360 - _t * 720), "Clear");
	Novice::ScreenPrintf(585, int(480 - _t * 720), "Push To Enter");

	/// 
	/// 描画処理ここまで
	/// 
}

// ゲームオーバー
void Scene::SceneGameOver(char keys[], char preKeys[], bool isDebug)
{
	/// 
	/// 更新処理ここから
	/// 

	if (isDebug)
	{
		if (keys[DIK_RETURN] && !preKeys[DIK_RETURN])
		{
			_sceneIndex = Title;
		}
	}

	if (keys[DIK_RETURN] && !preKeys[DIK_RETURN] && !_isEnter)
	{
		_isEnter = true;
		_t = 0;
	}

	if (_isEnter)
	{
		_t += 1 / 120.f;
	}
	
	if(_t > 1.f)
	{
		_sceneIndex = Title;
		_isEnter = false;

		_t = 0;

		_playerObj->Initial();

		for (int i = 0; i < _enemyNum; i++)
		{
			Vec2 pos = { float(170 + i * 320), float(240 + i * 40) };
			float radius = 15;

			if (i % 3 == 0)
			{
				_enemyObj[i]->Initial(pos, { 5, 0 }, radius);
			}
			else if (i % 3 == 1)
			{
				_enemyObj[i]->Initial(pos, { 0, 0 }, radius);
			}
			else
			{
				_enemyObj[i]->Initial(pos, { 5, 50 }, radius);
			}
		}
	}

	/// 
	/// 更新処理ここまで
	/// 

	/// 
	/// 描画処理ここから
	/// 

	// 背景
	if (isDebug)
	{
		Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x808000FF, kFillModeSolid);
	}

	Novice::DrawBox(0, int(0), 1280, 720, 0.0f, 0x00000080, kFillModeSolid);
	Novice::ScreenPrintf(595, int(360 - _t * 720), "Game Over");
	Novice::ScreenPrintf(585, int(480 - _t * 720), "Push To Enter");

	/// 
	/// 描画処理ここまで
	/// 
}
