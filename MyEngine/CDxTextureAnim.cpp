//===========================================================
#include "Global.h"
#include "CDxTextureAnim.h"
//===========================================================
CDxTextureAnim::CDxTextureAnim(int nFrameCount, DWORD dwFrameTime)
{
	m_dwUpdateTime = dwFrameTime;
	m_nFrameCount = nFrameCount;
}
//------------------------------------------
INT CDxTextureAnim::Create(LPDIRECT3DDEVICE9 pDev, const char* sFile, DWORD dwColorKey)
{
	INT res = CDxTexture::Create(pDev, sFile, dwColorKey);

	if (res == 0)
		m_fFramwWidth = GetImageWidth() / m_nFrameCount;

	return res;

}//	INT CDxTextureAnim::Create(LPDIRECT3DDEVICE9 pDev, const char* sFile, DWORD dwColorKey)
//------------------------------------------
void CDxTextureAnim::OnUpdateFrame( DWORD dwTime )
{
	if (dwTime > m_dwUpdateTime)
	{
		m_drawRect.left += m_fFramwWidth;

		if (m_drawRect.left + m_fFramwWidth >= GetImageWidth())
			m_drawRect.left = 0;

		m_drawRect.right = m_drawRect.left + m_fFramwWidth;

	}//	if ((m_dwEndTime - m_dwBeginTime) > FRAME_REFRESH_TIME)

}//	void CDxTextureAnim::OnUpdateFrame( DWORD dwTime )
//===========================================================