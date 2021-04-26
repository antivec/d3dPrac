#pragma once
#include "CCollisionBase.h"
#include <Windows.h>
class CCollisionAABB : public CCollisionBase
{
	RECT _rect;

public :
	RECT GetRect() { return _rect; }
	void SetRect(int left, int top, int width, int height);

	virtual bool IsCollision(CCollisionBase* pCollision);
};

