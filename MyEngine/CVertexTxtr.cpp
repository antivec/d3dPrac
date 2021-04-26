#include "Global.h"
HRESULT CVertexTxtr::InitTexture()
{
	m_pTex = new CDxTexture();
	m_pTex->Create(m_dev, "texture/wallpape.jpg", false);

	return S_OK;
}

HRESULT CVertexTxtr::InitVB(LPDIRECT3DDEVICE9 pDev)
{

	m_dev = pDev;

	if(FAILED(InitTexture()))
		return E_FAIL;

	SVtxDTxtr vtx[4];

	vtx[0]._pos = D3DXVECTOR3(3, -1, -1);
	vtx[0]._u = 0.0f;
	vtx[0]._v = 1.0f;

	vtx[1]._pos = D3DXVECTOR3(3, 1, -1);
	vtx[1]._u = 0.0f;
	vtx[1]._v = 0.0f;

	vtx[2]._pos = D3DXVECTOR3(5, -1, -1);
	vtx[2]._u = 1.0f;
	vtx[2]._v = 1.0f;

	vtx[3]._pos = D3DXVECTOR3(5, 1, -1);
	vtx[3]._u = 1.0f;
	vtx[3]._v = 0.0f;

	// �������۸� �����Ѵ�.
	if (FAILED(m_dev->CreateVertexBuffer(4 * sizeof(SVtxDTxtr)
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

void CVertexTxtr::SetLight()
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

HRESULT CVertexTxtr::RenderCube()
{
	//SetLight();

	m_dev->GetRenderState(D3DRS_CULLMODE, &dCullMode);

	// �������� ��Ȱ��ȭ
	m_dev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	/*	�ؽ��� - 3)
		-	�ؽ��� ����. */
	m_dev->SetTexture(0, m_pTex->GetTexture());

	// ������ ����̽��� ����
	m_dev->SetStreamSource(0, m_pVB, 0, sizeof(SVtxDTxtr));
	// ���� ������ ����
	m_dev->SetFVF(D3DFVF_CUSTOM);
	// ������
	m_dev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// ���� ���� ���� ����.
	m_dev->SetRenderState(D3DRS_CULLMODE, dCullMode);

	return S_OK;
}
