#pragma once

#include "player.h"
#include "ground.h"
#include "gamecamera.h"
#include "Map.h"


class Game{
public:

	//コンストラクタ
	Game();

	//デストラクタ
	~Game();

	//ゲームが起動してから一度だけ呼ばれる関数

	void Start();

	//更新
	void Update();

	//描画
	void Render();

	//カメラを取得
	Camera* GetCamera()
	{
		return &camera;
	}

	GameCamera* GetGameCamera()
	{
		return &g_camera;
	}

private:
	Camera camera;
	GameCamera g_camera;
	Player player;
	Ground ground;
	Map map;

};

extern Game* game;