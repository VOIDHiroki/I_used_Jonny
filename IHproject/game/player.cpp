#include "stdafx.h"
#include "player.h"
#include "game.h"
#include "gamecamera.h"


Player::Player()
{
	MoveDir = D3DXVECTOR3(0.0f,0.0f,0.0f);
}

Player::~Player()
{

}


void Player::Start()
{

	//ライトの初期化
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));

	//モデルをロード
	modelData.LoadModelData("Assets/model/Unity.X", &animation);
	animation.SetAnimationEndTime(2, 0.8f);

	model.Init(&modelData);
	model.SetLight(&light);
	animation.PlayAnimation(0);
	position = D3DXVECTOR3(0.0f, 2.05f, 0.0f);
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);

	state = State_STAND;
}

void Player::Update()
{	
	D3DXVECTOR3 V1 = game->GetGameCamera()->GetCamera().GetLookatPt() - game->GetGameCamera()->GetCamera().GetEyePt();	//少し長いけどカメラの位置と注視点で向きを求めてる
	D3DXVECTOR3 V2;
	D3DXVECTOR3 UP(0.0f, 1.0f, 0.0f);		//上方向のベクトル
	V1.y = 0.0f;
	D3DXVec3Normalize(&V1, &V1);			//正規化
	D3DXVec3Cross(&V2, &V1, &UP);			//上方向のベクトルを乗算することで横方向の直線ベクトルV2が求められるらしい
	D3DXVec3Normalize(&V2, &V2);			//正規化
	

	float movespeed = 0.0f;


	//キャラクターの移動
	if (GetAsyncKeyState('W')){
		MoveDir += V1;
		movespeed = 0.06f;
	}
	if (GetAsyncKeyState('S')){
		MoveDir -= V1;
		movespeed = 0.06f;

	}
	if (GetAsyncKeyState('A')){
		MoveDir += V2;
		movespeed = 0.06f;

	}
	if (GetAsyncKeyState('D')){
		MoveDir -= V2;
		movespeed = 0.06f;

	}

	D3DXVec3Normalize(&MoveDir, &MoveDir);
	position += MoveDir * movespeed;
	if (movespeed != 0.0f){
		state = State_RUN;
	}
	else
	{
		state = State_STAND;
	}

	//アニメーションアップデート
	
	AnimationControl();
	D3DXQUATERNION mRot;
	D3DXQuaternionRotationAxis(&mRot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), atan2f(MoveDir.x, MoveDir.z));//D3DXToRadian(UnityDir));
	model.UpdateWorldMatrix(position, mRot, D3DXVECTOR3(1.0f, 1.0f, 1.0f));	//ワールド行列更新

}

void Player::PlayAnimation(AnimationNo animNo)
{
	if (currentAnimNo != animNo){
		//現在のアニメーションと違う
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