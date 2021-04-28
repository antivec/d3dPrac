#include "Global.h"
#define USE_IDXBUFFER


HRESULT CVertexCube::InitVB(LPDIRECT3DDEVICE9 pDev)
{
#ifndef USE_IDXBUFFER

	m_dev = pDev;
	SVtxD vtx[6];

	vtx[0]._pos = D3DXVECTOR3(-1, 1, 0);
	vtx[0]._color = 0xff00ff00;

	vtx[1]._pos = D3DXVECTOR3(1, 1, 0);
	vtx[1]._color = 0xff00ff00;

	vtx[2]._pos = D3DXVECTOR3(-1, -1, 0);
	vtx[2]._color = 0xff00ff00;

	vtx[3]._pos = D3DXVECTOR3(1, 1, 0);
	vtx[3]._color = 0xff00ff00;

	vtx[4]._pos = D3DXVECTOR3(1, -1, 0);
	vtx[4]._color = 0xff0000ff;

	vtx[5]._pos = D3DXVECTOR3(-1, -1, 0);
	vtx[5]._color = 0xff00ff00;

	// 정점버퍼를 생성한다.
	if (FAILED(GetDev()->CreateVertexBuffer(6 * sizeof(SVtxD)
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
#else
	m_dev = pDev;

	SVtxD vtx[8];

	vtx[0]._pos = D3DXVECTOR3(-5, 1, -1);
	vtx[0]._color = 0xffff0000;

	vtx[1]._pos = D3DXVECTOR3(-3, 1, -1);
	vtx[1]._color = 0xff00ff00;

	vtx[2]._pos = D3DXVECTOR3(-5, -1, -1);
	vtx[2]._color = 0xff00ff00;

	vtx[3]._pos = D3DXVECTOR3(-3, -1, -1);
	vtx[3]._color = 0xff0000ff;

	// z = 1
	vtx[4]._pos = D3DXVECTOR3(-5, 1, 1); //( 0 : 4)
	vtx[4]._color = 0x00000000;

	vtx[5]._pos = D3DXVECTOR3(-3, 1, 1); // ( 1 : 5)
	vtx[5]._color = 0x00000000;

	vtx[6]._pos = D3DXVECTOR3(-5, -1, 1); // (2 : 7)
	vtx[6]._color = 0xff00ff00;

	vtx[7]._pos = D3DXVECTOR3(-3, -1, 1); // ( 3: 6 )
	vtx[7]._color = 0xff0000ff;

	// 정점버퍼를 생성한다.
	if (FAILED(m_dev->CreateVertexBuffer(8 * sizeof(SVtxD)
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

#endif
}
HRESULT CVertexCube::InitIB()
{
	SIdx indices[] =
	{
		{ 2,0,1 },{ 2,1,3 }, //앞면
		{2,0,4},{2,4,6}, //왼쪽옆
		{2,6,7},{2,7,3}, // 아랫면
		{1,5,7} ,{1,7,3}, //오른쪽옆
		{0,4,5},{0,5,1}, //윗면
		{6,4,5},{6,5,7} //뒷면
	};

	if (FAILED(m_dev->CreateIndexBuffer(
		12 * sizeof(SIdx), //indices array 개수
		0,
		D3DFMT_INDEX16,
		D3DPOOL_DEFAULT,
		&m_pIB,
		NULL
	)))
	{
		return E_FAIL;
	}

	void* pIndices;
	if (FAILED(m_pIB->Lock(
		0,
		sizeof(SIdx),
		(void**)&pIndices,
		0)))
		return E_FAIL;

	memcpy(pIndices, indices, sizeof(indices));

	m_pIB->Unlock();

	return S_OK;
}
HRESULT CVertexCube::RenderCube()
{

	m_dev->GetRenderState(D3DRS_CULLMODE, &dCullMode);

	// 정점을 디바이스에 연결
	m_dev->SetStreamSource(0, m_pVB, 0, sizeof(SVtxD));
	// 정점 포멧을 설정
	m_dev->SetFVF(D3DFVF_CUSTOM);


#ifndef USE_IDXBUFFER
	// 렌더링
	GetDev()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
#else
	//	인덱스 버퍼 7)
	//	-	인덱스 버퍼를 이용한 렌더링 설정.
	m_dev->SetIndices(m_pIB);
	// 렌더링
	m_dev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,	//	Type
		0,					//	BaseVertexIndex
		0,					//	MinIndex
		36,					//	NumVertices (6 * n)
		0,					//	StartIndex
		12					//	PrimitiveCount ( 2 * n)
	);

#endif

	// 은면 제거 상태 복구.
	m_dev->SetRenderState(D3DRS_CULLMODE, dCullMode);

	return S_OK;
}
CVertexCube::CVertexCube()
{
}
//	HRESULT CMyGame::InitVB()