#pragma once

#include "player.h"
#include "ground.h"

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

private:
	Camera camera;
	Player player;
	Ground ground;

};

extern Game* game;