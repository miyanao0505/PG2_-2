#pragma once
#include "MyTools.h"
#include "Bullet.h"
#include "Screen.h"

class Player :
	public MyTools
{
private:
	// メンバ変数
	// 定数
	static const int _speed = 8;
	static const int _damageTimeConst = 30;
	static const int _reloadTimeConst = 15;

	Vec2 _pos;
	Vec2 _velocity;
	Vec2 _size;
	float _radius;
	int _damageTime;
	//int _respawnTime;
	int _reloadTime;
	bool _isAlive;

	// 弾
	static const int _bulletNumConst = 20;
	Bullet* _bullet[_bulletNumConst];

	// マウス
	Vec2 mousePos;

public:
	// メンバ関数
	Player();									// コントラスト
	void Initial();								// 初期化
	void Move(char keys[]/*, char preKeys[]*/);		// 移動処理
	void Show(bool isDebug);					// 描画処理
	void Collision();							// 当たり判定処理

	// 取得
	Vec2 GetPos();								// 座標取得
	float GetSize();							// サイズ取得
	bool GetIsAlive();							// プレイヤーの存在取得
	int GetBulletNum();							// 弾の数取得
	bool GetBulletIsAlive(int num);				// 弾の存在取得
	Vec2 GetBulletPos(int num);					// 弾の座標取得
	float GetBulletSize(int num);				// 弾のサイズ取得

	// 弾の当たり判定処理
	void BulletCollision(int num);

};

