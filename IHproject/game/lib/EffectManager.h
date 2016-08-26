#pragma once


class Effect;

//エフェクトマネージャ
class EffectManager{
public:
	// コンストラクタ
	
	EffectManager();

	// デストラクタ
	
	~EffectManager();

	/*
	*エフェクトのロード。
	*読込済みのエフェクトの場合はロードは行われず、
	*既存のエフェクトが帰ってくる
	*filePath	ロードするエフェクトのファイルパス。
	*return		ロードしたエフェクトファイル。
	*/
	ID3DXEffect* LoadEffect( const char* filePath );


	// リリース
	void Release();
private:
	std::map<int, ID3DXEffect*>		effectDictionary;	//CEffectのインスタンスのディクショナリ。ファイルパスのハッシュ値をキーに持ち、CEffectのインスタンスを値に持つ。
};