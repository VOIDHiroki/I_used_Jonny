/*!
*@brief	スキンモデル
*/
#pragma once

#include "lib/Animation.h"


class SkinModelData;
class RenderContext;
class Light;
/*!
*@brief	スキンモデル
*/
class SkinModel {
public:
	SkinModel();
	~SkinModel();
	/*!
	*@brief	初期化
	*/
	void Init(SkinModelData* modelData);
	/*!
	*@brief	描画。
	*/
	void Draw(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix/*, bool isDrawToShadowMap, bool isRenderShadow*/);

	/*!
	*@brief	ワールド行列を更新。
	*@details
	* 後でCMotionクラスに移動させます。
	*@param[in]		trans	平行移動。
	*@param[in]		rot		回転。
	*@param[in]		scale	拡大。
	*/
	void UpdateWorldMatrix(const D3DXVECTOR3& trans, const D3DXQUATERNION& rot, const D3DXVECTOR3& scale);
	/*!
	*@brief	ライトを設定。
	*/
	void SetLight(Light* light)
	{
		this->light = light;
	}
	void SetCamera(Camera* camera)
	{
		this->camera = camera;
	}

	LPD3DXMESH GetOrgMeshFirst();


	D3DXMATRIX* GetWorldMatrix()
	{
		return &worldMatrix;
	}

private:
	D3DXMATRIX			worldMatrix;	//!<ワールド行列。
	D3DXMATRIX			rotationMatrix;	//!<回転行列。
	SkinModelData*		skinModelData;	//!<スキンモデルデータ。
	ID3DXEffect*		pEffect;		//!<エフェクト。
	Animation			animation;		//!<アニメーション。
	Light*				light;			//!<ライト。
	Camera*				camera;
};
