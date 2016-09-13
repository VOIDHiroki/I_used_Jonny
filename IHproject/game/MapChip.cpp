#include "stdafx.h"
#include "MapChip.h"
#include "game.h"
#include "gamecamera.h"

MapChip::MapChip()
{

}

MapChip::~MapChip()
{

}

void MapChip::Init(const SMapChipLocInfo* mapChipLocInfoTable)
{
	//ƒ‚ƒfƒ‹‚Ì“Ç‚Ýž‚Ý
	char modelPath[256];
	sprintf(modelPath, "Assets/model/%s.X", mapChipLocInfoTable->modelName);
	skinModelData.LoadModelData(modelPath, NULL);

	D3DXMATRIX mTrans;
	position = mapChipLocInfoTable->pos;
	position.x = position.x * 0.38f;
	position.y = position.y * 0.38f;
	position.z = position.z * 0.38f;

	mTrans.m[3][0] *= position.x;
	mTrans.m[3][1] *= position.y;
	mTrans.m[3][2] *= position.z;

	D3DXMATRIX mRot;
	D3DXMatrixRotationQuaternion(&mRot, &mapChipLocInfoTable->rotation);
	//D3DXMatrixMultiply(&m_world, &mRot, &mTrans);


	skinModel.Init(&skinModelData);
	skinModel.SetLight(&light);
	//
	//

	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, 0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, 0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.7f, 0.7f, 0.7f, 1.0f));

}

void MapChip::Update()
{
	skinModel.UpdateWorldMatrix(position, D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f), Vec3One);
}

void MapChip::Render()
{
	GameCamera* g_camera = game->GetGameCamera();
	skinModel.Draw(&g_camera->GetCamera().GetViewMatrix(), &g_camera->GetCamera().GetProjectionMatrix());
}