//========================================================
//	���� : https://zoom-up.tistory.com/15
//========================================================
#include "Global.h"
//========================================================
CDxFont::CDxFont()
{
	m_pDxFont = NULL;
}
//========================================================
CDxFont::~CDxFont() { Destroy(); }
//========================================================
HRESULT CDxFont::Create(LPDIRECT3DDEVICE9 pDev, TCHAR *tszFontName, int fontSize, int fontWeight, BOOL bItalic )
{
	if (FAILED(D3DXCreateFont(pDev
		, fontSize				//	����
		, 0						//	����
		, fontWeight			//	�β�.
		, 1						//	�Ӹʷ���, ������� ����. 0�� ����.
		, bItalic				//	���Ÿ�ü.
		, DEFAULT_CHARSET		//	ĳ���� ��.���� ����.
		, OUT_DEFAULT_PRECIS	//	OutputPrecision( ���м� ), �������� ��¼ӵ� ����.
		, DEFAULT_QUALITY		//	����Ƽ
		, FF_DONTCARE			//	PitchAndFamily, �⺻ ���� �� �۲� ����.
		, tszFontName			//	��Ʈ��
		, &m_pDxFont)))			//	��Ʈ ��ü
		return E_FAIL;

	return S_OK;

}//	HRESULT CDxFont::Create(LPDIRECT3DDEVICE9 pDev, char *szFontName, int fontSize)
//========================================================
void	CDxFont::Destroy() { SAFE_RELEASE(m_pDxFont); }
//========================================================
void	CDxFont::Draw(LPD3DXSPRITE spr, TCHAR *tszMessage, D3DXCOLOR color, int format)
{
	RECT	rc;
	SetRect(&rc, m_vecPos.x, m_vecPos.y, m_vecPos.x + m_nWidth, m_vecPos.y + m_nHeight);
	Draw(
		spr,
		tszMessage,
		m_vecPos.x,
		m_vecPos.y,
		m_vecPos.x + m_nWidth,
		m_vecPos.y + m_nHeight,
		color,
		format
	);
}//	void	CDxFont::Draw(LPD3DXSPRITE spr, TCHAR *tszMessage, D3DXCOLOR color, int format)
//----------------------------------------------------
//	����		: https://stackoverflow.com/questions/20177781/how-to-get-text-width-directx-c
//			  https://docs.microsoft.com/en-us/windows/win32/direct3d9/id3dxfont--drawtext
int CDxFont::GetTextWidth(LPD3DXSPRITE spr, TCHAR *tszMessage)
{
	RECT rcRect = { 0,0,0,0 };
	if (m_pDxFont)
	{
		m_pDxFont->DrawText(NULL, tszMessage, strlen(tszMessage), &rcRect, DT_CALCRECT,
			D3DCOLOR_XRGB(0, 0, 0));
	}

	return rcRect.right - rcRect.left;
}
//----------------------------------------------------
void	CDxFont::Draw(LPD3DXSPRITE spr, TCHAR *tszMessage, int posX, int posY, int width, int height, D3DXCOLOR color, int format )
{
	RECT	rc;
	SetRect(&rc, posX, posY, posX + width, posY + height);

	m_pDxFont->DrawText(
		spr,			//	��������Ʈ
		tszMessage,		//	�޽���
		-1,				//	�޽��� ����, �ؽ�Ʈ�� �ι��� ���� �������� ������.
		&rc,			//	��� ����
		format,			//	����
		color			//	��
	);

}//	void	CDxFont::DrawText(TCHAR *tszMessage, int posX, int posY, int width, int height, D3DXCOLOR color)
//========================================================