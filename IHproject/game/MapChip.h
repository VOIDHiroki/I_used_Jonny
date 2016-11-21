#pragma once

#include "MeshCollider.h"
#include "rigidBody.h"

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
	D3DXQUATERNION					rotation;
	D3DXMATRIX*						worldMatrixBuffer;
	MeshCollider*					meshCollider;
	RigidBody*						rigidBody;
	D3DXMATRIX*						rootBoneMatrix;
	//D3DXMATRIX					m_world;

};