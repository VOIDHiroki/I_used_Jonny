#pragma once

class Player{
public:

	Player();
	~Player();
	void Start();
	void Update();
	void Render();
	D3DXVECTOR3 GetPosition()
	{
		return position;
	}

private:
	SkinModel model;
	SkinModelData modelData;
	Animation animation;
	D3DXVECTOR3 position;
	D3DXQUATERNION rotation;
	Light light;
};