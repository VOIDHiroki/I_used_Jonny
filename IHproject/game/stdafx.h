#pragma once
#include <d3d9.h>
#include <d3dx9effect.h>
#pragma warning( disable : 4996 )
#include <strsafe.h>
#pragma warning( disable : 4996 )
#include <cstdlib>		//��ʓI�ȃ��[�e�B���e�B�̊֐����`
#include <memory>		//���������������߂̋@�\���`
#include <vector>		//���I�z��N���X
#include <list>			//�o�������X�g���\�z�����e���v���[�g�N���X
#include <map>			//�v�f���A�L�[�ƒl�̑g�ݍ��킹�ɂ���ĊǗ�����R���e�i�H

#include "lib/System.h"

#include "lib/Camera.h"
#include "lib/SkinModel.h"
#include "lib/SkinModelData.h"
#include "lib/Animation.h"
#include "lib/Light.h"

#define Vec3Zero D3DXVECTOR3(0.0f,0.0f,0.0f)
#define Vec3One D3DXVECTOR3(1.0f,1.0f,1.0f)
