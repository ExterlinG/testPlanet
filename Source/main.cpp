#include <DxLib.h>
#include "App.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetGraphMode(1920, 1080, 32);
	SetOutApplicationLogValidFlag(FALSE); // ログを出さない
#if _DEBUG // デバッグビルドのときだけ
	SetMainWindowText("デバッグウィンドウ");
	SetWindowSizeExtendRate(1.0);
	ChangeWindowMode(TRUE); // Windowモードの場合
#endif
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);
	AppInit();	//初期化
	int mStartTime = GetNowCount();
	while (ProcessMessage() >= 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 ) {
		int cur = GetNowCount();
		if (cur < mStartTime + 16) //120fps対策
			continue;
		mStartTime = cur;
		AppUpdate();	//処理
		ClearDrawScreen();
		AppDraw();	//描画
		ScreenFlip();
	}
	AppRelease();
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
} 