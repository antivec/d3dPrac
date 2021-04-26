#include "Global.h"

HRESULT CVertexTxtr::InitVB(LPDIRECT3DDEVICE9 pDev)
{

	m_dev = pDev;
	SVtxDTxtr vtx[4];

	vtx[0]._pos = D3DXVECTOR3(-1, -1, 0);
	vtx[0]._u = 0.0f;
	vtx[0]._v = 1.0f;

	vtx[1]._pos = D3DXVECTOR3(-1, 1, 0);
	vtx[1]._u = 0.0f;
	vtx[1]._v = 0.0f;

	vtx[2]._pos = D3DXVECTOR3(1, -1, 0);
	vtx[2]._u = 1.0f;
	vtx[2]._v = 1.0f;

	vtx[3]._pos = D3DXVECTOR3(1, 1, 0);
	vtx[3]._u = 1.0f;
	vtx[3]._v = 0.0f;

	// 정점버퍼를 생성한다.
	if (FAILED(m_dev->CreateVertexBuffer(4 * sizeof(SVtxDTxtr)
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
