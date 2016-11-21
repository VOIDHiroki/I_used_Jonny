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
	//テクスチャを取得
	LPDIRECT3DTEXTURE9 GetTexture()
	{
		return renderTarget.GetTexture();
	}
	//初期化
	void Init();
	//ライトビューの視点を設定
	void SetLightViewPosition(const D3DXVECTOR3& lightViewPosition )
	{
		viewPosition = lightViewPosition;
	}
	//ライトビューの注視点を設定
	void SetLightViewTarget(const D3DXVECTOR3& lightViewTarget)
	{
		viewTarget = lightViewTarget;
	}
	//ライトビュー行列を取得
	const D3DXMATRIX& GetLightViewMatrix()
	{
		return lightViewMatrix;
	}
	//プロジェクション行列を取得
	const D3DXMATRIX& GetLightProjectionMatrix()
	{
		return lightProjMatrix;
	}

	//更新
	void Update();
	//シャドウマップに書き込み
	void Draw();
};