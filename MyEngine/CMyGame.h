//============================================
/*
	���� :	https://wonjayk.tistory.com/172
			https://m.blog.naver.com/lgmpfree/100055862741
			https://programmerhk.tistory.com/entry/DrawIndexedPrimitive-%ED%95%A8%EC%88%98
			https://themangs.tistory.com/entry/d3d%EC%9D%98-DrawIndexedPrimitive-%ED%95%A8%EC%88%98%EC%97%90-%EB%8C%80%ED%95%B4%EC%84%9C

	7. �ε��� ����.
		-	������ �ε����� �����ϱ� ���� ���� ����.
		-	������ ������ �����ϴ� �� ���� �޸� �Ҹ��� ����.
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

	//	�ε��� ���� 3)
	//	-	�ε��� ���� �ʱ�ȭ �Լ�.
	HRESULT	InitIB();
	void SetMatrix();
	HRESULT InitTexture();
	//------------------------------------------
	//	�׸���.
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