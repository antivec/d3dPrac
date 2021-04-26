#pragma once
class CCollisionBase
{
	D3DXVECTOR2 _pos;
public:
	CCollisionBase() {}
	virtual ~CCollisionBase() {}
	D3DXVECTOR2 GetPos()			{ return _pos; }
	void SetPos(D3DXVECTOR2 pos)	{ _pos = pos; }

	virtual bool IsCollision(CCollisionBase* pCollision) = 0;
};

