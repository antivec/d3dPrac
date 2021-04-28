#pragma once
class CVertexTxNorm : public CVertexCube
{
private:
	CDxTexture*	m_pTex;
	LPDIRECT3DDEVICE9 m_dev;
	LPDIRECT3DVERTEXBUFFER9	m_pVB;
	LPDIRECT3DINDEXBUFFER9	m_pIB;
	DWORD dCullMode = 0;
public:
	virtual HRESULT InitVB(LPDIRECT3DDEVICE9 pDev);
	virtual HRESULT RenderCube();
	HRESULT InitTexture();
	void SetMaterial();
	void SetLight();
};

