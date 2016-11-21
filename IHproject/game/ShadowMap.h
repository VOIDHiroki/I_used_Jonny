#pragma once
#include "RenderTarget.h"


class ShadowMap{
	CRenderTarget renderTarget;
	D3DXMATRIX lightViewMatrix;
	D3DXMATRIX lightProjMatrix;
	D3DXVECTOR3	viewPosition;
	D3DXVECTOR3 viewTarget;
public:
	ShadowMap();
	~ShadowMap();
	//�e�N�X�`�����擾
	LPDIRECT3DTEXTURE9 GetTexture()
	{
		return renderTarget.GetTexture();
	}
	//������
	void Init();
	//���C�g�r���[�̎��_��ݒ�
	void SetLightViewPosition(const D3DXVECTOR3& lightViewPosition )
	{
		viewPosition = lightViewPosition;
	}
	//���C�g�r���[�̒����_��ݒ�
	void SetLightViewTarget(const D3DXVECTOR3& lightViewTarget)
	{
		viewTarget = lightViewTarget;
	}
	//���C�g�r���[�s����擾
	const D3DXMATRIX& GetLightViewMatrix()
	{
		return lightViewMatrix;
	}
	//�v���W�F�N�V�����s����擾
	const D3DXMATRIX& GetLightProjectionMatrix()
	{
		return lightProjMatrix;
	}

	//�X�V
	void Update();
	//�V���h�E�}�b�v�ɏ�������
	void Draw();
};