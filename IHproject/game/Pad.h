#pragma once

#include <XInput.h>


enum EnButton{
	enButtonUp,		//上
	enButtonDown,	//下
	enButtonLeft,	//左
	enButtonRight,	//右
	enButtonA,		//Aボタン
	enButtonB,		//Bボタン
	enButtonX,		//Xボタン
	enButtonY,		//Yボタン
	enButtonSelect,	//セレクトボタン
	enButtonStart,	//スタートボタン
	enButtonRB1,	//RB1ボタン
	enButtonRB2,	//RB2ボタン
	enButtonRB3,	//RB3ボタン
	enButtonLB1,	//LB1ボタン
	enButtonLB2,	//LB2ボタン
	enButtonLB3,	//LB3ボタン
	enButtonNum,	//ボタンの数
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

	//ボタンのトリガー判定
	bool IsTrigger(EnButton button) const
	{
		return m_trigger[button] != 0;
	}

	//ボタンの押下判定
	bool IsPress(EnButton button) const
	{
		return m_press[button] != 0;
	}

	//左スティックのX軸の入力量を取得する。
	float GetLStickXF() const
	{
		return m_lStickX;
	}
	//左スティックのY軸の入力量を取得する
	float GetLStickYF() const
	{
		return m_lStickY;
	}
	//右スティックのX軸の入力量を取得する
	float GetRStickXF() const
	{
		return m_rStickX;
	}
	float GetRStickYF() const
	{
		return m_rStickY;
	}
private:
	PAD_STATE m_state;	//!<パッドステート。
	int m_padNo;		//!<パッド番号。
	int m_trigger[enButtonNum];	//!<トリガー入力のフラグ。
	int m_press[enButtonNum];	//!<press入力のフラグ。
	float m_lStickX;			//!<左スティックのX軸の入力量。
	float m_lStickY;			//!<左スティックのY軸の入力量。
	float m_rStickX;			//!<右スティックのX軸の入力量。
	float m_rStickY;			//!<右スティックのY軸の入力量。

};
