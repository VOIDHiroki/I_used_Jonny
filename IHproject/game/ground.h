#pragma once
#include "MeshCollider.h"
#include "rigidBody.h"


class Ground{
public:

	Ground();
	~Ground();

	//‰Šú‰»
	void Init();

	//•`‰æ
	void Render();

private:
	SkinModel model;
	SkinModelData modelData;

	Light light;
	Camera camera;
	MeshCollider meshCollider;

	D3DXMATRIX* rootBoneMatrix;
	RigidBody rigidBody;
};