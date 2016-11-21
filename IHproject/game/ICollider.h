

#pragma once


class ICollider{
public:
	virtual btCollisionShape* GetBody() = 0;
};