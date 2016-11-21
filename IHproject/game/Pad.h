#pragma once

#include <XInput.h>


enum EnButton{
	enButtonUp,		//��
	enButtonDown,	//��
	enButtonLeft,	//��
	enButtonRight,	//�E
	enButtonA,		//A�{�^��
	enButtonB,		//B�{�^��
	enButtonX,		//X�{�^��
	enButtonY,		//Y�{�^��
	enButtonSelect,	//�Z���N�g�{�^��
	enButtonStart,	//�X�^�[�g�{�^��
	enButtonRB1,	//RB1�{�^��
	enButtonRB2,	//RB2�{�^��
	enButtonRB3,	//RB3�{�^��
	enButtonLB1,	//LB1�{�^��
	enButtonLB2,	//LB2�{�^��
	enButtonLB3,	//LB3�{�^��
	enButtonNum,	//�{�^���̐�
};

class CPad
{
public:
	struct PAD_STATE
	{
		XINPUT_STATE state;
		bool bConnected;
	};

	CPad();

	~CPad();

	void Init(int padNo)
	{
		m_padNo = padNo;
	}

	void Update();

	//�{�^���̃g���K�[����
	bool IsTrigger(EnButton button) const
	{
		return m_trigger[button] != 0;
	}

	//�{�^���̉�������
	bool IsPress(EnButton button) const
	{
		return m_press[button] != 0;
	}

	//���X�e�B�b�N��X���̓��͗ʂ��擾����B
	float GetLStickXF() const
	{
		return m_lStickX;
	}
	//���X�e�B�b�N��Y���̓��͗ʂ��擾����
	float GetLStickYF() const
	{
		return m_lStickY;
	}
	//�E�X�e�B�b�N��X���̓��͗ʂ��擾����
	float GetRStickXF() const
	{
		return m_rStickX;
	}
	float GetRStickYF() const
	{
		return m_rStickY;
	}
private:
	PAD_STATE m_state;	//!<�p�b�h�X�e�[�g�B
	int m_padNo;		//!<�p�b�h�ԍ��B
	int m_trigger[enButtonNum];	//!<�g���K�[���͂̃t���O�B
	int m_press[enButtonNum];	//!<press���͂̃t���O�B
	float m_lStickX;			//!<���X�e�B�b�N��X���̓��͗ʁB
	float m_lStickY;			//!<���X�e�B�b�N��Y���̓��͗ʁB
	float m_rStickX;			//!<�E�X�e�B�b�N��X���̓��͗ʁB
	float m_rStickY;			//!<�E�X�e�B�b�N��Y���̓��͗ʁB

};
