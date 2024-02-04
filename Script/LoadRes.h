#pragma once
#include <Novice.h>
#include <map>

class LoadRes
{
public:
	// スライドの構造体
	static struct Sprite
	{
		int path = 0;	// フォルダのどこにある
		int w = 0;		// 幅
		int h = 0;		// 高さ
	}structSP;
	// スライドシート構造体
	static struct SpriteList
	{
		int path = 0;		// フォルダのどこにある
		int x = 0;			// シート上のスライドの左上、X座標
		int y = 0;			// 　　　　　　　　　　　　　Y座標
		int w = 0;			// スライドの幅
		int h = 0;			// スライドの高さ
		int listW = 0;		// シートの幅
		int listH = 0;		// シートの高さ
	}structSL;

	// 例：
	// スライドは一つ目の様子、スライドシートは二つ目の様子、変数名だけを変えるといい
	// inline static Sprite _spriteTemplate;
	// inline static std::map<int, SpriteList> _spriteListTemplate;
	// inline static std::map<int, SpriteList> _spriteListTemplate_UI;

	


	static void LoadResNovice();
};

