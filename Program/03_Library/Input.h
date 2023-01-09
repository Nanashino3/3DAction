//******************************************************************
// ファイル名：Input(入力クラス)
// 作　成　日：2023/01/10
#pragma once
#pragma warning(disable:4005)
#define DIRECTINPUT_VERSION 0x800
#include <dinput.h>
#include <dinputd.h>

#include <stdint.h>

namespace tkl
{
class Input
{
public:
	// キーボード対応一覧
	enum class eKeys
	{
		KB_ENTER,	// エンター
		KB_SPACE,	// スペース
		KB_LEFT,	// 矢印(左)
		KB_UP,		// 矢印(上)
		KB_RIGHT,	// 矢印(右)
		KB_DOWN,	// 矢印(下)

		// アルファベット
		KB_A,
		KB_B,
		KB_C,
		KB_D,
		KB_E,
		KB_F,
		KB_G,
		KB_H,
		KB_I,
		KB_J,
		KB_K,
		KB_L,
		KB_M,
		KB_N,
		KB_O,
		KB_P,
		KB_Q,
		KB_R,
		KB_S,
		KB_T,
		KB_U,
		KB_V,
		KB_W,
		KB_X,
		KB_Y,
		KB_Z,

		KB_MAX
	};

	// 初期化
	static void Initialize(HINSTANCE hInstance, HWND hwnd);
	// 更新
	static void Update();
	// 解放
	static void Release();

	//******************************************************************
	// 関数名：キーボード押下検出
	// 引　数：arg1 検出したいキー(複数対応)
	// 戻り値：true : 押下されている、false ： 押下されていない
	// 詳　細：
	//******************************************************************
	template <typename... tKeys>
	static bool IsKeyDown(tKeys... param){
		const eKeys array[] = { static_cast<eKeys>(param)... };
		for(eKeys elem : array){
			if(0x80 & sKeyDwon[sKeyList[static_cast<uint32_t>(elem)]]){ return true; }
		}
		return false;
	}

private:
	static LPDIRECTINPUT8 sInput;
	static LPDIRECTINPUTDEVICE8 sKeyboard;
	static HWND sHwnd;

	static BYTE sKeyDwon[256];											// 押下キー
	static BYTE sKeyList[static_cast<uint32_t>(Input::eKeys::KB_MAX)];	// 対応リスト(キーボード)
};

using eKeys = tkl::Input::eKeys;

} // namespace tkl