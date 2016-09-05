#include "stdafx.h"
#include "ground.h"
#include "game.h"


Ground::Ground()
{
}

Ground::~Ground()
{

}

//������
void Ground::Init()
{
	modelData.LoadModelData("Assets/model/ground.x", NULL);
	model.Init(&modelData);
	light.SetAmbientLight(D3DXVECTOR4(0.7f, 0.7f, 0.7f, 0.0f));

	D3DXVECTOR3 position(0.0f, 2.0f, 0.0f);
	D3DXQUATERNION rotation(0.0f, 0.0f, 0.0f, 1.0f);
	model.SetLight(&light);
	model.UpdateWorldMatrix(position, rotation, D3DXVECTOR3(10.0f, 1.0f, 10.0f));
}


void Ground::Render()
{

	GameCamera* g_camera = game->GetGameCamera();
	model.Draw(&g_camera->GetCamera().GetViewMatrix(), &g_camera->GetCamera().GetProjectionMatrix());

	//Camera* camera = game->GetCamera();
	//model.Draw(&camera->GetViewMatrix(), &camera->GetProjectionMatrix());
}