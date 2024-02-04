#include "EnemyC.h"
#include "Novice.h"

// コントラスト
EnemyC::EnemyC(Vec2 pos, Vec2 vel, float radius)
{
	Initial(pos, vel, radius);
}

// 初期化
void EnemyC::Initial(Vec2 pos, Vec2 vel, float radius)
{
	// 基底
	_pos = { pos.x, 0 };
	_velocity = vel;
	_radius = radius;
	_isAlive = true;

	// 弾
	for (int i = 0; i < _bulletNumConst; i++)
	{
		_bullet[i] = new Bullet(2);
	}

	// 派生
	_centerPos = pos;
	_thetaX = float(M_PI) / 90.f;
	_thetaY = float(M_PI) / 45.f;
}

// 移動処理
void EnemyC::Move()
{
	if (_isAlive)
	{
		// 波の座標変化
		_pos.x = sinf(_thetaX) * 300.f;
		_pos.y = sinf(_thetaY) * _velocity.y;

		// 描画座標セット
		_pos = { _pos.x + _centerPos.x, _pos.y + _centerPos.y };

		// シータ値変更
		_thetaX += float(M_PI) / 90.f;
		_thetaY += float(M_PI) / 45.f;
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
void EnemyC::Show()
{
	if (_isAlive)
	{
		Novice::DrawEllipse(int(_pos.x), int(_pos.y), int(_radius), int(_radius), 0.0f, 0x808000FF, kFillModeSolid);
	}

	//Novice::ScreenPrintf(10, 90, "EnemyC : pos(%.0f, %.0f), vel(%.0f, %.0f)", _pos.x, _pos.y, _velocity.x, _velocity.y);
}

// 当たり判定処理
void EnemyC::Collision()
{
	_isAlive = false;

	_respawnTime = _respawnTimeConst;
}
