#include "stdafx.h"
#include "gamecamera.h"
#include "player.h"
#include "game.h"

GameCamera	*g_camera;

GameCamera::GameCamera() : player(nullptr)
{
}

GameCamera::~GameCamera()
{
}

void GameCamera::Start()
{
	camera.Init();
	camera.SetLookatPt(D3DXVECTOR3(0.0f, 3.0f, 5.0f));
	camera.SetEyePt(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	toPosition = camera.GetLookatPt() - camera.GetEyePt();
	
	camera.SetFar(1000.0f);
	camera.Update();
}

void GameCamera::Update()
{
	CPad* Pad = game->GetPad();


	////　キーボードでの移動処理

	//if (GetAsyncKeyState(VK_RIGHT)){
	//	D3DXMATRIX mRot;
	//	D3DXMatrixRotationY(&mRot, 0.05f);
	//	D3DXVec3TransformNormal(&toPosition, &toPosition, &mRot);
	//}

	//if (GetAsyncKeyState(VK_LEFT)){
	//	D3DXMATRIX mRot;
	//	D3DXMatrixRotationY(&mRot, -0.05f);
	//	D3DXVec3TransformNormal(&toPosition, &toPosition, &mRot);
	//}

	//if (GetAsyncKeyState(VK_UP)){
	//	D3DXVECTOR3 rotAxis;
	//	D3DXVec3Cross(&rotAxis,&toPosition, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	//	D3DXVec3Normalize(&rotAxis, &rotAxis);
	//	D3DXMATRIX mRot;
	//	D3DXMatrixRotationAxis(&mRot, &rotAxis, -0.02f);
	//	D3DXVECTOR3 toPositionOld = toPosition;
	//	D3DXVec3TransformNormal(&toPosition, &toPosition, &mRot);
	//	D3DXVECTOR3 toPosDir = toPosition;
	//	D3DXVec3Normalize(&toPosDir, &toPosDir); 
	//	if (toPosDir.y < -0.08f){
	//		toPosition = toPositionOld;
	//	}
	//}

	//if (GetAsyncKeyState(VK_DOWN))
	//{
	//	D3DXVECTOR3 rotAxis;
	//	D3DXVec3Cross(&rotAxis, &toPosition, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	//	D3DXVec3Normalize(&rotAxis, &rotAxis);
	//	D3DXMATRIX mRot;
	//	D3DXMatrixRotationAxis(&mRot, &rotAxis, 0.02f);
	//	D3DXVECTOR3 toPositionOld = toPosition;
	//	D3DXVec3TransformNormal(&toPosition, &toPosition, &mRot);
	//	D3DXVECTOR3 toPosDir = toPosition;
	//	D3DXVec3Normalize(&toPosDir, &toPosDir);
	//	if (toPosDir.y > 0.8f){
	//		toPosition = toPositionOld;
	//	}
	//}

	//　ゲームパッドでの移動処理
	if (fabsf(Pad->GetRStickXF()) > 0.0f){		//横回転
		D3DXMATRIX mRot;
		D3DXMatrixRotationY(&mRot, -0.07f * Pad->GetRStickXF());		//Ｙ軸回転の回転量
		D3DXVec3TransformNormal(&toPosition, &toPosition, &mRot);		//toPositionに回転量をかける
	}

	if (fabsf(Pad->GetRStickYF()) > 0.0f){		//縦回転
		D3DXVECTOR3 rotAxis;
		D3DXVec3Cross(&rotAxis, &toPosition, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
		D3DXVec3Normalize(&rotAxis, &rotAxis);
		D3DXMATRIX mRot;
		D3DXMatrixRotationAxis(&mRot, &rotAxis, 0.04f * Pad->GetRStickYF());
		D3DXVECTOR3 toPositionOld = toPosition;
		D3DXVec3TransformNormal(&toPosition, &toPosition, &mRot);
		D3DXVECTOR3 toPosDir = toPosition;
		D3DXVec3Normalize(&toPosDir, &toPosDir);
		if (toPosDir.y > 0.8f){
			toPosition = toPositionOld;
		}
		else if (toPosDir.y < -0.8f){
			toPosition = toPositionOld;
		}
	}

	D3DXVECTOR3 v = player->GetPosition();			//プレイヤーのポジションゲットだぜっ！
	//v.y += 2.5f;										//プレイヤーの（大体）頭に注視点を合わせる
	camera.SetLookatPt(v);							//プレイヤーのポジションを注視点にする
	v += toPosition;								//プレイヤーのポジションに距離を足す
	camera.SetEyePt(v);								//プレイヤーポジション＋距離＝カメラの位置

	camera.Update();
}

void GameCamera::Render()
{
}