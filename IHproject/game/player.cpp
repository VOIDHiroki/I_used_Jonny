#include "stdafx.h"
#include "player.h"
#include "game.h"


Player::Player()
{

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

	model.Init(&modelData);
	model.SetLight(&light);
	animation.PlayAnimation(0);
	position = D3DXVECTOR3(0.0f, 2.0f, 0.0f);
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);

}

void Player::Update()
{
	
	///////////////////////////////////////実装予定？//////////////////////////////////////////////////////////
	//
	//		**カメラの向いている方向に進ませる**
	//
	// D3DXVECTOR3 V1 = game->GetCamera()->GetLookatPt() - game->GetCamera()->GetEyePt();
	// D3DXVECTOR3 V2;
	// D3DXVECTOR3 Up(0.0f,0.1f,0.0f);		//上方向のベクトル
	// 
	// D3DXVec3Normalize(&V1, &V1);			//正規化
	// D3DXVec3Cross(&V2, &V1, &UP);		//上方向のベクトルを乗算することで直線のベクトルV2が求められる？
	// D3DXVec3Normalize(&V2, &V2);			//正規化
	//
	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (GetAsyncKeyState('W')){
		position.z -= 0.02f;
	}
	if (GetAsyncKeyState('S')){
		position.z += 0.02f;
	}
	if (GetAsyncKeyState('A')){
		position.x += 0.02f;
	}
	if (GetAsyncKeyState('D')){
		position.x -= 0.02f;
	}

	animation.Update(1.0f / 60.0f);
	model.UpdateWorldMatrix(position, rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));

}

void Player::Render()
{
	
	Camera* camera = game->GetCamera();
	model.Draw(&camera->GetViewMatrix(), &camera->GetProjectionMatrix());

}