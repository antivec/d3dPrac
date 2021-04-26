#pragma once
#include "CCollisionBase.h"
class CCollisionSphere : public CCollisionBase
{
	float _rad;
public:
	void SetRad(float rad)	{ _rad = rad; }
	float GetRad()			{ return _rad; }

	virtual bool IsCollision(CCollisionBase* pCollision);
};

