#pragma once
#include <d3d9.h>
#include <d3dx9effect.h>
#pragma warning( disable : 4996 )
#include <strsafe.h>
#pragma warning( disable : 4996 )
#include <cstdlib>		//一般的なユーティリティの関数を定義
#include <memory>		//メモリを扱うための機能を定義
#include <vector>		//動的配列クラス
#include <list>			//双方向リストを構築したテンプレートクラス
#include <map>			//要素を、キーと値の組み合わせによって管理するコンテナ？

#include "lib/System.h"

#include "lib/Camera.h"
#include "lib/SkinModel.h"
#include "lib/SkinModelData.h"
#include "lib/Animation.h"
#include "lib/Light.h"

#define Vec3Zero D3DXVECTOR3(0.0f,0.0f,0.0f)
#define Vec3One D3DXVECTOR3(1.0f,1.0f,1.0f)
