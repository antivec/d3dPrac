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
		DOWN,	//	���� ����.
		UP,		//	������ �� ����.
		PRESS,	//	������ �ִ� ����.
		DBLCLK,	//	���� Ŭ��.
	};

protected:
	HWND		m_hWnd;

	BYTE		m_kbdBttnCur[MAX_INPUT_KEY];	//	Ű���� ���� ����
	BYTE		m_kbdBttnOld[MAX_INPUT_KEY];	//	Ű���� ���� ����
	BYTE		m_kbdBttnMap[MAX_INPUT_KEY];	//	Ű���� ��
												//	m_kbdBttnCur, m_kbdBttnOld�� ����� ���Ͽ�
												//	���� ����� �����ϱ� ���� ����.

	BYTE		m_mouseBtttnCur[MAX_INPUT_MOUSEBTN];	// ���콺 ���� ����
	BYTE		m_mouseBtttnOld[MAX_INPUT_MOUSEBTN];	// ���콺 ���� ����
	BYTE		m_mouseBtttnMap[MAX_INPUT_MOUSEBTN];	// ���콺 ��

	D3DXVECTOR3	m_vcCur;						//	���� �������� ���콺 ��ǥ �� ���� �ɼ� ��.
	D3DXVECTOR3 m_vcOld;						//	����
	D3DXVECTOR3 m_vcEps;						//	���� �����Ӱ� ���� �������� ���콺 ���� ��ȭ��.

	DWORD		m_dTimeDC;						//	�ý��ۻ��� ���콺 ����Ŭ�� �ν���ȿ �ð�.
	DWORD		m_dBtnBgn[MAX_INPUT_MOUSEBTN];		//	�� ���콺 ��ư�� Ŭ�� �ð�.
	


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

	//	���콺 ��ǥ.
	D3DXVECTOR3 GetMousePos() { return m_vcCur; }
	//	���콺 �̵�����.
	D3DXVECTOR3 GetMouseEps() { return m_vcEps; }

	INT			m_dBtnCnt[MAX_INPUT_MOUSEBTN];	// Double Click Count

};//	class CInputManager
//=================================================================
#endif
//=================================================================