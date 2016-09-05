#include "stdafx.h"
#include "game.h"

Game::Game()
{
}

Game::~Game()
{

}


void Game::Start()
{
	//camera.Init();
	//camera.Update();
	

	player.Start();
	g_camera.Start();
	g_camera.SetPlayer(&player);
	ground.Init();

}

void Game::Update()
{
	//D3DXVECTOR3 playerPos = player.GetPosition();
	//D3DXVECTOR3 CameraPos(playerPos.x, playerPos.y + 2.0f, playerPos.z + 5.0f);
	//
	////camera.SetEyePt(D3DXVECTOR3(0.0f,4.0f,5.0f));
	//camera.SetEyePt(CameraPos);
	//camera.SetLookatPt(playerPos);
	//camera.Update();

	g_camera.Update();
	player.Update();
	

}
void Game::Render()
{
	player.Render();
	ground.Render();
}