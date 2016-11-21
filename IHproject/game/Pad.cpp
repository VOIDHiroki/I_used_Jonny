#include "stdafx.h"
#include "Pad.h"
#include <limits.h>



#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) )  // Default to 24% of the +/- 32767 range.   This is a reasonable default value but can be altered if needed.

CPad::CPad() : m_padNo(0)
{
	memset(&m_state, 0, sizeof(m_state));
	memset(m_trigger, 0, sizeof(m_trigger));
	memset(m_press, 0, sizeof(m_press));

	m_lStickX = 0.0f;
	m_lStickY = 0.0f;
	m_rStickX = 0.0f;
	m_rStickY = 0.0f;
}

CPad::~CPad()
{

}

struct VirtualPadToXPad {
	EnButton vButton;		//!<仮想ボタン。
	DWORD	 xButton;		//!<XBoxコントローラのボタン。
};

const VirtualPadToXPad vPadToXPadTable[enButtonNum] = {
	{ enButtonUp, XINPUT_GAMEPAD_DPAD_UP },			//上
	{ enButtonDown, XINPUT_GAMEPAD_DPAD_DOWN },		//下
	{ enButtonLeft, XINPUT_GAMEPAD_DPAD_LEFT },		//左
	{ enButtonRight, XINPUT_GAMEPAD_DPAD_RIGHT },	//右
	{ enButtonA, XINPUT_GAMEPAD_A },				//Aボタン
	{ enButtonB, XINPUT_GAMEPAD_B },				//Bボタン
	{ enButtonX, XINPUT_GAMEPAD_X },				//Xボタン
	{ enButtonY, XINPUT_GAMEPAD_Y },				//Yボタン
	{ enButtonSelect, XINPUT_GAMEPAD_BACK },		//セレクトボタン
	{ enButtonStart, XINPUT_GAMEPAD_START },		//スタートボタン
	{ enButtonRB1, XINPUT_GAMEPAD_RIGHT_SHOULDER },	//RB1ボタン
	{ enButtonRB2, 0 },								//RB2ボタン
	{ enButtonRB3, XINPUT_GAMEPAD_RIGHT_THUMB },	//RB3ボタン
	{ enButtonLB1, XINPUT_GAMEPAD_LEFT_SHOULDER },	//LB1ボタン
	{ enButtonLB2, 0 },								//LB2ボタン
	{ enButtonLB3, XINPUT_GAMEPAD_LEFT_THUMB },		//LB3ボタン
};

struct VirtualPadToKeyboard{
	EnButton vButton;
	DWORD keyCoord;
};

const VirtualPadToKeyboard vPadToKeyboardTable[enButtonNum] = {
	{ enButtonUp, '8' },				//上
	{ enButtonDown, '2' },				//下
	{ enButtonLeft, '4' },				//左
	{ enButtonRight, '6' },				//右
	{ enButtonA, 'J' },					//Aボタン
	{ enButtonB, 'K' },					//Bボタン
	{ enButtonX, 'I' },					//Xボタン
	{ enButtonY, 'O' },					//Yボタン
	{ enButtonSelect, VK_SPACE },		//セレクトボタン
	{ enButtonStart, VK_RETURN },		//スタートボタン
	{ enButtonRB1, '7' },				//RB1ボタン
	{ enButtonRB2, '8' },				//RB2ボタン
	{ enButtonRB3, '9' },				//RB3ボタン
	{ enButtonLB1, 'B' },				//LB1ボタン
	{ enButtonLB2, 'N' },				//LB2ボタン
	{ enButtonLB3, 'M' },				//LB3ボタン
};

