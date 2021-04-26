#pragma once
class CDx
{
	LPDIRECT3D9				m_pD3D;
	D3DPRESENT_PARAMETERS	m_D3DPp;
	LPDIRECT3DDEVICE9		m_pD3DDevice;
	LPD3DXSPRITE			m_pD3DSprite = NULL;

public :
	HRESULT CreateDX( HWND hWnd, int width, int height, BOOL isWindow );
	void CleanUp();
	~CDx();
	
	HRESULT BeginScene();
	HRESULT BeginSprite( DWORD flag );
	void EndSprite();
	void EndScene();	
	LPDIRECT3DDEVICE9 GetDev()	{ return m_pD3DDevice; }
	LPD3DXSPRITE GetSprite()	{ return m_pD3DSprite; }
	bool IsInValidDevice()		{ return GetDev() == NULL; }

};

