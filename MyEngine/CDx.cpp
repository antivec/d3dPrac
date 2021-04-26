#include "Global.h"


HRESULT CDx::CreateDX(HWND hWnd, int width, int height, BOOL isWindow)
{
	// D3D생성
	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	// D3D를 통해서 화면 모드를 찾는다.
	D3DDISPLAYMODE d3ddm;
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
		return E_FAIL;

	// 디바이스를 생성하기 위해서는 프리젠트 파라메터 구조체가 필요
	// 전부 0으로 셋팅한다음 일부만 변수세팅
	ZeroMemory(&m_D3DPp, sizeof(m_D3DPp));
	m_D3DPp.Windowed = isWindow;
	m_D3DPp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_D3DPp.BackBufferFormat = d3ddm.Format;
	m_D3DPp.BackBufferCount = 2;
	m_D3DPp.BackBufferWidth = width;
	m_D3DPp.BackBufferHeight = height;
	m_D3DPp.EnableAutoDepthStencil = TRUE;
	//	http://telnet.or.kr/directx/graphics/reference/d3d/constants/d3dpresent.htm
	//	런타임은 윈도우 클라이언트 영역을 즉시 갱신한다.
	//	어댑터 리프레쉬 간격중에 2 회 이상 이 갱신을 실시하는 일이 있다.
	//	이것은, DirectX 8.0 의 D3DSWAPEFFECT_COPY 를 사용하는 것에 동일하다. 
	//	IDirect3DDevice9::Present 에 직접 영향을 주는 경우가 있다. 이 옵션은, 윈도우 스왑 체인 및 풀 스크린 스왑 체인의 양쪽 모두로 항상 사용할 수 있다.
	m_D3DPp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	m_D3DPp.AutoDepthStencilFormat = D3DFMT_D16;

	//	D3DADAPTER_DEFAULT	:	대부분의 그래픽카드는 모노.
	//							듀얼일 경우 이부분을 수정.
	//	D3DDEVTYPE_HAL		:	하드웨어 가속(가장 큰 속도)을 받을 것인가..
	//							하드웨어 지원이 없을 경우 D3D는 소프트웨어로 이를 대체 가능.
	//	D3DCREATE_HARDWARE_VERTEXPROCESSING	:	정점처리를 gpu에 맡김.
	//	D3DCREATE_SOFTWARE_VERTEXPROCESSING :	CPU에 맡김.
	//	D3DCREATE_MIXED_VERTEXPROCESSING    :	HVP, SVP간의 전환 가능.

	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_MIXED_VERTEXPROCESSING, &m_D3DPp, &m_pD3DDevice)))
	{
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_D3DPp, &m_pD3DDevice)))
		{
			SAFE_RELEASE(m_pD3DDevice);
			SAFE_RELEASE(m_pD3D);
			return E_FAIL;
		}
	}

	// DX의 스프라이트는 디바이스가 생성된 후에 만들어야 한다.
	if (FAILED(D3DXCreateSprite(m_pD3DDevice, &m_pD3DSprite)))
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;

		m_pD3D->Release();
		m_pD3D = NULL;

		return E_FAIL;

	}//	if (FAILED(D3DXCreateSprite(m_pD3DDevice, &m_pD3DSprite)))

	return S_OK;

}//	HRESULT CCore::CreateDX()
//-------------------------------
void CDx::CleanUp()
{
	SAFE_RELEASE(m_pD3DSprite);
	SAFE_RELEASE(m_pD3DDevice);
	SAFE_RELEASE(m_pD3D);
}
//-------------------------------
HRESULT CDx::BeginScene()
{
	m_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 120, 160), 1.0f, 0);

	return m_pD3DDevice->BeginScene();
}
//-------------------------------
void CDx::EndScene()
{
	// EndScene
	m_pD3DDevice->EndScene();

	// 후면버퍼 전면버퍼 교체( flipping)
	m_pD3DDevice->Present(0, 0, 0, 0);
}
//-------------------------------
HRESULT CDx::BeginSprite( DWORD flag ) { return m_pD3DSprite->Begin(flag); }
//-------------------------------
void CDx::EndSprite() { m_pD3DSprite->End(); }
//-------------------------------
CDx::~CDx() { CleanUp(); }
//-------------------------------