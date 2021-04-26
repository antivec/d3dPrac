//============================================
/*
	참고 :	https://wonjayk.tistory.com/172
			https://m.blog.naver.com/lgmpfree/100055862741
			https://programmerhk.tistory.com/entry/DrawIndexedPrimitive-%ED%95%A8%EC%88%98
			https://themangs.tistory.com/entry/d3d%EC%9D%98-DrawIndexedPrimitive-%ED%95%A8%EC%88%98%EC%97%90-%EB%8C%80%ED%95%B4%EC%84%9C

	7. 인덱스 버퍼.
		-	정점의 인덱스를 보관하기 위한 전용 버퍼.
		-	정점을 여러번 나열하는 것 보다 메모리 소모량이 적음.
*/
//============================================
#pragma once
//============================================
#ifndef _MYGAME_H_
#define _MYGAME_H_
//============================================
#include "Global.h"
//============================================
class CMyGame :	public CCore
{
public:
	CMyGame();
	virtual ~CMyGame();

	virtual INT		Init();
	virtual INT		Render2D();
	virtual INT		Render3D();
	virtual INT		FrameMove();
	virtual void	Destroy();
	
	virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
	CDxFont*				m_pDxFont;
	
	//------------------------------------------

	HRESULT InitVB();

	//	인덱스 버퍼 3)
	//	-	인덱스 버퍼 초기화 함수.
	HRESULT	InitIB();
	void SetMatrix();
	HRESULT InitTexture();
	//------------------------------------------
	//	그리드.
	CDxGrid*	m_pGrid;
	CVertexCube* m_pVCube;
	CVertexTxtr* m_pVTxtr;
	//------------------------------------------	
	CDxTexture*	m_pTex;
};// class CMyGame :	public CCore

extern CMyGame*	g_pMyGame;
//============================================
#endif // _MYGAME_H_
//============================================