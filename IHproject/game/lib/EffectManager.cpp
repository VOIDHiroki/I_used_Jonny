
#include "stdafx.h"
#include "lib/EffectManager.h"


namespace{

	//�����񂩂�32bit�̃n�b�V���l���쐬�B
	int MakeHash( const char* string )
	{
		int hash = 0;
		int l = (int)strlen(string);
		for ( int i = 0; i < l; i++ ){
			hash = hash * 37 + string[i];
		}
		return hash;
	}
}


EffectManager::EffectManager()
{

}


EffectManager::~EffectManager()
{
	Release();
}


/*
*�G�t�F�N�g�̃��[�h�B
*�Ǎ��ς݂̃G�t�F�N�g�̏ꍇ�̓��[�h�͍s��ꂸ�A
*�����̃G�t�F�N�g���A���Ă���
*filePath	���[�h����G�t�F�N�g�̃t�@�C���p�X�B
*return		���[�h�����G�t�F�N�g�t�@�C���B
*/

LPD3DXEFFECT EffectManager::LoadEffect(const char* filePath)
{

	LPD3DXEFFECT effect = nullptr;
	int hash = MakeHash(filePath);

	auto it = effectDictionary.find(hash);
	if (it == effectDictionary.end()){
		//�V�K�B
		LPD3DXBUFFER compileErrorBuffer = nullptr;
		HRESULT hr = D3DXCreateEffectFromFile(
			g_pd3dDevice,
			filePath,
			NULL,
			NULL,
#ifdef _DEBUG
			D3DXSHADER_DEBUG,
#else
			D3DXSHADER_SKIPVALIDATION,
#endif
			NULL,
			&effect,
			&compileErrorBuffer
			);
		if (FAILED(hr)){
			MessageBox(nullptr, reinterpret_cast<char*>(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
			//�ǂݍ��ݎ��s
			std::abort();
		}

		std::pair<int, LPD3DXEFFECT> node(hash, effect);	//��̒l�����g�ɂ���B�^���w��ł���B
		effectDictionary.insert(node); //�V�����v�f�����A�R���e�i���g������B
	}
	else{
		//�o�^�ς�
		effect = it->second;
	}
	return effect;
}

//�����[�X
void EffectManager::Release()
{
	for (auto p : effectDictionary){
		p.second->Release();
	}
	//�}�b�v����ɂ���
	effectDictionary.clear();
}