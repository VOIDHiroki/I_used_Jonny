#include "stdafx.h"
#include "CapsuleCollider.h"

CCapsuleCollider::CCapsuleCollider() :
shape(nullptr)
{
}

CCapsuleCollider::~CCapsuleCollider()
{
	delete shape;
}