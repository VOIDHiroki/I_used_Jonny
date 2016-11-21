#pragma once

#include "player.h"
#include "ground.h"
#include "gamecamera.h"
#include "Map.h"
#include "Pad.h"
#include "SkyBox.h"
#include "Physics.h"

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
	CPad* GetPad()
	{
		return &Pad;
	}

	PhysicsWorld* GetPhysics()
	{
		return &physics;
	}
private:
	Camera camera;
	GameCamera g_camera;
	Player player;
	Ground ground;
	Map map;
	CPad Pad;
	SkyBox sky;
	PhysicsWorld physics;
};

extern Game* game;