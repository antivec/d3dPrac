//========================================================
#pragma once
//========================================================
#ifndef _DXTEXTURE_H_
#define _DXTEXTURE_H_
//========================================================
class CDxTexture
{
protected:
	LPDIRECT3DDEVICE9	m_pDev;	
	D3DXIMAGE_INFO		m_ImgInfo;
	LPDIRECT3DTEXTURE9	m_pTx;
	D3DXVECTOR3			m_vecPos;
	D3DXVECTOR3			m_vecPivot;
	D3DXCOLOR			m_color;
	RECT				m_drawRect;
	DWORD				m_dwColorKey;

public:
	CDxTexture();
	virtual ~CDxTexture();

	virtual INT		Create(LPDIRECT3DDEVICE9 pDev, const char* sFile, bool applyPow2, DWORD colorKey = 0);
	virtual INT		Create(LPDIRECT3DDEVICE9 pDev, const char* sFile, DWORD colorKey = 0);
	virtual INT		Create(LPDIRECT3DDEVICE9 pDev, const char* sFile, int width, int height, DWORD colorKey = 0);
	virtual void	Destroy();
	void SetPos( D3DXVECTOR3 vecPos ) { m_vecPos = vecPos; }
	void SetPos2D(float posX, float posY)
	{
		D3DXVECTOR3 tmpPos(0, 0, 0);
		tmpPos.x = posX;
		tmpPos.y = posY;
		m_vecPos = tmpPos;
	}
	D3DXVECTOR3 GetPos() { return m_vecPos; }


public:
	INT		GetImageWidth()	{ return m_ImgInfo.Width; }
	INT		GetImageHeight() { return m_ImgInfo.Height; }	
	LPDIRECT3DTEXTURE9 GetTexture() { return m_pTx; }
	void SetPivot(D3DXVECTOR3 vecPivot) { m_vecPivot = vecPivot; }
	RECT		GetImageRect();	
	D3DXVECTOR3 GetImageCenter();	

	void Draw( LPD3DXSPRITE spr, D3DXVECTOR3 vecPos);
	void Draw( LPD3DXSPRITE spr );
};

#endif