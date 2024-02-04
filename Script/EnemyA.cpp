#include "EnemyA.h"
#include "Novice.h"

// コントラスト
EnemyA::EnemyA(Vec2 pos, Vec2 vel, float radius)
{
	Initial(pos, vel, radius);
}

// 初期化
void EnemyA::Initial(Vec2 pos, Vec2 vel, float radius)
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
void EnemyA::Move()
{
	if (_isAlive)
	{
		if (_t < 0.5f)
		{
			_pos = { _pos.x + _velocity.x, _pos.y + _velocity.y };
		}
		else
		{
			_pos = { _pos.x + -_velocity.x, _pos.y + -_velocity.y };
		}

		_t += 1.f / 120.f;
		if (_t >= 1.f)
		{
			_t = 0;
		}
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
void EnemyA:: Show()
{
	if (_isAlive)
	{
		Novice::DrawEllipse(int(_pos.x), int(_pos.y), int(_radius), int(_radius), 0.0f, 0x808000FF, kFillModeSolid);
	}

	//Novice::ScreenPrintf(10, 50, "EnemyA : pos(%.0f, %.0f), vel(%.0f, %.0f)", _pos.x, _pos.y, _velocity.x, _velocity.y);
}

// 当たり判定処理
void EnemyA::Collision()
{
	_isAlive = false;

	_respawnTime = _respawnTimeConst;
}
