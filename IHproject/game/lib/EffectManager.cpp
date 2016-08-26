
#include "stdafx.h"
#include "lib/EffectManager.h"


namespace{

	//文字列から32bitのハッシュ値を作成。
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
*エフェクトのロード。
*読込済みのエフェクトの場合はロードは行われず、
*既存のエフェクトが帰ってくる
*filePath	ロードするエフェクトのファイルパス。
*return		ロードしたエフェクトファイル。
*/

LPD3DXEFFECT EffectManager::LoadEffect(const char* filePath)
{

	LPD3DXEFFECT effect = nullptr;
	int hash = MakeHash(filePath);

	auto it = effectDictionary.find(hash);
	if (it == effectDictionary.end()){
		//新規。
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
			//読み込み失敗
			std::abort();
		}

		std::pair<int, LPD3DXEFFECT> node(hash, effect);	//二つの値を糸組にする。型を指定できる。
		effectDictionary.insert(node); //新しい要素を入れ、コンテナを拡張する。
	}
	else{
		//登録済み
		effect = it->second;
	}
	return effect;
}

//リリース
void EffectManager::Release()
{
	for (auto p : effectDictionary){
		p.second->Release();
	}
	//マップを空にする
	effectDictionary.clear();
}