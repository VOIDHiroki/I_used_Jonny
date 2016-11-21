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

	//�R���X�g���N�^
	Game();

	//�f�X�g���N�^
	~Game();

	//�Q�[�����N�����Ă����x�����Ă΂��֐�

	void Start();

	//�X�V
	void Update();

	//�`��
	void Render();

	//�J�������擾
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