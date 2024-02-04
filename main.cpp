#include <Novice.h>
#include "Script/Scene.h"
#include "Script/LoadRes.h"
#include "Script/Screen.h"

const char kWindowTitle[] = "ShootingGame";

int Screen::_screenW;
int Screen::_screenH;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// スクリーンのサイズ設定
	Screen::SetScreenSize(1280, 720);

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, Screen::_screenW, Screen::_screenH);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// シーン
	Scene* sceneObj = new Scene();

	// 画像
	LoadRes::LoadResNovice();

	// デバッグ
	bool isDebug = false;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		// デバッグ切り替え
		if (keys[DIK_Q] && !preKeys[DIK_Q])
		{
			isDebug = !isDebug;
		}

		// デバッグ処理
		if (isDebug)
		{
			if (keys[DIK_0] && !preKeys[DIK_0])
			{
				sceneObj->_sceneIndex = Scene::Loading;
			}
			if (keys[DIK_1] && !preKeys[DIK_1])
			{
				sceneObj->_sceneIndex = Scene::Title;
			}
			if (keys[DIK_2] && !preKeys[DIK_2])
			{
				sceneObj->_sceneIndex = Scene::Rule;
			}
			if (keys[DIK_3] && !preKeys[DIK_3])
			{
				sceneObj->_sceneIndex = Scene::Game;
			}
			if (keys[DIK_4] && !preKeys[DIK_4])
			{
				sceneObj->_sceneIndex = Scene::Clear;
			}
			if (keys[DIK_5] && !preKeys[DIK_5])
			{
				sceneObj->_sceneIndex = Scene::GameOver;
			}
		}

		switch (sceneObj->_sceneIndex)
		{
		case Scene::Loading:

			sceneObj->SceneLoading(keys, preKeys, isDebug);

			break;
		case Scene::Title:
			
			sceneObj->SceneTitle(keys, preKeys, isDebug);
			
			break;
		case Scene::Rule:
			
			sceneObj->SceneRule(keys, preKeys, isDebug);
			
			break;
		case Scene::Game:
			
			sceneObj->SceneGame(keys, preKeys, isDebug);
			
			break;
		case Scene::Clear:
			
			sceneObj->SceneClear(keys, preKeys, isDebug);
			
			break;
		case Scene::GameOver:
			
			sceneObj->SceneGameOver(keys, preKeys, isDebug);
			
			break;
		default:
			break;
		}

		// デバッグ
		if (isDebug)
		{
			// 背景
			Novice::DrawBox(5, 5, 800, 200, 0.0f, 0x080808BB, kFillModeSolid);
			Novice::DrawBox(5, 5, 800, 200, 0.0f, 0xFFFFFFFF, kFillModeWireFrame);

			// 文字
			Novice::ScreenPrintf(10, 10, "Scene : 0.Loading, 1.Title, 2.Rule, 3.Game, 4.Clear, 5.GameOver	SceneIndex : %d", sceneObj->_sceneIndex);
		}

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// デリート
	delete sceneObj;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