void CPad::Update()
{
	DWORD result = XInputGetState(m_padNo, &m_state.state);
	if (result == ERROR_SUCCESS){
		//接続されている
		m_state.bConnected = true;
		for (const VirtualPadToXPad& vPadToXPad : vPadToXPadTable){						//foreach(綴りあってるかわからん)ですって
			if (m_state.state.Gamepad.wButtons & vPadToXPad.xButton){					//現在押されているボタンと各ボタンの論理和をとる
				m_trigger[vPadToXPad.vButton] = 1 ^ m_press[vPadToXPad.vButton];		//押された瞬間の判定。1f以降は判定されない(＾は排他的論理和をとる演算子らしい)
				m_press[vPadToXPad.vButton] = 1;
			}
			else{
				m_trigger[vPadToXPad.vButton] = 0;
				m_press[vPadToXPad.vButton] = 0;
			}
		}
		if ((m_state.state.Gamepad.sThumbLX < INPUT_DEADZONE &&
			m_state.state.Gamepad.sThumbLX > -INPUT_DEADZONE) &&
			(m_state.state.Gamepad.sThumbLY < INPUT_DEADZONE &&
			m_state.state.Gamepad.sThumbLY > -INPUT_DEADZONE))
		{
			m_state.state.Gamepad.sThumbLX = 0;
			m_state.state.Gamepad.sThumbLY = 0;
			m_lStickX = 0.0f;
			m_lStickY = 0.0f;
		}
		else{
			//左スティックの入力量//shortをfloatに変更?
			if (m_state.state.Gamepad.sThumbLX > 0){
				m_lStickX = static_cast<float>(m_state.state.Gamepad.sThumbLX) / -SHRT_MAX;
			}
			else {
				m_lStickX = static_cast<float>(m_state.state.Gamepad.sThumbLX) / SHRT_MIN;
			}
			if (m_state.state.Gamepad.sThumbLY > 0){
				m_lStickY = static_cast<float>(m_state.state.Gamepad.sThumbLY) / -SHRT_MAX;
			}
			else {
				m_lStickY = static_cast<float>(m_state.state.Gamepad.sThumbLY) / SHRT_MIN;
			}
		}
		if ((m_state.state.Gamepad.sThumbRX < INPUT_DEADZONE &&
			m_state.state.Gamepad.sThumbRX > -INPUT_DEADZONE) &&
			(m_state.state.Gamepad.sThumbRY < INPUT_DEADZONE &&
			m_state.state.Gamepad.sThumbRY > -INPUT_DEADZONE))
		{
			m_state.state.Gamepad.sThumbRX = 0;
			m_state.state.Gamepad.sThumbRY = 0;
			m_rStickX = 0.0f;
			m_rStickY = 0.0f;
		}
		else{
			//右スティックの入力量//shortをfloatに変更?
			if (m_state.state.Gamepad.sThumbRX > 0){
				m_rStickX = static_cast<float>(m_state.state.Gamepad.sThumbRX) / -SHRT_MAX;
			}
			else {
				m_rStickX = static_cast<float>(m_state.state.Gamepad.sThumbRX) / SHRT_MIN;
			}
			if (m_state.state.Gamepad.sThumbRY > 0){
				m_rStickY = static_cast<float>(m_state.state.Gamepad.sThumbRY) / -SHRT_MAX;
			}
			else {
				m_rStickY = static_cast<float>(m_state.state.Gamepad.sThumbRY) / SHRT_MIN;
			}
		}
	}
	else{
		//未接続
		if (m_state.bConnected){
			memset(&m_state, 0, sizeof(m_state));
			memset(m_trigger, 0, sizeof(m_trigger));
			memset(m_press, 0, sizeof(m_press));
		}
		m_lStickX = 0.0f;
		m_lStickY = 0.0f;
		m_rStickX = 0.0f;
		m_rStickY = 0.0f;

		if (GetAsyncKeyState(VK_LEFT)){
			m_rStickX = 1.0f;
		}
		else if (GetAsyncKeyState(VK_RIGHT)){
			m_rStickX = -1.0f;
		}
		if (GetAsyncKeyState(VK_UP)){
			m_rStickY = -1.0f;
		}
		else if (GetAsyncKeyState(VK_DOWN)){
			m_rStickY = 1.0f;
		}

		//スティックの入力量を正規化
		float t = fabsf(m_rStickX) + fabsf(m_rStickY);
		if (t > 0.0f){
			m_rStickX /= t;
			m_rStickY /= t;
		}

		if (GetAsyncKeyState('A')){
			m_lStickX = 1.0f;
		}
		else if (GetAsyncKeyState('D')){
			m_lStickX = -1.0f;
		}
		if (GetAsyncKeyState('W')){
			m_lStickY = -1.0f;
		}
		else if (GetAsyncKeyState('S')){
			m_lStickY = 1.0f;
		}
		//スティックの入力量を正規化
		t = fabsf(m_lStickX) + fabsf(m_lStickY);
		if (t > 0.0f){
			m_lStickX /= t;
			m_lStickY /= t;
		}

		for (const VirtualPadToKeyboard& vPadToKeyboard : vPadToKeyboardTable){
			if (GetAsyncKeyState(vPadToKeyboard.keyCoord)){
				m_trigger[vPadToKeyboard.vButton] = 1 ^ m_press[vPadToKeyboard.vButton];
				m_press[vPadToKeyboard.vButton] = 1;
			}
			else {
				m_trigger[vPadToKeyboard.vButton] = 0;
				m_press[vPadToKeyboard.vButton] = 0;
			}
		}
	}
}



