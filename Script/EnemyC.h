#pragma once
#include "Enemy.h"
#define _USE_MATH_DEFINES
#include "math.h"

class EnemyC :
    public Enemy
{
protected:
	// メンバ変数
	Vec2 _centerPos;
	float _thetaX;
	float _thetaY;

public:
	// メンバ関数
	EnemyC(Vec2 pos, Vec2 vel, float radius);			// コントラスト
	void Initial(Vec2 pos, Vec2 vel, float radius);		// 初期化
	void Move() override;								// 移動処理
	void Show() override;								// 描画処理
	void Collision() override;							// 当たり判定処理
};

