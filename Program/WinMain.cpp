
#include "DxLib.h"
#include "03_Library/Input.h"

#include <iostream>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(1024, 768, 32);
	if(DxLib_Init() == -1){ return -1; }

	SetDrawScreen(DX_SCREEN_BACK);

	HWND hWnd = GetMainWindowHandle();
	tkl::Input::Initialize(hInstance, hWnd);

	while(ProcessMessage() != -1){

		ClearDrawScreen();

		// 入力システムの更新
		tkl::Input::Update();

		if (tkl::Input::IsKeyDown(tkl::eKeys::KB_DOWN)){
			DrawString(0, 0, "下押下中", -1);
		}
		if (tkl::Input::IsKeyDown(tkl::eKeys::KB_UP)){
			DrawString(0, 0, "上押下中", -1);
		}
		if (tkl::Input::IsKeyDown(tkl::eKeys::KB_LEFT)){
			DrawString(0, 0, "左押下中", -1);
		}
		if (tkl::Input::IsKeyDown(tkl::eKeys::KB_RIGHT)){
			DrawString(0, 0, "右押下中", -1);
		}


		ScreenFlip();
	}
	DxLib_End();

	return 0;
}