#include "stdafx.h"
#include "gamecamera.h"
#include "player.h"


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
	camera.SetLookatPt(D3DXVECTOR3(0.0f, 2.0f, 5.0f));
	camera.SetEyePt(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	toPosition = camera.GetLookatPt() - camera.GetEyePt();
	
	camera.SetFar(100.0f);
	camera.Update();


}

void GameCamera::Update()
{
		if (GetAsyncKeyState(VK_RIGHT)){
			D3DXMATRIX mRot;
			D3DXMatrixRotationY(&mRot, 0.05f);
			D3DXVec3TransformNormal(&toPosition, &toPosition, &mRot);
		}

		if (GetAsyncKeyState(VK_LEFT)){
			D3DXMATRIX mRot;
			D3DXMatrixRotationY(&mRot, -0.05f);
			D3DXVec3TransformNormal(&toPosition, &toPosition, &mRot);
		}

	if (GetAsyncKeyState(VK_UP)){
		D3DXVECTOR3 rotAxis;
		D3DXVec3Cross(&rotAxis,&toPosition, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
		D3DXVec3Normalize(&rotAxis, &rotAxis);
		D3DXMATRIX mRot;
		D3DXMatrixRotationAxis(&mRot, &rotAxis, -0.02f);
		D3DXVECTOR3 toPositionOld = toPosition;
		D3DXVec3TransformNormal(&toPosition, &toPosition, &mRot);
		D3DXVECTOR3 toPosDir = toPosition;
		D3DXVec3Normalize(&toPosDir, &toPosDir);
		if (toPosDir.y < -0.08f){
			toPosition = toPositionOld;
		}
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		D3DXVECTOR3 rotAxis;
		D3DXVec3Cross(&rotAxis, &toPosition, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
		D3DXVec3Normalize(&rotAxis, &rotAxis);
		D3DXMATRIX mRot;
		D3DXMatrixRotationAxis(&mRot, &rotAxis, 0.02f);
		D3DXVECTOR3 toPositionOld = toPosition;
		D3DXVec3TransformNormal(&toPosition, &toPosition, &mRot);
		D3DXVECTOR3 toPosDir = toPosition;
		D3DXVec3Normalize(&toPosDir, &toPosDir);
		if (toPosDir.y > 0.8f){
			toPosition = toPositionOld;
		}
	}

	D3DXVECTOR3 v = player->GetPosition();
	v.y = 2.5f;
	camera.SetLookatPt(v);
	v += toPosition;
	camera.SetEyePt(v);

	camera.Update();
}

void GameCamera::Render()
{
}