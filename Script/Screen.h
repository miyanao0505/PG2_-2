#pragma once
#include "MyBase.h"

class Screen :
	public MyBase
{
public:
	static int _screenW;
	static int _screenH;

	// 値設定
	static void SetScreenSize(int screenW = 1280, int screenH = 720);	// スクリーンサイズの設定
};

