#include "stdafx.h"
#include "ground.h"
#include "game.h"

Ground::Ground()
{
}

Ground::~Ground()
{

}

//‰Šú‰»
void Ground::Init()
{
	modelData.LoadModelData("Assets/model/ground_castle.X", NULL);
	model.Init(&modelData);
	light.SetAmbientLight(D3DXVECTOR4(0.7f, 0.7f, 0.7f, 0.0f));

	D3DXVECTOR3 position(0.0f, 2.0f, 0.0f);
	D3DXQUATERNION rotation(0.0f, 0.0f, 0.0f, 1.0f);
	model.SetLight(&light);
	model.UpdateWorldMatrix(position, rotation, D3DXVECTOR3(10.0f, 1.0f, 10.0f));

	rootBoneMatrix = modelData.GetRootBoneWorldMatrix();
	meshCollider.CreateMeshFromSkinmodel(&model, rootBoneMatrix);
	RigidBodyInfo rbInfo;
	rbInfo.collider = &meshCollider;
	rbInfo.mass = 0.0f;
	rigidBody.Create(rbInfo);
	game->GetPhysics()->AddRigidBody(&rigidBody);

}


void Ground::Render()
{

	GameCamera* g_camera = game->GetGameCamera();
	model.Draw(&g_camera->GetCamera().GetViewMatrix(), &g_camera->GetCamera().GetProjectionMatrix());

	//Camera* camera = game->GetCamera();
	//model.Draw(&camera->GetViewMatrix(), &camera->GetProjectionMatrix());
}