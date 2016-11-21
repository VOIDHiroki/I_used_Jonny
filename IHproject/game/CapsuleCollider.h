//カプセルコライダー

#pragma once

#include "ICollider.h"


class CCapsuleCollider : public ICollider
{
public:

	CCapsuleCollider();
	~CCapsuleCollider();

	//コライダー作成。
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
