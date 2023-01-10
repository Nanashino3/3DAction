//******************************************************************
// �t�@�C�����FInput(���̓N���X)
// ��@���@���F2023/01/10
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
	// �L�[�{�[�h�Ή��ꗗ
	enum class eKeys
	{
		KB_ENTER,	// �G���^�[
		KB_SPACE,	// �X�y�[�X
		KB_LEFT,	// ���(��)
		KB_UP,		// ���(��)
		KB_RIGHT,	// ���(�E)
		KB_DOWN,	// ���(��)

		// �A���t�@�x�b�g
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

	// �}�E�X�Ή��ꗗ
	enum class eMouse
	{
		LEFT,
		RIGHT,
		CENTER
	};

	// ������
	static void Initialize(HINSTANCE hInstance, HWND hwnd);
	// �X�V
	static void Update();
	// ���
	static void Release();

	//******************************************************************
	// �֐����F�L�[�{�[�h�������o
	// ���@���Farg1 ���o�������L�[(�����Ή�)
	// �߂�l�Ftrue : ��������Ă���Afalse �F ��������Ă��Ȃ�
	// �ځ@�ׁF
	//******************************************************************
	template <typename... tKeys>
	static bool IsKeyDown(tKeys... params){
		const eKeys array[] = { static_cast<eKeys>(params)... };
		for(eKeys elem : array){
			if(0x80 & sKeyState[sKeyList[static_cast<uint32_t>(elem)]]){ return true; }
		}
		return false;
	}

	//******************************************************************
	// �֐����F�L�[�{�[�h�����g���K�[���o
	// ���@���Farg1 ���o�������L�[(�����Ή�)
	// �߂�l�Ftrue : ��������Ă���Afalse �F ��������Ă��Ȃ�
	// �ځ@�ׁF
	//******************************************************************
	template <typename... tKeys>
	static bool IsKeyDownTrigger(tKeys... params){
		const eKeys array[] = { static_cast<eKeys>(params)... };
		for(eKeys elem : array){
			if(0 != sKeyTrgDown[sKeyList[static_cast<uint32_t>(elem)]]){ return true; }
		}
		return false;
	}

	//******************************************************************
	// �֐����F�L�[�{�[�h�����g���K�[���o
	// ���@���Farg1 ���o�������L�[(�����Ή�)
	// �߂�l�Ftrue : ��������Ă���Afalse �F ��������Ă��Ȃ�
	// �ځ@�ׁF
	//******************************************************************
	template <typename... tKeys>
	static bool IsKeyReleaseTrigger(tKeys... params){
		const eKeys array[] = { static_cast<eKeys>(params)... };
		for(eKeys elem : array){
			if(0 != sKeyTrgRelease[sKeyList[static_cast<uint32_t>(elem)]]){ return true; }
		}
		return false;
	}

	//******************************************************************
	// �֐����F�}�E�X�������o
	// ���@���Farg1 ���o�������L�[(�����Ή�)
	// �߂�l�Ftrue : ��������Ă���Afalse �F ��������Ă��Ȃ�
	// �ځ@�ׁF
	//******************************************************************
	template <typename... tMouse>
	static bool IsMouseDown(tMouse... params){
		const eMouse array[] = { static_cast<eMouse>(params)... };
		for(eMouse elem : array){
			if(0x80 & sMouseState.rgbButtons[static_cast<uint32_t>(elem)]){ return true; }
		}
		return false;
	}

private:
	// �f�o�C�X�擾�p�ϐ�
	static LPDIRECTINPUT8 sInput;
	static LPDIRECTINPUTDEVICE8 sKeyboard;
	static LPDIRECTINPUTDEVICE8 sMouse;
	static HWND sHwnd;

	// �f�o�C�X��Ԑݒ�p�ϐ�
	static BYTE sKeyState[256];			// �����L�[
	static int sKeyXorDown[256];
	static int sKeyTrgDown[256];
	static int sKeyXorRelease[256];
	static int sKeyTrgRelease[256];
	static DIMOUSESTATE2 sMouseState;

	// �Ή����X�g�ϐ�
	static BYTE sKeyList[static_cast<uint32_t>(Input::eKeys::KB_MAX)];
};

using eKeys = tkl::Input::eKeys;
using eMouse = tkl::Input::eMouse;

} // namespace tkl