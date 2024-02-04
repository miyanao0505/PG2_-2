#include "Player.h"
#include "Novice.h"

// コントラスト
Player::Player()
{
	Initial();
}

// 初期化
void Player::Initial()
{
	_pos = { 640, 600 };
	_velocity = { 0, 0 };
	_size = { 64, 64 };
	_radius = 32.f;
	_damageTime = 0;
	//_respawnTime = 0;
	_reloadTime = 0;
	_isAlive = true;

	// 弾
	for (int i = 0; i < _bulletNumConst; i++)
	{
		_bullet[i] = new Bullet(5);
	}

	// マウス
	mousePos = { 0, 0 };
}

// 移動処理
void Player::Move(char keys[]/*, char preKeys[]*/)
{
	int mouseX = 0, mouseY = 0;

	if(_isAlive)
	{
		// マウス座標セット
		Novice::GetMousePosition(&mouseX, &mouseY);
		mousePos = { float(mouseX), float(mouseY) };

		_velocity = { 0, 0 };

		if (keys[DIK_W])
		{
			_velocity.y -= _speed;
		}
		if (keys[DIK_S])
		{
			_velocity.y += _speed;
		}
		if (keys[DIK_A])
		{
			_velocity.x -= _speed;
		}
		if (keys[DIK_D])
		{
			_velocity.x += _speed;
		}
		if (Novice::IsPressMouse(0) && _reloadTime <= 0)
		{
			for (int i = 0; i < _bulletNumConst; i++)
			{
				if (!_bullet[i]->GetIsAlive())
				{
					_bullet[i]->Firing(_pos, MyTools::Normalization(mousePos.x - _pos.x, mousePos.y - _pos.y));
					_reloadTime = _reloadTimeConst;
					break;
				}
			}
		}

		// 弾の移動処理
		for (int i = 0; i < _bulletNumConst; i++)
		{
			_bullet[i]->Move();
		}

		// 弾のリロード処理
		if (_reloadTime > 0)
		{
			_reloadTime--;
		}

		// 正規化
		_velocity = MyTools::Normalization(_velocity.x, _velocity.y);
		_velocity = { _velocity.x * _speed, _velocity.y * _speed };

		// 座標移動
		_pos = { _pos.x + _velocity.x, _pos.y + _velocity.y };

		// 画面内に収める
		_pos.x = MyTools::Clamp(_pos.x, 0 + _radius, float(Screen::_screenW) - _radius);
		_pos.y = MyTools::Clamp(_pos.y, 0 + _radius, float(Screen::_screenH) - _radius);
	}
}

// 描画処理
void Player::Show(bool isDebug)
{
	// マーカー
	if (_isAlive)
	{
		Novice::DrawEllipse(int(mousePos.x), int(mousePos.y), 16, 16, 0.0f, 0xFFFFFFFF, kFillModeWireFrame);
		Novice::DrawLine(int(mousePos.x - 8), int(mousePos.y), int(mousePos.x + 8), int(mousePos.y), 0xFFFFFFFF);
		Novice::DrawLine(int(mousePos.x), int(mousePos.y - 8), int(mousePos.x), int(mousePos.y + 8), 0xFFFFFFFF);
	}

	// 弾の描画
	for (int i = 0; i < _bulletNumConst; i++)
	{
		_bullet[i]->Show();
	}

	// プレイヤーの描画
	if (_isAlive)
	{
		Novice::DrawEllipse(int(_pos.x), int(_pos.y), int(_radius), int(_radius), 0.0f, 0xFFFFFFFF, kFillModeSolid);
	}

	if (isDebug)
	{
		Novice::ScreenPrintf(10, 30, "Player : Pos(%4.0f, %4.0f), Vel(%2.0f, %2.0f), Radius(%.0f)", _pos.x, _pos.y, _velocity.x, _velocity.y, _radius);
	}
}

// 当たり判定処理
void Player::Collision()
{
	_isAlive = false;
}

// 取得
// 座標取得
MyBase::Vec2 Player::GetPos()
{
	return _pos;
}

// サイズ取得
float Player::GetSize()
{
	return _radius;
}

// 存在取得
bool Player::GetIsAlive()
{
	return _isAlive;
}

// 弾の数取得
int Player::GetBulletNum()
{
	return _bulletNumConst;
}

// 弾の存在取得
bool Player::GetBulletIsAlive(int num)
{
	return _bullet[num]->GetIsAlive();
}

// 弾の座標取得
MyBase::Vec2 Player::GetBulletPos(int num)
{
	return _bullet[num]->GetPos();
}

// 弾のサイズ取得
float Player::GetBulletSize(int num)
{
	return _bullet[num]->GetSize();
}


// 弾の当たり判定処理
void Player::BulletCollision(int num)
{
	return _bullet[num]->Collision();
}
