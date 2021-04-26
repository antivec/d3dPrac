//========================================================
#include "Global.h"
//========================================================
CCore*	g_pDxCore;
//========================================================
//-------------------------------
CCore::CCore()
{
	g_pDxCore = this;

	strcpy(m_tszClassName, "2D Game App");

	m_hInst = NULL;
	m_hWnd = NULL;
	m_dwWinStyle	= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_VISIBLE;
	m_dwScrWidth	= 800;
	m_dwScrHeight	= 600;

	m_bShowCursor	= TRUE;
	m_bWindowMode	= TRUE;			// Window mode

}//	CCore::CCore()
//-------------------------------
LPDIRECT3DDEVICE9 CCore::GetDev() { return m_pDx->GetDev(); }
LPD3DXSPRITE CCore::GetSprite() { return m_pDx->GetSprite(); }
//-------------------------------
void CCore::RegistWinClass()
{
	// Register the window class
	WNDCLASS wc =
	{
		CS_CLASSDC
		, WndProc
		, 0L
		, 0L
		, m_hInst
		, NULL
		, LoadCursor(NULL,IDC_ARROW)
		, (HBRUSH)GetStockObject(WHITE_BRUSH)
		, NULL
		, m_tszClassName
	};

	RegisterClass(&wc);

}//	void CCore::RegistWinClass()
//-------------------------------
HRESULT CCore::CreateWindows()
{
	//	regist win class
	RegistWinClass();

	//Create the application's window
	RECT rc;
	SetRect(&rc, 0, 0, m_dwScrWidth, m_dwScrHeight);
	AdjustWindowRect(&rc, m_dwWinStyle, FALSE);

	int iScnSysW = ::GetSystemMetrics(SM_CXSCREEN);
	int iScnSysH = ::GetSystemMetrics(SM_CYSCREEN);

	m_hWnd = CreateWindow(m_tszClassName
		, m_tszClassName
		, m_dwWinStyle
		, (iScnSysW - (rc.right - rc.left)) / 2
		, (iScnSysH - (rc.bottom - rc.top)) / 2
		, (rc.right - rc.left)
		, (rc.bottom - rc.top)
		, NULL
		, NULL
		, m_hInst
		, NULL);

	if (m_hWnd == NULL)
		return E_FAIL;

	return S_OK;

}//	HRESULT CCore::CreateWindows()
//-------------------------------
BOOL CCore::Create(HINSTANCE hInst)
{
	m_hInst = hInst;

	if (CreateWindows() == E_FAIL)
		return FALSE;

	m_pDx = new CDx();
	if (m_pDx->CreateDX(m_hWnd, m_dwScrWidth, m_dwScrHeight, m_bWindowMode) == E_FAIL)
	{
		SAFE_DELETE(m_pDx);
		return FALSE;
	}		

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
	ShowCursor(m_bShowCursor);

	if (FAILED(Init()))
		return FALSE;

	m_dwLastTime = timeGetTime();

	m_pInputManager = new CInputManager();

	m_pDxCamera = new CDxCamera();
	m_pDxCamera->Create(GetDev(), m_dwScrWidth, m_dwScrHeight, 0.01f, 0.1f);

	return TRUE;

}//	INT	CCore::Create(HINSTANCE hInst)
//-------------------------------
void CCore::CleanUp()
{
	Destroy();

	SAFE_DELETE(m_pDxCamera);
	SAFE_DELETE(m_pInputManager);
	SAFE_DELETE(m_pDx);
	
}//	void CCore::CleanUp()
//-------------------------------
INT CCore::Run()
{
	MSG msg;
	memset(&msg, 0, sizeof(msg));
	
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		
		}//	if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		else
		{
			if (FAILED(Idle()))
				break;

		}//	~if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))

	}//	while (msg.message != WM_QUIT)

	UnregisterClass(m_tszClassName, m_hInst);

	return 0;

}//	INT CCore::Run()
//-------------------------------
HRESULT CCore::OnRender()
{
	if(FAILED(m_pDx->BeginScene()))
		return E_FAIL;

	if(FAILED(m_pDx->BeginSprite(D3DXSPRITE_ALPHABLEND)))
		return E_FAIL;

	if (FAILED(Render2D()))
		return E_FAIL;

	m_pDx->EndSprite();

	if (FAILED(Render3D()))
		return E_FAIL;

	m_pDx->EndScene();

	return S_OK;

}//	HRESULT CCore::OnRender()
//-------------------------------
HRESULT	CCore::Idle()
{
	if (m_pDx->IsInValidDevice())
		return E_FAIL;
	
	DWORD dwCurTime = timeGetTime();
	m_dwElapsedTime = dwCurTime - m_dwLastTime;
	m_dwLastTime = dwCurTime;

	if (FAILED(FrameMove()))
		return E_FAIL;

	if (FAILED(OnRender()))
		return E_FAIL;

	return S_OK;

}//	HRESULT	CCore::Idle()
//-------------------------------
LRESULT WINAPI CCore::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)	{ return g_pDxCore->MsgProc(hWnd, msg, wParam, lParam); }
//-------------------------------
LRESULT CCore::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//------------------------
	switch (msg)
	{
		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case VK_ESCAPE:
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
					break;

				}//	case VK_ESCAPE:

			}//	switch (wParam)

			break;

		}//	case WM_KEYDOWN:

		case WM_DESTROY:
		{
			CleanUp();
			PostQuitMessage(0);
			break;

		}//	case WM_DESTROY:
				
	}//	switch (msg)
	//------------------------

	return DefWindowProc(hWnd, msg, wParam, lParam);

}//	LRESULT CCore::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//-------------------------------
void CCore::UpdateFPS()
{
	static int frameCount = 0;					//	프레임 호출 횟수 누적.
	static float timeElapsed = 0.0f;			//	프레임간 경과시간 누적.
	static DWORD dwLastTime = timeGetTime();	//	이전 프레임 호출 시간 관리.

	DWORD curTime = timeGetTime();				//	현재 프레임 호출 시간 관리.
	float timeDelta = (curTime - dwLastTime) * 0.001f;	//	프레임간 경과시간 계산.( 초단위 )

	timeElapsed += timeDelta;	//	프레임간 경과시간 누적.

	++frameCount;	//	프레임 호출 횟수 증가.

	if (timeElapsed >= 1.0f)	//	경과시간이 1초 지났나??
	{
		float fps = (float)frameCount / timeElapsed;	//	FPS = 초당 프레임 호출 횟수.
		sprintf(m_tszFPS, TEXT("게임속도 FPS: %f"), fps);     //FPS출력 하는 소스

		frameCount = 0;		//	프레임 호출 횟수 초기화.
		timeElapsed = 0.0f;	//	경과 시간 초기화.

	}//	if (timeElapsed >= 1.0f)

	dwLastTime = curTime;	//	"현재 프레임 시간"은 다음 프레임에선 "이전 프레임 시간".

}//	void CDxCore::UpdateFPS()
CCore::~CCore() { CleanUp(); }
//-------------------------------