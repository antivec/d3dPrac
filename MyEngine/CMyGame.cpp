//============================================
#include "Global.h"
//============================================
#define USE_IDXBUFFER
//============================================
CMyGame::CMyGame()	{}
//============================================
CMyGame::~CMyGame()	{}
//============================================
//	인덱스 버퍼 4)
//	-	버텍스 버퍼 초기화.
HRESULT CMyGame::InitTexture()
{
	m_pTex = new CDxTexture();
	m_pTex->Create(GetDev(), "texture/wallpape.jpg", false);

	return S_OK;
}

void CMyGame::SetMatrix()
{
	//---------------------------------
	// 월드 변환
	//---------------------------------
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixRotationY(&matWorld, timeGetTime() / 500.0f);	// 회전행렬
	GetDev()->SetTransform(D3DTS_WORLD, &matWorld);			// 디바이스의 월드 행렬을 설정한다.

}

//	void CMyGame::SetMatrix()
//============================================
INT		CMyGame::Init()
{
	m_pDxFont = new CDxFont();
	if (FAILED(m_pDxFont->Create(GetDev(), _T("궁서체"), 20, FW_BOLD)))
		return E_FAIL;


	m_pGrid = new CDxGrid();
	m_pGrid->Create(GetDev());

	m_pVCube = new CVertexCube();


	return 0;

}//	INT		CMyGame::Init()
//============================================
INT		CMyGame::Render2D()
{
	//	폰트 출력.
	m_pDxFont->Draw(GetSprite(), _T("fps 테스트"), 300, 0, 300, 50, D3DXCOLOR(1, 1, 0, 1), DT_LEFT);
	m_pDxFont->Draw(GetSprite(), m_tszFPS, 0, 0, 300, 50, D3DXCOLOR(1, 1, 0, 1), DT_LEFT);

	return S_OK;
}
//============================================
INT		CMyGame::Render3D()
{
	//	그리드 렌더링.
	m_pGrid->FrameMove();
	m_pGrid->Render();

	//	월드 행렬 설정.
	SetMatrix();	

	// 현재 은면제거 상태 확인.
	m_pVCube->InitVB(GetDev());
	m_pVCube->InitIB();
	m_pVCube->InitCube();

	return 0;

}//	INT		CMyGame::Render()
//============================================
INT		CMyGame::FrameMove()
{
	UpdateFPS();

	if (GetInput())
	{
		GetInput()->FrameMove();

		bool isForward = GetInput()->KeyPress('W');
		bool isBack = GetInput()->KeyPress('S');
		bool isLeft = GetInput()->KeyPress('A');
		bool isRight = GetInput()->KeyPress('D');
		bool isUp = GetInput()->KeyPress('Q');
		bool isDown = GetInput()->KeyPress('Z');
		bool isMouseRBttnPress = GetInput()->MouseBtnPress(1);
		D3DXVECTOR3 mouseEps = GetInput()->GetMouseEps();

		GetCam()->FrameMove(isForward, isBack, isLeft, isRight, isUp, isDown, isMouseRBttnPress, mouseEps );

	}//	if (m_pInputManager)

	return S_OK;
}
//============================================
void	CMyGame::Destroy()
{
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pDxFont);
	//	인덱스 버퍼 7)
	//	-	인덱스 버퍼 정리.
	SAFE_DELETE(m_pTex);
	SAFE_DELETE(m_pVCube);
}
//============================================
LRESULT CMyGame::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (GetInput())
		GetInput()->MsgProc(hWnd, msg, wParam, lParam);

	return CCore::MsgProc(hWnd, msg, wParam, lParam);
}
//============================================//