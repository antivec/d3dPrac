//========================================================
#pragma once
//========================================================
#ifndef _DXFONT_H_
#define _DXFONT_H_
//========================================================
class CDxFont
{
protected:
	LPD3DXFONT m_pDxFont;
	D3DXVECTOR3 m_vecPos;
	int m_nWidth, m_nHeight;	

public:
	CDxFont();
	virtual ~CDxFont();
	LPD3DXFONT GetFont() { return m_pDxFont; }
	virtual HRESULT Create(LPDIRECT3DDEVICE9 pDev, TCHAR *tszFontName, int fontSize, int fontWeight, BOOL bItalic = FALSE);
	void SetPos(float posX, float posY)
	{
		m_vecPos.x = posX;
		m_vecPos.y = posY;
		m_vecPos.z = 0.f;
	}
	D3DXVECTOR3 GetPos() { return m_vecPos; }

	void SetSize(int width, int height)
	{
		m_nWidth = width;
		m_nHeight = height;
	}
	int GetWidth() { return m_nWidth; }
	int GetHeight() { return m_nHeight; }
	virtual void	Destroy();
	virtual void	Draw(LPD3DXSPRITE spr, TCHAR *tszMessage, int posX, int posY, int width, int height, D3DXCOLOR color, int format = 0);
	virtual void	Draw(LPD3DXSPRITE spr, TCHAR *tszMessage, D3DXCOLOR color, int format = 0);
	int GetTextWidth(LPD3DXSPRITE spr, TCHAR *tszMessage);

};
//========================================================
#endif
//========================================================