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

	if (FAILED(InitTexture()))
		return E_FAIL;

	SVtxDTxtr vtx[] =

	{
		{D3DXVECTOR3(3, -1, -1), 0,1 },
		{D3DXVECTOR3(3, 1, -1), 0,0 },
		{D3DXVECTOR3(5, -1, -1), 1,1 },

		{D3DXVECTOR3(5, 1, -1), 1,0 },
		{D3DXVECTOR3(5, -1, -1), 1,1 },
		{D3DXVECTOR3(3, 1, -1), 0,0 },

		//	Right..
		{D3DXVECTOR3(5, 1, -1), 0,0 },
		{D3DXVECTOR3(5, -1, 1), 1,1 },
		{D3DXVECTOR3(5, -1, -1), 0,1 },

		{D3DXVECTOR3(5, 1, -1), 0,0 },
		{D3DXVECTOR3(5, 1, 1), 1,0 },
		{D3DXVECTOR3(5, -1, 1), 1,1 },

		//	Back..
		{D3DXVECTOR3(5, 1, 1), 0,0 },
		{D3DXVECTOR3(3, -1, 1), 1,1 },
		{D3DXVECTOR3(5, -1, 1), 0,1 },

		{D3DXVECTOR3(5, 1, 1), 0,0 },
		{D3DXVECTOR3(3, 1, 1), 1,0 },
		{D3DXVECTOR3(3, -1, 1), 1,1 },

		//	Left..
		{D3DXVECTOR3(3, 1, 1), 0,0 },
		{D3DXVECTOR3(3, -1, -1), 1,1 },
		{D3DXVECTOR3(3, -1, 1), 0,1 },

		{D3DXVECTOR3(3, 1, 1), 0,0 },
		{D3DXVECTOR3(3, 1, -1), 1,0 },
		{D3DXVECTOR3(3, -1, -1), 1,1 },

		//	Bottom..
		{D3DXVECTOR3(3, -1, -1), 0,0 },
		{D3DXVECTOR3(5, -1, 1), 1,1 },
		{D3DXVECTOR3(3, -1, 1), 0,1 },

		{D3DXVECTOR3(3, -1, -1), 0,0 },
		{D3DXVECTOR3(5, -1, 1), 1,1 },
		{D3DXVECTOR3(5, -1, -1), 1,0 },

		//	Top..
		{D3DXVECTOR3(3, 1, 1), 0,0 },
		{D3DXVECTOR3(5, 1, 1), 1,0 },
		{D3DXVECTOR3(5, 1, -1), 1,1 },

		{D3DXVECTOR3(3, 1, 1), 0,0 },
		{D3DXVECTOR3(5, 1, -1), 1,1 },
		{D3DXVECTOR3(3, 1, -1), 0,1 },
	};



	// 정점버퍼를 생성한다.
	if (FAILED(m_dev->CreateVertexBuffer(sizeof(vtx)
		, 0
		, D3DFVF_CUSTOM
		, D3DPOOL_MANAGED
		, &m_pVB
		, NULL)))
	{
		return E_FAIL;
	}

	// 정점데이터를 채운다.
	// Lock은 현재의 독점을 유지
	void* pvtx;
	if (FAILED(m_pVB->Lock(0, sizeof(vtx), (void**)&pvtx, 0)))
		return E_FAIL;

	memcpy(pvtx, vtx, sizeof(vtx));

	m_pVB->Unlock();

	return S_OK;
}

HRESULT CVertexTxtr::RenderCube()
{
	//SetLight();

	m_dev->GetRenderState(D3DRS_CULLMODE, &dCullMode);

	// 은면제거 비활성화
	m_dev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	/*	텍스쳐 - 3)
		-	텍스쳐 지정. */
	m_dev->SetTexture(0, m_pTex->GetTexture());

	// 정점을 디바이스에 연결
	m_dev->SetStreamSource(0, m_pVB, 0, sizeof(SVtxDTxtr));
	// 정점 포멧을 설정
	m_dev->SetFVF(D3DFVF_XYZTEX);
	// 렌더링
	m_dev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 12);

	// 은면 제거 상태 복구.
	m_dev->SetRenderState(D3DRS_CULLMODE, dCullMode);

	return S_OK;
}
