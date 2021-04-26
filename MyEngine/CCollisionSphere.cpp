#include "Global.h"
//-----------------------------------------------------
bool CCollisionSphere::IsCollision(CCollisionBase *pTmpCheck)
{
	CCollisionSphere *pTmp = (CCollisionSphere*)pTmpCheck;

	float curDist = sqrtf(	(pTmp->GetPos().x - GetPos().x) * (pTmp->GetPos().x - GetPos().x) +
							(pTmp->GetPos().y - GetPos().y) * (pTmp->GetPos().y - GetPos().y) );

	if (curDist < _rad + pTmp->GetRad())
		return true;

	return false;

}//	bool CCollisionSphere::IsCollision(CCollisionBase *pTmpCheck)
//-----------------------------------------------------