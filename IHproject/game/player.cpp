#include "stdafx.h"
#include "player.h"
#include "game.h"
#include "gamecamera.h"


Player::Player()
{
	MoveDir = Vec3Zero;
}

Player::~Player()
{

}


void Player::Start()
{

	//���C�g�̏�����
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));

	GameCamera* g_camera = game->GetGameCamera();

	//���f�������[�h
	modelData.LoadModelData("Assets/model/Unity.X", &animation);
	animation.SetAnimationEndTime(2, 0.8f);

	model.Init(&modelData);
	model.SetLight(&light);
	model.SetCamera(&g_camera->GetCamera());
	animation.PlayAnimation(0);
	position = D3DXVECTOR3(0.0f, 2.5f, 0.0f);
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 InitPos = position;
	InitPos.y += 0.2f;
	characterController.Init(0.5f, 0.5f, InitPos);
	characterController.SetGravity(-20.0f);

	state = State_STAND;
}

void Player::Update()
{	
	D3DXVECTOR3 V1 = game->GetGameCamera()->GetCamera().GetLookatPt() - game->GetGameCamera()->GetCamera().GetEyePt();	//�����������ǃJ�����̈ʒu�ƒ����_�Ō��������߂Ă�
	D3DXVECTOR3 V2;
	D3DXVECTOR3 UP(0.0f, 1.0f, 0.0f);		//������̃x�N�g��
	V1.y = 0.0f;
	D3DXVec3Normalize(&V1, &V1);			//���K��
	D3DXVec3Cross(&V2, &V1, &UP);			//������̃x�N�g������Z���邱�Ƃŉ������̒����x�N�g��V2�����߂���炵��
	D3DXVec3Normalize(&V2, &V2);			//���K��
	CPad* Pad = game->GetPad();

	float movespeed = 0.0f;


	//�L�����N�^�[�̈ړ�
	//if (GetAsyncKeyState('W')){
	//	MoveDir += V1;
	//	movespeed = 0.06f;
	//}
	//if (GetAsyncKeyState('S')){
	//	MoveDir -= V1;
	//	movespeed = 0.06f;

	//}
	//if (GetAsyncKeyState('A')){
	//	MoveDir += V2;
	//	movespeed = 0.06f;

	//}
	//if (GetAsyncKeyState('D')){
	//	MoveDir -= V2;
	//	movespeed = 0.06f;

	//}

	if (fabsf(Pad->GetLStickXF()) > 0.0f || fabsf(Pad->GetLStickYF()) > 0.0f){
		MoveDir.x += V2.x * Pad->GetLStickXF() - V1.x * Pad->GetLStickYF();
		MoveDir.z += V2.z * Pad->GetLStickXF() - V1.z * Pad->GetLStickYF();
		
		movespeed = 4.8f * max(fabsf(Pad->GetLStickXF()) + fabsf(Pad->GetLStickYF()), 0.0f);
	}


	D3DXVec3Normalize(&MoveDir, &MoveDir);		//���K��
	D3DXVECTOR3 moveSpeed = movespeed * MoveDir;
	moveSpeed.y = characterController.GetMoveSpeed().y;
	if (characterController.GetOnGround()){
		if (movespeed != 0.0f){
			if (movespeed >= 0.05f){
				state = State_RUN;
			}
			else
			{
				state = State_WALK;
			}
		}

		else
		{
			state = State_STAND;
		}
		if (Pad->IsTrigger(enButtonA) ){
			moveSpeed.y = 8.0f;
			characterController.Jump();
		}
	}
	else{
		state = State_JUMP;
	}
	characterController.SetMoveSpeed(moveSpeed);
	characterController.Execute();
	position = characterController.GetPosition();


	//�A�j���[�V�����A�b�v�f�[�g
	
	AnimationControl();
	D3DXQUATERNION mRot;
	D3DXQuaternionRotationAxis(&mRot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), atan2f(MoveDir.x, MoveDir.z));//D3DXToRadian(UnityDir));
	model.UpdateWorldMatrix(position, mRot, D3DXVECTOR3(1.0f, 1.0f, 1.0f));	//���[���h�s��X�V

}

void Player::PlayAnimation(AnimationNo animNo)
{
	if (currentAnimNo != animNo){
		//���݂̃A�j���[�V�����ƈႤ
		animation.PlayAnimation(animNo);
		currentAnimNo = animNo;
	}
}


void Player::AnimationControl()
{
	animation.Update(1.0f / 60.0f);
	if (state == State_RUN){
		PlayAnimation(Anim_RUN);
	}
	else if (state == State_WALK)
	{
		PlayAnimation(Anim_WALK);
	}
	else if (state == State_JUMP){
		PlayAnimation(Anim_JUMP);
	}
	else
	{
		PlayAnimation(Anim_STAND);
	}
}

void Player::Render()
{
	GameCamera* g_camera = game->GetGameCamera();
	model.Draw(&g_camera->GetCamera().GetViewMatrix(), &g_camera->GetCamera().GetProjectionMatrix());
	
	//Camera* camera = game->GetCamera();
	//model.Draw(&camera->GetViewMatrix(), &camera->GetProjectionMatrix());
}