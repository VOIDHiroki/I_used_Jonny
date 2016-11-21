#pragma once


class SkyBox{
public:
	SkyBox();
	~SkyBox();
	void Init(){}
	void Update();
	void Render();
private:
	SkinModelData modelData;
	SkinModel model;

	Light light;
};