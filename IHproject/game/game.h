#pragma once

#include "player.h"
#include "ground.h"
#include "gamecamera.h"



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

private:
	Camera camera;
	GameCamera g_camera;
	Player player;
	Ground ground;

};

extern Game* game;