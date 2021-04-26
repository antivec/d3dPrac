#include"Global.h"
//-----------------------------------------------------
void CCollisionAABB::SetRect(int left, int top, int width, int height)
{
	_rect.left = left;
	_rect.top = top;
	_rect.right = left + width;
	_rect.bottom = top + height;

}//	void CCollisionAABB::SetRect(int left, int top, int right, int bottom)
//-----------------------------------------------------
bool CCollisionAABB::IsCollision(CCollisionBase* pTmpCheck)
{
	CCollisionAABB *pTmp = (CCollisionAABB*)pTmpCheck;
		
	if ((_rect.left <= pTmp->GetRect().right && pTmp->GetRect().left <= _rect.right) &&
		(_rect.top <= pTmp->GetRect().bottom && pTmp->GetRect().top <= _rect.bottom))
		return true;

	return false;

}//	bool CCollisionAABB::IsCollision(CCollisionBase* pTmpCheck)
//-----------------------------------------------------