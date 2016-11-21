#pragma once
#include "ICollider.h"

class MeshCollider : public ICollider
{
public:
	//コンストラクタ
	MeshCollider();
	
	//デストラクタ
	~MeshCollider();

	//スキンモデルクラスからメッシュコライダーを作成
	void CreateMeshFromSkinmodel(SkinModel* model, D3DXMATRIX* offsetMatrix);
	btCollisionShape* GetBody()override
	{
		return meshShape;
	}
	
private:
	typedef std::vector<D3DXVECTOR3>	VertexBuffer;			//頂点バッファ
	typedef std::vector<unsigned int>	IndexBuffer;			//インデックスバッファ
	std::vector<VertexBuffer*>			vertexBufferArray;		//頂点バッファの配列
	std::vector<IndexBuffer*>			indexBufferArray;		//インデックスバッファの配列
	btBvhTriangleMeshShape*				meshShape;				//メッシュの形状
	btTriangleIndexVertexArray*			stridingMeshInterface;	//!!!何かわからない!!!
};