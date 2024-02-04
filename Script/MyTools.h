#pragma once
#include "MyBase.h"
#include <math.h>

class MyTools :
    public MyBase
{
public:

    // 長さ
    static float Length(float x, float y);

    // 正規化
    static Vec2 Normalization(float x, float y);

    // 範囲
    static float Clamp(float num, float min, float max);

    // 円と円の当たり判定
    static bool CircleToCircleCollision(Vec2 circleAPos, float circleARadius, Vec2 circleBPos, float circleBRadius);

};

