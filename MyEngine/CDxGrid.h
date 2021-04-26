// Interface for the CDxGrid class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _McGrid_H_
#define _McGrid_H_

class CDxGrid
{
public:
	struct SVtxD
	{
		D3DXVECTOR3	p;
		DWORD		d;
		
		SVtxD()								
		{
			p.x=p.y=p.z=0.f;d=0xFFFFFFFF;
		}
		SVtxD(FLOAT X,FLOAT Y,FLOAT Z,DWORD D)
		{
			p.x=X; p.y=Y; p.z=Z; d=D;
		}
		enum	{FVF = (D3DFVF_XYZ|D3DFVF_DIFFUSE),};
	};

protected:
	LPDIRECT3DDEVICE9	m_pDev;
	SVtxD*		m_pLine;
	bool		m_bIsActive;
	
public:
	CDxGrid();
	~CDxGrid();

	INT		Create(LPDIRECT3DDEVICE9 pDev);
	void	Destroy();

	INT		FrameMove();
	void	Render();
	void	SetActive(bool isActive) { m_bIsActive = isActive; }
	bool	IsActive() { return m_bIsActive; }
};

#endif