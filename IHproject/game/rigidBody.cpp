#include "stdafx.h"
#include "rigidBody.h"
#include "ICollider.h"

RigidBody::RigidBody()
{
}

RigidBody::~RigidBody()
{
	Release();
}

void RigidBody::Release()
{
	delete rigidBody;
	delete myMotionState;
	rigidBody = NULL;
	myMotionState = NULL;
}

void RigidBody::Create(RigidBodyInfo& rbInfo)
{
	Release();
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(rbInfo.pos.x, rbInfo.pos.y, rbInfo.pos.z));
	transform.setRotation(btQuaternion(rbInfo.rot.x, rbInfo.rot.y, rbInfo.rot.z,rbInfo.rot.w));
	myMotionState = new btDefaultMotionState;
	btRigidBody::btRigidBodyConstructionInfo btRbInfo(rbInfo.mass, myMotionState, rbInfo.collider->GetBody(), btVector3(0, 0, 0));
	//„‘Ì‚ğì‚é
	rigidBody = new btRigidBody(btRbInfo);
}