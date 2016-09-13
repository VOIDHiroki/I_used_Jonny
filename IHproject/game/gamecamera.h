#pragma once

class Player;

class GameCamera{
public:
	GameCamera();
	~GameCamera();

	void Start();
	void Update();
	void Render();
	void SetPlayer(Player* player)
	{
		this->player = player;
	}

	Camera& GetCamera()
	{
		return camera;
	}


private:
	Player* player;
	Camera camera;
	D3DXVECTOR3 toPosition;

};

extern GameCamera*			g_camera;