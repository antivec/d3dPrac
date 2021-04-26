#pragma once
#ifndef _DXTEXTUREANIM_H_
#define _DXTEXTUREANIM_H_

#include "CDxTexture.h"

class CDxTextureAnim :
	public CDxTexture
{
protected:
	//	������ ����.
	int			m_nFrameCount;
	//	������ ���� �ð�.
	DWORD		m_dwUpdateTime;
	//	������ �ʺ�.
	float m_fFramwWidth;

public:
	CDxTextureAnim(int nFrameCount, DWORD dwFrameTime);
	virtual INT	Create(LPDIRECT3DDEVICE9 pDev, const char* sFile, DWORD dwColorKey = 0);

	void OnUpdateFrame( DWORD dwTime );
};

#endif //	_DXTEXTUREANIM_H_