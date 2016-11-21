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
	EnButton vButton;		//!<���z�{�^���B
	DWORD	 xButton;		//!<XBox�R���g���[���̃{�^���B
};

const VirtualPadToXPad vPadToXPadTable[enButtonNum] = {
	{ enButtonUp, XINPUT_GAMEPAD_DPAD_UP },			//��
	{ enButtonDown, XINPUT_GAMEPAD_DPAD_DOWN },		//��
	{ enButtonLeft, XINPUT_GAMEPAD_DPAD_LEFT },		//��
	{ enButtonRight, XINPUT_GAMEPAD_DPAD_RIGHT },	//�E
	{ enButtonA, XINPUT_GAMEPAD_A },				//A�{�^��
	{ enButtonB, XINPUT_GAMEPAD_B },				//B�{�^��
	{ enButtonX, XINPUT_GAMEPAD_X },				//X�{�^��
	{ enButtonY, XINPUT_GAMEPAD_Y },				//Y�{�^��
	{ enButtonSelect, XINPUT_GAMEPAD_BACK },		//�Z���N�g�{�^��
	{ enButtonStart, XINPUT_GAMEPAD_START },		//�X�^�[�g�{�^��
	{ enButtonRB1, XINPUT_GAMEPAD_RIGHT_SHOULDER },	//RB1�{�^��
	{ enButtonRB2, 0 },								//RB2�{�^��
	{ enButtonRB3, XINPUT_GAMEPAD_RIGHT_THUMB },	//RB3�{�^��
	{ enButtonLB1, XINPUT_GAMEPAD_LEFT_SHOULDER },	//LB1�{�^��
	{ enButtonLB2, 0 },								//LB2�{�^��
	{ enButtonLB3, XINPUT_GAMEPAD_LEFT_THUMB },		//LB3�{�^��
};

struct VirtualPadToKeyboard{
	EnButton vButton;
	DWORD keyCoord;
};

const VirtualPadToKeyboard vPadToKeyboardTable[enButtonNum] = {
	{ enButtonUp, '8' },				//��
	{ enButtonDown, '2' },				//��
	{ enButtonLeft, '4' },				//��
	{ enButtonRight, '6' },				//�E
	{ enButtonA, 'J' },					//A�{�^��
	{ enButtonB, 'K' },					//B�{�^��
	{ enButtonX, 'I' },					//X�{�^��
	{ enButtonY, 'O' },					//Y�{�^��
	{ enButtonSelect, VK_SPACE },		//�Z���N�g�{�^��
	{ enButtonStart, VK_RETURN },		//�X�^�[�g�{�^��
	{ enButtonRB1, '7' },				//RB1�{�^��
	{ enButtonRB2, '8' },				//RB2�{�^��
	{ enButtonRB3, '9' },				//RB3�{�^��
	{ enButtonLB1, 'B' },				//LB1�{�^��
	{ enButtonLB2, 'N' },				//LB2�{�^��
	{ enButtonLB3, 'M' },				//LB3�{�^��
};

void CPad::Update()
{
	DWORD result = XInputGetState(m_padNo, &m_state.state);
	if (result == ERROR_SUCCESS){
		//�ڑ�����Ă���
		m_state.bConnected = true;
		for (const VirtualPadToXPad& vPadToXPad : vPadToXPadTable){						//foreach(�Ԃ肠���Ă邩�킩���)�ł�����
			if (m_state.state.Gamepad.wButtons & vPadToXPad.xButton){					//���݉�����Ă���{�^���Ɗe�{�^���̘_���a���Ƃ�
				m_trigger[vPadToXPad.vButton] = 1 ^ m_press[vPadToXPad.vButton];		//�����ꂽ�u�Ԃ̔���B1f�ȍ~�͔��肳��Ȃ�(�O�͔r���I�_���a���Ƃ鉉�Z�q�炵��)
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
			//���X�e�B�b�N�̓��͗�//short��float�ɕύX?
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
			//�E�X�e�B�b�N�̓��͗�//short��float�ɕύX?
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
		//���ڑ�
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

		//�X�e�B�b�N�̓��͗ʂ𐳋K��
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
		//�X�e�B�b�N�̓��͗ʂ𐳋K��
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



