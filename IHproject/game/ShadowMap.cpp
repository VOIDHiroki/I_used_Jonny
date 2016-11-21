#include "stdafx.h"
#include "ShadowMap.h"


ShadowMap::ShadowMap()
{
	D3DXMatrixIdentity(&lightViewMatrix);
	D3DXMatrixIdentity(&lightProjMatrix);
	viewPosition.x = 0.0f;
	viewPosition.y = 0.0f;
	viewPosition.z = 0.0f;
	viewTarget.x = 0.0f;
	viewTarget.y = 0.0f;
	viewTarget.z = 0.0f;
}

ShadowMap::~ShadowMap()
{

}

void ShadowMap::Init()
{
	//�����_�����O�^�[�Q�b�g��������
	renderTarget.Create(
		512,
		512,
		1,
		D3DFMT_A8R8G8B8,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0
		);
}


void ShadowMap::Update()
{
	//���C�g�r���[�v���W�F�N�V�����s����X�V�B
	//���ʂ̃J�����Ɠ����B
	//�J�����̏���������߂�v�Z��������Ă����B
	D3DXVECTOR3 tmp = viewTarget - viewPosition;
	D3DXVec3Normalize(&tmp, &tmp);
	if (fabsf(tmp.y) > 0.9999f) {
		//�J�������قڐ^��or�^���������Ă���B
		D3DXMatrixLookAtLH(&lightViewMatrix, &viewPosition, &viewTarget, &D3DXVECTOR3(1.0f, 0.0f, 0.0f));
	}
	else {
		D3DXMatrixLookAtLH(&lightViewMatrix, &viewPosition, &viewTarget, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&lightProjMatrix, D3DXToRadian(60.0f), 1.0f, 0.1f, 100.0f);

}

void ShadowMap::Draw()
{
	LPDIRECT3DSURFACE9 renderTargetBackup;
	LPDIRECT3DSURFACE9 depthBufferBackup;
	g_pd3dDevice->GetRenderTarget(0, &renderTargetBackup);		//���X�̃����_�����O�^�[�Q�b�g��ۑ��B��Ŗ߂��K�v������̂ŁB
	g_pd3dDevice->GetDepthStencilSurface(&depthBufferBackup);	//���X�̃f�v�X�X�e���V���o�b�t�@��ۑ��B��Ŗ߂��K�v������̂ŁB
	//�����_�����O�^�[�Q�b�g��ύX����B
	g_pd3dDevice->SetRenderTarget(0, renderTarget.GetRenderTarget());
	g_pd3dDevice->SetDepthStencilSurface(renderTarget.GetDepthStencilBuffer());
	//�������ݐ��ύX�����̂ŃN���A�B
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	//g_tiger.Draw(&lightViewMatrix, &lightProjMatrix, true, false);

	g_pd3dDevice->SetRenderTarget(0, renderTargetBackup);		//�߂��B
	g_pd3dDevice->SetDepthStencilSurface(depthBufferBackup);	//�߂��B

}