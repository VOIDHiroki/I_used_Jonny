#include "stdafx.h"
#include "SkyBox.h"
#include "game.h"
#include "gamecamera.h"

SkyBox::SkyBox()
{
	light.SetAmbientLight(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

	modelData.LoadModelData("Assets/model/sky.x", NULL);
	model.Init(&modelData);
	model.SetLight(&light);
	

}

SkyBox::~SkyBox()
{
}

void SkyBox::Update()
{
	
}

void SkyBox::Render()
{
	GameCamera* g_camera = game->GetGameCamera();
	model.Draw(&g_camera->GetCamera().GetViewMatrix(), &g_camera->GetCamera().GetProjectionMatrix());
}