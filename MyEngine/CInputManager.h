//=================================================================
#pragma once
//=================================================================
#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_
//=================================================================
#define MAX_INPUT_KEY		256
#define MAX_INPUT_MOUSEBTN	3
//=================================================================
class CInputManager
{
public:
	enum eINPUTSTATE
	{
		NONE,
		DOWN,	//	누른 상태.
		UP,		//	눌렀다 뗀 상태.
		PRESS,	//	누르고 있는 상태.
		DBLCLK,	//	더블 클릭.
	};

protected:
	HWND		m_hWnd;

	BYTE		m_kbdBttnCur[MAX_INPUT_KEY];	//	키보드 현재 상태
	BYTE		m_kbdBttnOld[MAX_INPUT_KEY];	//	키보드 이전 상태
	BYTE		m_kbdBttnMap[MAX_INPUT_KEY];	//	키보드 맵
												//	m_kbdBttnCur, m_kbdBttnOld의 결과를 비교하여
												//	최종 결과를 적용하기 위한 버퍼.

	BYTE		m_mouseBtttnCur[MAX_INPUT_MOUSEBTN];	// 마우스 현재 상태
	BYTE		m_mouseBtttnOld[MAX_INPUT_MOUSEBTN];	// 마우스 이전 상태
	BYTE		m_mouseBtttnMap[MAX_INPUT_MOUSEBTN];	// 마우스 맵

	D3DXVECTOR3	m_vcCur;						//	현재 프레임의 마우스 좌표 및 휠의 옵셋 값.
	D3DXVECTOR3 m_vcOld;						//	이전
	D3DXVECTOR3 m_vcEps;						//	현재 프레임과 이전 프레임의 마우스 정보 변화량.

	DWORD		m_dTimeDC;						//	시스템상의 마우스 더블클릭 인식유효 시간.
	DWORD		m_dBtnBgn[MAX_INPUT_MOUSEBTN];		//	각 마우스 버튼의 클릭 시간.
	


public:
	CInputManager();
	virtual ~CInputManager();
	void Init();
	INT			Create(HWND	hWnd);
	INT			FrameMove();
	LRESULT		MsgProc(HWND,UINT, WPARAM, LPARAM);

	BOOL		KeyDown	(INT nKey) { return m_kbdBttnMap[nKey] == DOWN; }
	BOOL		KeyUp	(INT nKey) { return m_kbdBttnMap[nKey] == UP; }
	BOOL		KeyPress(INT nKey) { return m_kbdBttnMap[nKey] == PRESS; }
	INT			KeyState(INT nKey) { return m_kbdBttnMap[nKey]; }

	BOOL		MouseBtnDown(INT nBtn)	{ return m_mouseBtttnMap[nBtn] == DOWN; }
	BOOL		MouseBtnUp(INT nBtn)	{ return m_mouseBtttnMap[nBtn] == UP; }
	BOOL		MouseBtnPress(INT nBtn) { return m_mouseBtttnMap[nBtn] == PRESS; }
	INT			MouseBtnState(INT nBtn) { return m_mouseBtttnMap[nBtn]; }

	//	마우스 좌표.
	D3DXVECTOR3 GetMousePos() { return m_vcCur; }
	//	마우스 이동간격.
	D3DXVECTOR3 GetMouseEps() { return m_vcEps; }

	INT			m_dBtnCnt[MAX_INPUT_MOUSEBTN];	// Double Click Count

};//	class CInputManager
//=================================================================
#endif
//=================================================================