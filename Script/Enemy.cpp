#include "Enemy.h"
#include "Novice.h"

// コントラスト
Enemy::Enemy()
{
	
}

// 初期化
void Enemy::Initial(Vec2 pos, Vec2 vel, float radius)
{
	_pos = pos;
	_velocity = vel;
	_radius = radius;
	_isAlive = true;

	_respawnTime = 0;

	// 弾
	for (int i = 0; i < _bulletNumConst; i++)
	{
		_bullet[i] = new Bullet(2);
	}
}

// 移動処理
void Enemy::Move()
{
	if (_isAlive)
	{
		_pos = { _pos.x + _velocity.x, _pos.y + _velocity.y };
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
void Enemy::Show()
{
	if (_isAlive)
	{
		Novice::DrawEllipse(int(_pos.x), int(_pos.y), int(_radius), int(_radius), 0.0f, 0x808000FF, kFillModeSolid);
	}
}

// 当たり判定処理
void Enemy::Collision()
{
	_isAlive = false;

	_respawnTime = _respawnTimeConst;
}

///
/// 取得ここから
///

// 座標取得
MyBase::Vec2 Enemy::GetPos()
{
	return _pos;
}

// サイズ取得
float Enemy::GetSize()
{
	return _radius;
}

// 存在取得
bool Enemy::GetIsAlive()
{
	return _isAlive;
}
