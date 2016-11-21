/*!
*@brief	�X�L�����f���f�[�^
*/

#pragma once


struct D3DXFRAME_DERIVED : public D3DXFRAME {
	D3DXMATRIXA16	CombinedTransformationMatrix;	//�����ςݍs��B
};
struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER {
	LPDIRECT3DTEXTURE9* ppTextures;
	LPD3DXMESH pOrigMesh;
	LPD3DXATTRIBUTERANGE pAttributeTable;
	DWORD NumAttributeGroups;
	DWORD NumInfl;
	LPD3DXBUFFER pBoneCombinationBuf;
	D3DXMATRIX** ppBoneMatrixPtrs;
	D3DXMATRIX* pBoneOffsetMatrices;
	DWORD NumPaletteEntries;
	bool UseSoftwareVP;
	DWORD iAttributeSW;
};
class Animation;
/*!
*@brief	�X�L�����f���f�[�^
*/
class SkinModelData{
public:
	/*!
	*@brief	�R���X�g���N�^�B
	*/
	SkinModelData();
	/*!
	*@brief	�f�X�g���N�^�B
	*/
	~SkinModelData();
	/*!
	* @brief	���f���f�[�^�����[�h�B
	*@param[in]	filePath	�t�@�C���p�X�B
	*@param[out]	anim		�A�j���[�V�����t�����f���f�[�^�̏ꍇ�A�A�j���[�V�����N���X���\�z����܂��B
	*/

	void LoadModelData(const char* filePath, Animation* anim);
	/*!
	* @brief	�����[�X�B
	*/
	void Release();
	LPD3DXFRAME GetFrameRoot()
	{
		return frameRoot;
	}
	ID3DXAnimationController* GetAnimationController()
	{
		return pAnimController;
	}

	D3DXMATRIX* GetRootBoneWorldMatrix()
	{
		//frameRoot != nullptr, "m_frameRoot is null";
		D3DXFRAME_DERIVED* frameDer = (D3DXFRAME_DERIVED*)frameRoot;
		return (D3DXMATRIX*)&frameDer->CombinedTransformationMatrix;
	}
	/*!
	* @brief	�{�[���s����X�V�B
	*/
	void UpdateBoneMatrix(const D3DXMATRIX& matWorld);

	LPD3DXMESH GetOrgMeshFirst()
	{
		return GetOrgMesh(frameRoot);
	}

	LPD3DXMESH GetOrgMesh(LPD3DXFRAME frame)const;
private:
	LPD3DXFRAME					frameRoot;		//�t���[�����[�g�B
	ID3DXAnimationController*   pAnimController;	//�A�j���[�V�����R���g���[���B
};
