//******************************************************************
// ファイル名：Input(入力クラス)
// 作　成　日：2023/01/10
#include "../Expansion.h"
#include "Input.h"
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

namespace tkl
{
LPDIRECTINPUT8 Input::sInput = NULL;
LPDIRECTINPUTDEVICE8 Input::sKeyboard = NULL;
LPDIRECTINPUTDEVICE8 Input::sMouse = NULL;
HWND Input::sHwnd = NULL;

BYTE Input::sKeyState[256] = {0};
int Input::sKeyXorDown[256] = {0};
int Input::sKeyTrgDown[256] = {0};
int Input::sKeyXorRelease[256] = {0};
int Input::sKeyTrgRelease[256] = {0};
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

DIMOUSESTATE2 Input::sMouseState;

void Input::Initialize(HINSTANCE hInstance, HWND hwnd)
{
	sHwnd = hwnd;
	HRESULT ret = S_OK;

	// IDirectInput8の作成
	ret = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)(&sInput), NULL);
	if(FAILED(ret)){ return; }

	//******************************************************************
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
	//******************************************************************

	//******************************************************************
	// マウス関連
	ret = sInput->CreateDevice(GUID_SysMouse, &sMouse, NULL);
	if(FAILED(ret)){
		sInput->Release();
		return;
	}
	ret = sMouse->SetDataFormat(&c_dfDIMouse2);
	if(FAILED(ret)){
		sMouse->Release();
		sInput->Release();
		return;
	}
	ret = sMouse->SetCooperativeLevel(sHwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if(FAILED(ret)){
		sMouse->Release();
		sInput->Release();
		return;
	}
	
	// デバイスの設定 
	DIPROPDWORD diprop;
    diprop.diph.dwSize       = sizeof(DIPROPDWORD);
    diprop.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    diprop.diph.dwObj        = 0;
    diprop.diph.dwHow        = DIPH_DEVICE;
    diprop.dwData            = DIPROPAXISMODE_REL;
	ret = sMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph);
	if(FAILED(ret)){
		sMouse->Release();
		sInput->Release();
		return;
	}
	sMouse->Acquire();
	//******************************************************************
}

void Input::Update()
{
	memset(sKeyState, 0, sizeof(sKeyState));
	sKeyboard->GetDeviceState(sizeof(sKeyState), &sKeyState);

	memset(sKeyTrgDown, 0, sizeof(sKeyTrgDown));
	memset(sKeyTrgRelease, 0, sizeof(sKeyTrgRelease));
	for(uint32_t i = 0; i < static_cast<uint32_t>(Input::eKeys::KB_MAX); ++i){
		if(0x80 & sKeyState[sKeyList[i]]){
			// 0x00 xor 0x01 = 0x01, 0x01 xor 0x01 = 0x00
			sKeyTrgDown[sKeyList[i]] = (sKeyXorDown[sKeyList[i]] ^ 0x01);
			sKeyXorDown[sKeyList[i]] = 0x01;

			sKeyXorRelease[sKeyList[i]] = 0;
		}else{
			sKeyXorDown[sKeyList[i]] = 0;

			sKeyTrgRelease[sKeyList[i]] = (sKeyXorRelease[sKeyList[i]] ^ 0x01);
			sKeyXorRelease[sKeyList[i]] = 0x01;
		}
	}

	sMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &sMouseState);
}

void Input::Release()
{}

} // namespace tkl