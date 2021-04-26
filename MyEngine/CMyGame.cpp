//============================================
#include "Global.h"
//============================================
#define USE_IDXBUFFER
//============================================
CMyGame::CMyGame()	{}
//============================================
CMyGame::~CMyGame()	{}
//============================================
//	�ε��� ���� 4)
//	-	���ؽ� ���� �ʱ�ȭ.
HRESULT CMyGame::InitTexture()
{
	m_pTex = new CDxTexture();
	m_pTex->Create(GetDev(), "texture/wallpape.jpg", false);

	return S_OK;
}

void CMyGame::SetMatrix()
{
	//---------------------------------
	// ���� ��ȯ
	//---------------------------------
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixRotationY(&matWorld, timeGetTime() / 500.0f);	// ȸ�����
	GetDev()->SetTransform(D3DTS_WORLD, &matWorld);			// ����̽��� ���� ����� �����Ѵ�.

}

//	void CMyGame::SetMatrix()
//============================================
INT		CMyGame::Init()
{
	m_pDxFont = new CDxFont();
	if (FAILED(m_pDxFont->Create(GetDev(), _T("�ü�ü"), 20, FW_BOLD)))
		return E_FAIL;


	m_pGrid = new CDxGrid();
	m_pGrid->Create(GetDev());

	m_pVCube = new CVertexCube();


	return 0;

}//	INT		CMyGame::Init()
//============================================
INT		CMyGame::Render2D()
{
	//	��Ʈ ���.
	m_pDxFont->Draw(GetSprite(), _T("fps �׽�Ʈ"), 300, 0, 300, 50, D3DXCOLOR(1, 1, 0, 1), DT_LEFT);
	m_pDxFont->Draw(GetSprite(), m_tszFPS, 0, 0, 300, 50, D3DXCOLOR(1, 1, 0, 1), DT_LEFT);

	return S_OK;
}
//============================================
INT		CMyGame::Render3D()
{
	//	�׸��� ������.
	m_pGrid->FrameMove();
	m_pGrid->Render();

	//	���� ��� ����.
	SetMatrix();	

	// ���� �������� ���� Ȯ��.
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
	//	�ε��� ���� 7)
	//	-	�ε��� ���� ����.
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