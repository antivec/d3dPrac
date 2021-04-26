//========================================================
#pragma once
//========================================================
#ifndef _CORE_H_
#define _CORE_H_
//========================================================
class CDx;
class CCore
{
protected:
	//-------------------------------
	//	win
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	DWORD		m_dwWinStyle;
	DWORD		m_dwScrWidth;
	DWORD		m_dwScrHeight;
	BOOL		m_bShowCursor;
	BOOL		m_bWindowMode;
	TCHAR		m_tszClassName[256];

	//	fps	
	//	http://skmagic.tistory.com/298
	TCHAR	m_tszFPS[256];	
	//-------------------------------
	static LRESULT WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);	
	//-------------------------------
	//	etc
	void UpdateFPS();
	
public:
	//-------------------------------
	CCore();
	~CCore();
	//-------------------------------
	//	core
	BOOL	Create(HINSTANCE hInst);
	INT		Run();
	void	CleanUp();
	HRESULT	Idle();
	LPDIRECT3DDEVICE9 GetDev();
	LPD3DXSPRITE GetSprite();
	//-------------------------------
	//	game
	virtual INT		Init()		{ return 0; }	
	virtual INT		Render2D()	{ return 0; }
	virtual INT		Render3D()	{ return 0; }
	virtual INT		FrameMove() { return 0; }
	virtual void	Destroy()	{			}
	//-------------------------------
	//	procedure
	virtual	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
	//-------------------------------
	DWORD GetElapsedTime() { return m_dwElapsedTime; }
	DWORD GetScrWidth() { return m_dwScrWidth; }
	DWORD GetScrHeight() { return m_dwScrHeight; }
	CInputManager* GetInput() { return m_pInputManager; }	
	CDxCamera* GetCam() { return m_pDxCamera; }
	//-------------------------------

private:
	//-------------------------------
	// 시작 타임
	DWORD		m_dwLastTime;
	//	경과시간
	DWORD		m_dwElapsedTime;
	//-------------------------------
	void RegistWinClass();
	HRESULT CreateWindows();	
	HRESULT OnRender();
	//-------------------------------
	CDx* m_pDx;
	CInputManager *m_pInputManager;
	CDxCamera*	m_pDxCamera;
	//-------------------------------
	
	

};	//class CCore
//========================================================
#endif	//	_DXCORE_H_
