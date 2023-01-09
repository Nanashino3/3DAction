//******************************************************************
// ファイル名：Input(入力クラス)
// 作　成　日：2023/01/10
#include "Input.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

namespace tkl
{
LPDIRECTINPUT8 Input::sInput = NULL;
LPDIRECTINPUTDEVICE8 Input::sKeyboard = NULL;
HWND Input::sHwnd = NULL;

BYTE Input::sKeyDwon[256] = {0};
BYTE Input::sKeyList[static_cast<uint32_t>(Input::eKeys::KB_MAX)] = {
	DIK_RETURN,	// エンター
	DIK_SPACE,	// スペース
	DIK_LEFT,	// 矢印(左)
	DIK_UP,		// 矢印(上)
	DIK_RIGHT,	// 矢印(右)
	DIK_DOWN,	// 矢印(下)

	// アルファベット
	DIK_A,
	DIK_B,
	DIK_C,
	DIK_D,
	DIK_E,
	DIK_F,
	DIK_G,
	DIK_H,
	DIK_I,
	DIK_J,
	DIK_K,
	DIK_L,
	DIK_M,
	DIK_N,
	DIK_O,
	DIK_P,
	DIK_Q,
	DIK_R,
	DIK_S,
	DIK_T,
	DIK_U,
	DIK_V,
	DIK_W,
	DIK_X,
	DIK_Y,
	DIK_Z
};

void Input::Initialize(HINSTANCE hInstance, HWND hwnd)
{
	sHwnd = hwnd;
	HRESULT ret = S_OK;

	// IDirectInput8の作成
	ret = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)(&sInput), NULL);
	if(FAILED(ret)){ return; }

	//***********************************************************
	// キーボード関連
	ret = sInput->CreateDevice(GUID_SysKeyboard, &sKeyboard, NULL);
	if(FAILED(ret)){
		sInput->Release();
		return;
	}
	ret = sKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(ret)){
		sKeyboard->Release();
		sInput->Release();
		return;
	}
	ret = sKeyboard->SetCooperativeLevel(sHwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	if(FAILED(ret)){
		sKeyboard->Release();
		sInput->Release();
		return;
	}
	sKeyboard->Acquire();
	//***********************************************************
}

void Input::Update()
{
	memset(sKeyDwon, 0, sizeof(sKeyDwon));
	sKeyboard->GetDeviceState(sizeof(sKeyDwon), &sKeyDwon);
}

void Input::Release()
{}

} // namespace tkl