#pragma once

struct SMapChipLocInfo{
	const char* modelName;
	D3DXVECTOR3 pos;
	D3DXQUATERNION rotation;
};

class MapChip{
public:
	MapChip();
	~MapChip();
	void Init(const SMapChipLocInfo* mapChipLocInfoTable);
	void Start();
	void Update();
	void Render();

private:
	SkinModelData					skinModelData;
	SkinModel						skinModel;
	Animation						animation;
	Light							light;
	D3DXVECTOR3						position;
	//D3DXMATRIX					m_world;

};