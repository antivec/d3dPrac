#pragma once
class CVertexTxtr : public CVertexCube
{
private:
	LPDIRECT3DDEVICE9 m_dev;
	LPDIRECT3DVERTEXBUFFER9	m_pVB;
	LPDIRECT3DINDEXBUFFER9	m_pIB;
	DWORD dCullMode = 0;
public:
	virtual HRESULT InitVB(LPDIRECT3DDEVICE9 pDev);
};

