#pragma once
class ICollider;

struct RigidBodyInfo
{
	RigidBodyInfo()
	{
		pos = Vec3Zero;
		rot = QuaternionIdentity;
	}
	D3DXVECTOR3 pos;
	D3DXQUATERNION rot;
	ICollider* collider;
	float mass;
};

class RigidBody
{
public:
	RigidBody();
	~RigidBody();
	void Release();
	void Create(RigidBodyInfo& rbInfo);
	btRigidBody* GetBody()
	{
		return rigidBody;
	}
private:
	btRigidBody*			rigidBody;
	btDefaultMotionState*	myMotionState;

};