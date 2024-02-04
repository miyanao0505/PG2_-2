#pragma once
#include "MyTools.h"
#include "Screen.h"

class Bullet :
	public MyTools
{
private:
	// メンバ変数
	Vec2 _pos;
	Vec2 _velocity;
	float _radius;
	bool _isAlive;
	float _speed;

public:
	// メンバ関数
	Bullet(int speed);			// コントラスト
	void Initial(int speed);	// 初期化
	void Move();				// 移動処理
	void Show();				// 描画処理
	void Collision();			// 当たり判定処理

	// 取得
	bool GetIsAlive();			// 生存フラグの取得
	Vec2 GetPos();				// 座標取得
	float GetSize();			// サイズ取得

	// 設定
	void Firing(Vec2 pos, Vec2 vel);	// 射撃

};

