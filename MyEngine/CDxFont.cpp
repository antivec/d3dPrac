//========================================================
//	참고 : https://zoom-up.tistory.com/15
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
		, fontSize				//	높이
		, 0						//	가로
		, fontWeight			//	두께.
		, 1						//	밉맵레벨, 사용하지 않음. 0은 생성.
		, bItalic				//	이탤릭체.
		, DEFAULT_CHARSET		//	캐릭터 셋.문자 집합.
		, OUT_DEFAULT_PRECIS	//	OutputPrecision( 정밀성 ), 높을수록 출력속도 느림.
		, DEFAULT_QUALITY		//	퀄리티
		, FF_DONTCARE			//	PitchAndFamily, 기본 간격 및 글꼴 집합.
		, tszFontName			//	폰트명
		, &m_pDxFont)))			//	폰트 객체
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
//	참고		: https://stackoverflow.com/questions/20177781/how-to-get-text-width-directx-c
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
		spr,			//	스프라이트
		tszMessage,		//	메시지
		-1,				//	메시지 길이, 텍스트가 널문자 만날 때까지만 렌더링.
		&rc,			//	출력 영역
		format,			//	포맷
		color			//	색
	);

}//	void	CDxFont::DrawText(TCHAR *tszMessage, int posX, int posY, int width, int height, D3DXCOLOR color)
//========================================================