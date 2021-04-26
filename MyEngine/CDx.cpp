#include "Global.h"


HRESULT CDx::CreateDX(HWND hWnd, int width, int height, BOOL isWindow)
{
	// D3D����
	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	// D3D�� ���ؼ� ȭ�� ��带 ã�´�.
	D3DDISPLAYMODE d3ddm;
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
		return E_FAIL;

	// ����̽��� �����ϱ� ���ؼ��� ������Ʈ �Ķ���� ����ü�� �ʿ�
	// ���� 0���� �����Ѵ��� �Ϻθ� ��������
	ZeroMemory(&m_D3DPp, sizeof(m_D3DPp));
	m_D3DPp.Windowed = isWindow;
	m_D3DPp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_D3DPp.BackBufferFormat = d3ddm.Format;
	m_D3DPp.BackBufferCount = 2;
	m_D3DPp.BackBufferWidth = width;
	m_D3DPp.BackBufferHeight = height;
	m_D3DPp.EnableAutoDepthStencil = TRUE;
	//	http://telnet.or.kr/directx/graphics/reference/d3d/constants/d3dpresent.htm
	//	��Ÿ���� ������ Ŭ���̾�Ʈ ������ ��� �����Ѵ�.
	//	����� �������� �����߿� 2 ȸ �̻� �� ������ �ǽ��ϴ� ���� �ִ�.
	//	�̰���, DirectX 8.0 �� D3DSWAPEFFECT_COPY �� ����ϴ� �Ϳ� �����ϴ�. 
	//	IDirect3DDevice9::Present �� ���� ������ �ִ� ��찡 �ִ�. �� �ɼ���, ������ ���� ü�� �� Ǯ ��ũ�� ���� ü���� ���� ��η� �׻� ����� �� �ִ�.
	m_D3DPp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	m_D3DPp.AutoDepthStencilFormat = D3DFMT_D16;

	//	D3DADAPTER_DEFAULT	:	��κ��� �׷���ī��� ���.
	//							����� ��� �̺κ��� ����.
	//	D3DDEVTYPE_HAL		:	�ϵ���� ����(���� ū �ӵ�)�� ���� ���ΰ�..
	//							�ϵ���� ������ ���� ��� D3D�� ����Ʈ����� �̸� ��ü ����.
	//	D3DCREATE_HARDWARE_VERTEXPROCESSING	:	����ó���� gpu�� �ñ�.
	//	D3DCREATE_SOFTWARE_VERTEXPROCESSING :	CPU�� �ñ�.
	//	D3DCREATE_MIXED_VERTEXPROCESSING    :	HVP, SVP���� ��ȯ ����.

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

	// DX�� ��������Ʈ�� ����̽��� ������ �Ŀ� ������ �Ѵ�.
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

	// �ĸ���� ������� ��ü( flipping)
	m_pD3DDevice->Present(0, 0, 0, 0);
}
//-------------------------------
HRESULT CDx::BeginSprite( DWORD flag ) { return m_pD3DSprite->Begin(flag); }
//-------------------------------
void CDx::EndSprite() { m_pD3DSprite->End(); }
//-------------------------------
CDx::~CDx() { CleanUp(); }
//-------------------------------