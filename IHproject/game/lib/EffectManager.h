#pragma once


class Effect;

//�G�t�F�N�g�}�l�[�W��
class EffectManager{
public:
	// �R���X�g���N�^
	
	EffectManager();

	// �f�X�g���N�^
	
	~EffectManager();

	/*
	*�G�t�F�N�g�̃��[�h�B
	*�Ǎ��ς݂̃G�t�F�N�g�̏ꍇ�̓��[�h�͍s��ꂸ�A
	*�����̃G�t�F�N�g���A���Ă���
	*filePath	���[�h����G�t�F�N�g�̃t�@�C���p�X�B
	*return		���[�h�����G�t�F�N�g�t�@�C���B
	*/
	ID3DXEffect* LoadEffect( const char* filePath );


	// �����[�X
	void Release();
private:
	std::map<int, ID3DXEffect*>		effectDictionary;	//CEffect�̃C���X�^���X�̃f�B�N�V���i���B�t�@�C���p�X�̃n�b�V���l���L�[�Ɏ����ACEffect�̃C���X�^���X��l�Ɏ��B
};