#include "Global.h"

HRESULT CVertexTxNorm::InitTexture()
{
	m_pTex = new CDxTexture();
	m_pTex->Create(m_dev, "texture/brick.jpg", false);

	return S_OK;
}


void CVertexTxNorm::SetMaterial()
{
	D3DMATERIAL9 mtrl = { 0 };
	mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 1.0f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;

	m_dev->SetMaterial(&mtrl);
}

void CVertexTxNorm::SetLight()
{
	D3DXVECTOR3 vecDir;
	D3DLIGHT9 light;
	memset(&light, 0, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;	//	���� ����.
	light.Diffuse.r = 1.0f;				//	���� ����.
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;

	vecDir = D3DXVECTOR3(cosf(timeGetTime() / 500.f), 1.0f, sinf(timeGetTime() / 500.f));

	//	���� ����.	
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);

	light.Range = 1000.0f;	// ���� ��ȿ ����.

	//	����̽��� ���� ����.
	m_dev->SetLight(0, &light);

	//	���� Ȱ��ȭ.
	m_dev->LightEnable(0, TRUE);

	// �ֺ� ���� ����.
	m_dev->SetRenderState(D3DRS_AMBIENT, 0x00004444);
}

HRESULT CVertexTxNorm::InitVB(LPDIRECT3DDEVICE9 pDev)
{

	m_dev = pDev;

	if (FAILED(InitTexture()))
		return E_FAIL;

	SVtxTxtrNormal vtx[] =

	{
		//	Front..
		{D3DXVECTOR3(-1, -1, -1), D3DXVECTOR3(0, 0, -1), 0,1 },
		{D3DXVECTOR3(-1, 1, -1), D3DXVECTOR3(0, 0, -1), 0,0 },
		{D3DXVECTOR3(1, -1, -1), D3DXVECTOR3(0, 0, -1), 1,1 },
		
		{D3DXVECTOR3(1, 1, -1), D3DXVECTOR3(0, 0, -1), 1,0 },
		{D3DXVECTOR3(1, -1, -1), D3DXVECTOR3(0, 0, -1), 1,1 },
		{D3DXVECTOR3(-1, 1, -1), D3DXVECTOR3(0, 0, -1), 0,0 },

		//	Right..
		{D3DXVECTOR3(1, 1, -1), D3DXVECTOR3(1, 0, 0), 0,0 },
		{D3DXVECTOR3(1, -1, 1), D3DXVECTOR3(1, 0, 0), 1,1 },
		{D3DXVECTOR3(1, -1, -1), D3DXVECTOR3(1, 0, 0), 0,1 },

		{D3DXVECTOR3(1, 1, -1), D3DXVECTOR3(1, 0, 0), 0,0 },
		{D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(1, 0, 0), 1,0 },
		{D3DXVECTOR3(1, -1, 1), D3DXVECTOR3(1, 0, 0), 1,1 },

		//	Back..
		{D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 0, 1), 0,0 },
		{D3DXVECTOR3(-1, -1, 1), D3DXVECTOR3(0, 0, 1), 1,1 },
		{D3DXVECTOR3(1, -1, 1), D3DXVECTOR3(0, 0, 1), 0,1 },

		{D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 0, 1), 0,0 },
		{D3DXVECTOR3(-1, 1, 1), D3DXVECTOR3(0, 0, 1), 1,0 },
		{D3DXVECTOR3(-1, -1, 1), D3DXVECTOR3(0, 0, 1), 1,1 },

		//	Left..
		{D3DXVECTOR3(-1, 1, 1), D3DXVECTOR3(-1, 0, 0), 0,0 },
		{D3DXVECTOR3(-1, -1, -1),D3DXVECTOR3(-1, 0, 0), 1,1  },
		{D3DXVECTOR3(-1, -1, 1), D3DXVECTOR3(-1, 0, 0), 0,1 },

		{D3DXVECTOR3(-1, 1, 1), D3DXVECTOR3(-1, 0, 0), 0,0 },
		{D3DXVECTOR3(-1, 1, -1), D3DXVECTOR3(-1, 0, 0), 1,0 },
		{D3DXVECTOR3(-1, -1, -1), D3DXVECTOR3(-1, 0, 0), 1,1 },

		//	Bottom..
		{D3DXVECTOR3(-1, -1, -1), D3DXVECTOR3(0, -1, 0), 0,0 },
		{D3DXVECTOR3(1, -1, 1), D3DXVECTOR3(0, -1, 0), 1,1 },
		{D3DXVECTOR3(-1, -1, 1), D3DXVECTOR3(0, -1, 0), 0,1 },

		{D3DXVECTOR3(-1, -1, -1), D3DXVECTOR3(0, -1, 0), 0,0 },
		{D3DXVECTOR3(1, -1, 1), D3DXVECTOR3(0, -1, 0), 1,1 },
		{D3DXVECTOR3(1, -1, -1), D3DXVECTOR3(0, -1, 0), 1,0 },

		//	Top..
		{D3DXVECTOR3(-1, 1, 1), D3DXVECTOR3(0, 1, 0), 0,0 },
		{D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 1, 0), 1,0 },
		{D3DXVECTOR3(1, 1, -1), D3DXVECTOR3(0, 1, 0), 1,1 },

		{D3DXVECTOR3(-1, 1, 1), D3DXVECTOR3(0, 1, 0), 0,0 },
		{D3DXVECTOR3(1, 1, -1), D3DXVECTOR3(0, 1, 0), 1,1 },
		{D3DXVECTOR3(-1, 1, -1), D3DXVECTOR3(0, 1, 0), 0,1 },
	};



	// �������۸� �����Ѵ�.
	if (FAILED(m_dev->CreateVertexBuffer(sizeof(vtx)
		, 0
		, D3DFVF_CUSTOM
		, D3DPOOL_MANAGED
		, &m_pVB
		, NULL)))
	{
		return E_FAIL;
	}

	// ���������͸� ä���.
	// Lock�� ������ ������ ����
	void* pvtx;
	if (FAILED(m_pVB->Lock(0, sizeof(vtx), (void**)&pvtx, 0)))
		return E_FAIL;

	memcpy(pvtx, vtx, sizeof(vtx));

	m_pVB->Unlock();

	return S_OK;
}

HRESULT CVertexTxNorm::RenderCube()
{
	SetMaterial();

	SetLight();

	// ���� �������� ���� Ȯ��.
	DWORD dCullMode = 0;
	m_dev->GetRenderState(D3DRS_CULLMODE, &dCullMode);

	// �������� ��Ȱ��ȭ
	m_dev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	/*	�ؽ��� - 3)
		-	�ؽ��� ����. */
	m_dev->SetTexture(0, m_pTex->GetTexture());

	// ������ ����̽��� ����
	m_dev->SetStreamSource(0, m_pVB, 0, sizeof(SVtxTxtrNormal));
	// ���� ������ ����
	m_dev->SetFVF(D3DFVF_XYZTEXNORMAL);
	// ������
	m_dev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 12);

	// ���� ���� ���� ����.
	m_dev->SetRenderState(D3DRS_CULLMODE, dCullMode);

	return S_OK;
}
