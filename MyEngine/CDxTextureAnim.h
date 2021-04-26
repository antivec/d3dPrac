#pragma once
#ifndef _DXTEXTUREANIM_H_
#define _DXTEXTUREANIM_H_

#include "CDxTexture.h"

class CDxTextureAnim :
	public CDxTexture
{
protected:
	//	프레임 갯수.
	int			m_nFrameCount;
	//	프레임 갱신 시간.
	DWORD		m_dwUpdateTime;
	//	프레임 너비.
	float m_fFramwWidth;

public:
	CDxTextureAnim(int nFrameCount, DWORD dwFrameTime);
	virtual INT	Create(LPDIRECT3DDEVICE9 pDev, const char* sFile, DWORD dwColorKey = 0);

	void OnUpdateFrame( DWORD dwTime );
};

#endif //	_DXTEXTUREANIM_H_