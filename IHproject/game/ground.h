#pragma once


class Ground{
public:

	Ground();
	~Ground();

	//������
	void Init();

	//�`��
	void Render();

private:
	SkinModel model;
	SkinModelData modelData;

	Light light;
	Camera camera;

};