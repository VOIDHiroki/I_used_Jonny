#pragma once
#include "lib\Camera.h"
#include "player.h"


class PlayerCamera{
public:
	PlayerCamera();
	~PlayerCamera();

	void Update();

	D3DXMATRIX GetViewMatrix();
	
	D3DXMATRIX GetProjectionMatrix();

	void SetPlayer(Player* player)
	{
		this->player = player;
	}

private:

	Camera camera;
	Player* player;


};