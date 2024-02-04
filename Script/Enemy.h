#pragma once
#include "MyBase.h"
#include "Bullet.h"

class Enemy :
	public MyBase
{
protected:
	// メンバ変数
	Vec2 _pos;
	Vec2 _velocity;
	float _radius;
	bool _isAlive;

	static const int _respawnTimeConst = 60;
	int _respawnTime;

	// 弾
	static const int _bulletNumConst = 10;
	Bullet* _bullet[_bulletNumConst];

public:
	// メンバ関数
	Enemy();										// コントラスト
	void Initial(Vec2 pos, Vec2 vel, float radius);	// 初期化
	virtual void Move();							// 移動処理
	virtual void Show();							// 描画処理
	virtual void Collision();						// 当たり判定処理

	// 取得
	Vec2 GetPos();				// 座標取得
	float GetSize();			// サイズ取得
	bool GetIsAlive();			// 存在取得

};

