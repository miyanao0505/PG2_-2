#include "MyTools.h"

// 長さ
float MyTools::Length(float x, float y)
{
	return sqrtf(x * x + y * y);
}

// 正規化
MyBase::Vec2 MyTools::Normalization(float x, float y)
{
	float length = Length(x, y);

	if (length != 0) {
		x = x / length;
		y = y / length;
	}
	
	return Vector2{ x,y };
}

// 範囲
float MyTools::Clamp(float num, float min, float max)
{
	if (num < min)
	{
		return min;
	}
	if (num > max)
	{
		return max;
	}
	return num;
}

// 円と円の当たり判定
bool MyTools::CircleToCircleCollision(Vec2 circleAPos, float circleARadius, Vec2 circleBPos, float circleBRadius)
{
	float length = Length(circleAPos.x - circleBPos.x, circleAPos.y - circleBPos.y);

	if (length <= circleARadius + circleBRadius)
	{
		return true;
	}
	return false;
}
