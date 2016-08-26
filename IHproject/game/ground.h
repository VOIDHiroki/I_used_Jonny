#pragma once


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

};