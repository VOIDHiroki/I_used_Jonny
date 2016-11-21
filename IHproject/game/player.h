#pragma once

#include "CharacterController.h"

class Player{
	enum AnimationNo{
		Anim_STAND,
		Anim_WALK,
		Anim_RUN,
		Anim_JUMP
	};

public:
	enum NowState
	{
		State_STAND,
		State_WALK,
		State_RUN,
		State_JUMP
	};
	Player();
	~Player();
	void Start();
	void Update();
	void Render();
	const D3DXVECTOR3& GetPosition()
	{
		return position;
	}
	void PlayAnimation(AnimationNo animNo);

	void AnimationControl();

private:
	SkinModel model;
	SkinModelData modelData;
	Animation animation;
	AnimationNo currentAnimNo;
	NowState state;
	D3DXVECTOR3 position;
	D3DXQUATERNION rotation;
	Light light;

	D3DXVECTOR3 MoveDir;
	CCharacterController characterController;
};