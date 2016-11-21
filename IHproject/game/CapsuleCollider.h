//�J�v�Z���R���C�_�[

#pragma once

#include "ICollider.h"


class CCapsuleCollider : public ICollider
{
public:

	CCapsuleCollider();
	~CCapsuleCollider();

	//�R���C�_�[�쐬�B
	void Create(float radius, float height)
	{
		shape = new btCapsuleShape(radius, height);
	}
	btCollisionShape* GetBody() override
	{
		return shape;
	}
private:
	btCapsuleShape*		shape;
};
