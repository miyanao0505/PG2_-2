#include "EnemyB.h"
#include "Novice.h"

// コントラスト
EnemyB::EnemyB(Vec2 pos, Vec2 vel, float radius)
{
	Initial(pos, vel, radius);
}

// 初期化
void EnemyB::Initial(Vec2 pos, Vec2 vel, float radius)
{
	// 基底
	_pos = pos;
	_velocity = vel;
	_radius = radius;
	_isAlive = true;

	// 弾
	for (int i = 0; i < _bulletNumConst; i++)
	{
		_bullet[i] = new Bullet(2);
	}

	// 派生
	_t = 0;
}

// 移動処理
void EnemyB::Move()
{
	if (_isAlive)
	{
		// 座標計算
		_pos.x += _velocity.x;
		_pos.y += _velocity.y;
	}
	else
	{
		_respawnTime--;
		if (_respawnTime <= 0)
		{
			_isAlive = true;
		}
	}
}

// 描画処理
void EnemyB::Show()
{
	if (_isAlive)
	{
		Novice::DrawEllipse(int(_pos.x), int(_pos.y), int(_radius), int(_radius), 0.0f, 0x808000FF, kFillModeSolid);
	}

	//Novice::ScreenPrintf(10, 70, "EnemyB : pos(%.0f, %.0f), vel(%.0f, %.0f)", _pos.x, _pos.y, _velocity.x, _velocity.y);
}

// 当たり判定処理
void EnemyB::Collision()
{
	_isAlive = false;

	_respawnTime = _respawnTimeConst;
}

// 速度設定
void EnemyB::SetVelocity(Vec2 playerPos)
{
	_velocity.x = playerPos.x - _pos.x;
	_velocity.y = playerPos.y - _pos.y;
}
