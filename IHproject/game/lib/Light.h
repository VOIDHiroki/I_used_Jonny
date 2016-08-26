#pragma once 


class Light {
public:
	static const int	DIFFUSE_LIGHT_NUM = 4;	//���s�����̐�
public:
	//�R���X�g���N�^
	Light()
	{
		memset(this, 0, sizeof(Light));
	}
	~Light()
	{

	}

	//���s�����̕������擾
	const D3DXVECTOR4* GetDiffuseLightDirection() const
	{
		return diffuseLightDirection;
	}

	//���s�����̐F���擾
	const D3DXVECTOR4* GetDiffuseLightColor() const
	{
		return diffuseLightColor;
	}

	//���s�����̕�����ݒ�
	// lightNo		���C�g�̔ԍ�
	// dir			����
	void SetDiffuseLightDirection(int lightNo, D3DXVECTOR4& dir)
	{
		diffuseLightDirection[lightNo] = dir;
	}

	// ���s�����̐F��ݒ�
	// lightNo		���C�g�̔ԍ�
	// color		���s�����̐F
	void SetDiffuseLightColor(int lightNo, D3DXVECTOR4& color)
	{
		diffuseLightColor[lightNo] = color;
	}


	//������ݒ�
	void SetAmbientLight(const D3DXVECTOR4& ambient)
	{
		ambientLight = ambient;
	}

private:

	D3DXVECTOR4		diffuseLightDirection[DIFFUSE_LIGHT_NUM];	//���s�����̌���
	D3DXVECTOR4		diffuseLightColor[DIFFUSE_LIGHT_NUM];		//���s�����̐F
	D3DXVECTOR4		ambientLight;						//����
};