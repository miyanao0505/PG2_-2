#pragma once
#include "Enemy.h"
#define _USE_MATH_DEFINES
#include "math.h"

class EnemyB :
    public Enemy
{
protected:
	// メンバ変数
	float _t;

public:
	// メンバ関数
	EnemyB(Vec2 pos, Vec2 vel, float radius);			// コントラスト
	void Initial(Vec2 pos, Vec2 vel, float radius);		// 初期化
	void Move() override;								// 移動処理
	void Show() override;								// 描画処理
	void Collision() override;							// 当たり判定処理

	void SetVelocity(Vec2 playerPos);					// 速度の設定

};

