//============================================
#include "Global.h"
//============================================
CDxGrid::CDxGrid()
{
	m_pDev	= NULL;
	m_pLine	= NULL;
	m_bIsActive = true;

}//	CDxGrid::CDxGrid()
//============================================
CDxGrid::~CDxGrid()	{ Destroy(); }
//============================================
INT CDxGrid::Create(LPDIRECT3DDEVICE9 pDev)
{
	m_pDev	= pDev;

	INT		i;
	INT		j;
	FLOAT	fMax;

	fMax = 10000;
	m_pLine = (SVtxD*)malloc( (6 + 20*4 ) * 2 * sizeof(SVtxD));	

	m_pLine[ 0] = SVtxD(-fMax,     0,     0, 0xFFFF0000);
	m_pLine[ 1] = SVtxD(    0,     0,     0, 0xFFFF0000);
	m_pLine[ 2] = SVtxD(    0,     0,     0, 0xFFFF0000);
	m_pLine[ 3] = SVtxD( fMax,     0,     0, 0xFFFF0000);
	
	m_pLine[ 4] = SVtxD(    0, -fMax,     0, 0xFF00FF00);
	m_pLine[ 5] = SVtxD(    0,     0,     0, 0xFF00FF00);
	m_pLine[ 6] = SVtxD(    0,     0,     0, 0xFF00FF00);
	m_pLine[ 7] = SVtxD(    0,  fMax,     0, 0xFF00FF00);
	
	m_pLine[ 8] = SVtxD(    0,     0, -fMax, 0xFF0000FF);
	m_pLine[ 9] = SVtxD(    0,     0,     0, 0xFF0000FF);
	m_pLine[10] = SVtxD(    0,     0,     0, 0xFF0000FF);
	m_pLine[11] = SVtxD(    0,     0,  fMax, 0xFF0000FF);

	j =6 * 2;

	DWORD	d1 = 0xFF999999;
	DWORD	d2 = 0xFF555555;

	SVtxD*	pLine = &m_pLine[j];

	for(i=0; i<20; ++i)
	{
		pLine[8*i +0 ] = SVtxD(-200.f, 0.f, 10.f * (i+1), (i%2)? d1 : d2);
		pLine[8*i +1 ] = SVtxD( 200.f, 0.f, 10.f * (i+1), (i%2)? d1 : d2);
		pLine[8*i +2 ] = SVtxD(-200.f, 0.f, -10.f* (i+1), (i%2)? d1 : d2);
		pLine[8*i +3 ] = SVtxD( 200.f, 0.f, -10.f* (i+1), (i%2)? d1 : d2);

		pLine[8*i +4 ] = SVtxD( 10.f * (i+1), 0,-200.f, (i%2)? d1 : d2);
		pLine[8*i +5 ] = SVtxD( 10.f * (i+1), 0, 200.f, (i%2)? d1 : d2);
		pLine[8*i +6 ] = SVtxD( -10.f * (i+1), 0,-200.f, (i%2)? d1 : d2);
		pLine[8*i +7 ] = SVtxD( -10.f * (i+1), 0, 200.f, (i%2)? d1 : d2);
	
	}//	for(i=0; i<20; ++i)

	return 0;

}//	INT CDxGrid::Create(LPDIRECT3DDEVICE9 pDev)
 //============================================
void CDxGrid::Destroy()
{
	if(m_pLine)
	{
		free(m_pLine);
		m_pLine = NULL;
	}

}//	void CDxGrid::Destroy()
//============================================
INT	CDxGrid::FrameMove()
{
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);	
	m_pDev->SetTransform(D3DTS_WORLD, &matWorld);			// 디바이스의 월드 행렬을 설정한다.

	if (g_pMyGame->GetInput()->KeyUp('G'))
		SetActive(!IsActive()); 

	return 0;

}//	INT	CDxGrid::FrameMove()
//============================================
void CDxGrid::Render()
{
	if (m_bIsActive)
	{
		//	조명 필요 없음.
		m_pDev->SetRenderState(D3DRS_LIGHTING, FALSE);

		//	텍스쳐 필요 없음.
		m_pDev->SetTexture(0, 0);
		m_pDev->SetFVF(SVtxD::FVF);

		//	버텍스 버퍼를 생성하지 않고 시스템 메모리의 정보만으로 폴리곤을 그림.
		//	시스테 메모리의 내용을 gpu 에 써야하기 때문에 속도가 느림.
		//	UP : User Point
		m_pDev->DrawPrimitiveUP
		(
			D3DPT_LINELIST,	//	도형 그리기 타입.
			6 + 4 * 20,		//	그릴 도형의 갯수.
			m_pLine,		//	버텍스 정보를 저장한 배열 포인터.
			sizeof(SVtxD)	//	버텍스 성분 하나의 크기.
		);

	}//	if (m_isActive)	

}//	void CDxGrid::Render()
 //============================================