#include "Bullet.h"
#include "Novice.h"

// コントラスト
Bullet::Bullet(int speed)
{
	Initial(speed);
}

// 初期化
void Bullet::Initial(int speed)
{
	_pos = { 0, 0 };
	_velocity = { 0, 0 };
	_radius = 8.f;
	_isAlive = false;
	_speed = float(speed);
}

// 移動処理
void Bullet::Move()
{
	// 生存していたら
	if (_isAlive)
	{
		// 画面外に行ったとき
		if (_pos.x < 0 - _radius || _pos.x > float(Screen::_screenW) + _radius ||
			_pos.y < 0 - _radius || _pos.y > float(Screen::_screenH) + _radius)
		{
			_isAlive = false;
			_pos = { 0, 0 };
			_velocity = { 0, 0 };
		}

		// 座標移動
		_pos = { _pos.x + _velocity.x, _pos.y + _velocity.y };
	}
}

// 描画処理
void Bullet::Show()
{
	// 生存していたら
	if (_isAlive)
	{
		Novice::DrawEllipse(int(_pos.x), int(_pos.y), int(_radius), int(_radius), 0.0f, 0xFFFFFFFF, kFillModeSolid);
	}
}

// 当たり判定処理
void Bullet::Collision()
{
	_isAlive = false;
}

///
/// 取得ここから
/// 

// 生存フラグ取得
bool Bullet::GetIsAlive()
{
	return _isAlive;
}

// 座標取得
MyBase::Vec2 Bullet::GetPos()
{
	return _pos;
}

// サイズ取得
float Bullet::GetSize()
{
	return _radius;
}

///
/// 設定ここから
/// 
 
// 射撃
void Bullet::Firing(Vec2 pos, Vec2 vel)
{
	_isAlive = true;
	_pos = pos;
	_velocity = { vel.x * _speed, vel.y * _speed };
}