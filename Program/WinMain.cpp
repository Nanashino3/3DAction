#include <DxLib.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(1024, 768, 32);
	if(DxLib_Init() == -1){ return -1; }

	SetDrawScreen(DX_SCREEN_BACK);

	while(ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		ClearDrawScreen();
		DrawBox(0, 0, 600, 400, GetColor(255, 255, 0), true);

		ScreenFlip();
	}
	DxLib_End();

	return 0;
}