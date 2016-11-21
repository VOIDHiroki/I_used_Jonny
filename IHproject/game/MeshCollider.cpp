#include "stdafx.h"
#include "MeshCollider.h"

MeshCollider::MeshCollider() :
stridingMeshInterface(NULL)
{

}
MeshCollider::~MeshCollider()
{
	for (auto& vb : vertexBufferArray){
		delete vb;
	}
	for (auto& ib : indexBufferArray){
		delete ib;
	}
	delete stridingMeshInterface;
}


//SkinModelからメッシュコライダーを作成する
void MeshCollider::CreateMeshFromSkinmodel(SkinModel* model, D3DXMATRIX* offsetMatrix)
{
	stridingMeshInterface = new btTriangleIndexVertexArray;
	//SkinModelからコリジョンで使用する頂点バッファとインデックスバッファを作成する
	LPD3DXMESH mesh = model->GetOrgMeshFirst();
	if (mesh != NULL){
		{
			//頂点ストライドを取得
			DWORD stride = D3DXGetFVFVertexSize(mesh->GetFVF());
			//頂点バッファを取得
			LPDIRECT3DVERTEXBUFFER9 vb;
			mesh->GetVertexBuffer(&vb);
			//頂点バッファの定義を取得
			D3DVERTEXBUFFER_DESC desc;
			vb->GetDesc(&desc);
			//頂点バッファをロックする
			D3DXVECTOR3* pos;
			vb->Lock(0, 0, (void**)&pos, D3DLOCK_READONLY);
			VertexBuffer* vertexBuffer = new VertexBuffer;
			int numVertex = mesh->GetNumVertices();
			//あたりで使用する頂点バッファを作成する。
			for (int v = 0; v < numVertex; v++){
				D3DXVECTOR3 posTmp = *pos;
				if (offsetMatrix){
					D3DXVec3TransformCoord(&posTmp, &posTmp, offsetMatrix);
				}
				vertexBuffer->push_back(posTmp);
				char* p = (char*)pos;
				p += stride;
				pos = (D3DXVECTOR3*)p;
			}
			vb->Unlock();
			vb->Release();
			vertexBufferArray.push_back(vertexBuffer);
		}
		{
		//インデックスバッファを作成
		LPDIRECT3DINDEXBUFFER9 ib;
		mesh->GetIndexBuffer(&ib);
		D3DINDEXBUFFER_DESC desc;
		ib->GetDesc(&desc);
		int stride = 0;
		if (desc.Format == D3DFMT_INDEX16){
			//インデックスが16bit
			stride = 2;
		}
		else if (desc.Format == D3DFMT_INDEX32){
			//インデックスが32bit
			stride = 4;
		}
		//インデックスバッファをロック
		char* p;
		HRESULT hr = ib->Lock(0, 0, (void**)&p, D3DLOCK_READONLY);
		IndexBuffer* indexBuffer = new IndexBuffer;
		for (int i = 0; i < desc.Size / stride; i++){
			unsigned int index;
			if (desc.Format == D3DFMT_INDEX16){
				unsigned short* pIndex = (unsigned short*)p;
				index = (unsigned int)*pIndex;
			}
			else{
				unsigned int* pIndex = (unsigned int*)p;
				index = *pIndex;
			}

			indexBuffer->push_back(index);
			p += stride;
		}
		ib->Unlock();
		ib->Release();
		indexBufferArray.push_back(indexBuffer);
	}
		//インデックスメッシュを作成
		btIndexedMesh indexedMesh;
		IndexBuffer* ib = indexBufferArray.back();
		VertexBuffer* vb = vertexBufferArray.back();
		indexedMesh.m_numTriangles = ib->size() / 3;
		indexedMesh.m_triangleIndexBase = (unsigned char*)(&ib->front());
		indexedMesh.m_triangleIndexStride = 12;
		indexedMesh.m_numVertices = vb->size();
		indexedMesh.m_vertexBase = (unsigned char*)(&vb->front());
		indexedMesh.m_vertexStride = sizeof(D3DXVECTOR3);
		stridingMeshInterface->addIndexedMesh(indexedMesh);

	}
	meshShape = new btBvhTriangleMeshShape(stridingMeshInterface, true);
}