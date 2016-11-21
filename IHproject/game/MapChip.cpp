#include "stdafx.h"
#include "MapChip.h"
#include "game.h"
#include "gamecamera.h"
#include "rigidBody.h"


MapChip::MapChip()
{

}

MapChip::~MapChip()
{

}

void MapChip::Init(const SMapChipLocInfo* mapChipLocInfoTable)
{
	//モデルの読み込み
	char modelPath[256];
	sprintf(modelPath, "Assets/model/%s.X", mapChipLocInfoTable->modelName);
	skinModelData.LoadModelData(modelPath, NULL);

	//D3DXMatrixRotationQuaternion(&mRot, &mapChipLocInfoTable->rotation);
	//D3DXMatrixMultiply(&m_world, &mRot, &mTrans);


	skinModel.Init(&skinModelData);
	skinModel.SetLight(&light);

	//ワールド行列のバッファを作成
	meshCollider = new MeshCollider;
	rigidBody = new RigidBody;

	D3DXMATRIX mTrans;
	position = mapChipLocInfoTable->pos;
	position.x = position.x;
	position.y = position.y;
	position.z = position.z;

	mTrans.m[3][0] *= position.x;
	mTrans.m[3][1] *= position.y;
	mTrans.m[3][2] *= position.z;
	rotation = mapChipLocInfoTable->rotation;


	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, 0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, 0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.7f, 0.7f, 0.7f, 1.0f));

	Update();
	rootBoneMatrix = skinModelData.GetRootBoneWorldMatrix();	
	meshCollider->CreateMeshFromSkinmodel(&skinModel, rootBoneMatrix);
	RigidBodyInfo rbInfo;
	rbInfo.collider = meshCollider;
	rbInfo.mass = 0.0f;
	rigidBody->Create(rbInfo);
	btRigidBody* btRb = rigidBody->GetBody(); 
	game->GetPhysics()->AddRigidBody(rigidBody);
}

void MapChip::Update()
{
	skinModel.UpdateWorldMatrix(position, rotation, Vec3One);
}

void MapChip::Render()
{
	GameCamera* g_camera = game->GetGameCamera();
	skinModel.Draw(&g_camera->GetCamera().GetViewMatrix(), &g_camera->GetCamera().GetProjectionMatrix());
}