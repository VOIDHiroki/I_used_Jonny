#pragma once
#include "ICollider.h"

class MeshCollider : public ICollider
{
public:
	//�R���X�g���N�^
	MeshCollider();
	
	//�f�X�g���N�^
	~MeshCollider();

	//�X�L�����f���N���X���烁�b�V���R���C�_�[���쐬
	void CreateMeshFromSkinmodel(SkinModel* model, D3DXMATRIX* offsetMatrix);
	btCollisionShape* GetBody()override
	{
		return meshShape;
	}
	
private:
	typedef std::vector<D3DXVECTOR3>	VertexBuffer;			//���_�o�b�t�@
	typedef std::vector<unsigned int>	IndexBuffer;			//�C���f�b�N�X�o�b�t�@
	std::vector<VertexBuffer*>			vertexBufferArray;		//���_�o�b�t�@�̔z��
	std::vector<IndexBuffer*>			indexBufferArray;		//�C���f�b�N�X�o�b�t�@�̔z��
	btBvhTriangleMeshShape*				meshShape;				//���b�V���̌`��
	btTriangleIndexVertexArray*			stridingMeshInterface;	//!!!�����킩��Ȃ�!!!
};