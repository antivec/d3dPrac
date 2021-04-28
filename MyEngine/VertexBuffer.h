//===============================================================
#pragma once
//===============================================================
// ���� ����ü
struct SVtxD
{
	//-------------------------------
	D3DXVECTOR3 _pos;	//	���� ��ġ
	DWORD		_color;	//	���� ��.
	//-------------------------------
	SVtxD() { ZeroMemory(this, sizeof(this)); }
	//-------------------------------
	SVtxD(D3DXVECTOR3 pos, DWORD color)
	{
		_pos = pos;
		_color = color;
	}
	//-------------------------------

};	//	struct SVtxDiffuse
//#define D3DFVF_CUSTOM	(D3DFVF_XYZ|D3DFVF_DIFFUSE)
//===============================================================
//	�ε��� ���� 2)
//	-	�ε��� ���� ����ü.
struct SIdx
{
	WORD _0, _1, _2;	// �Ϲ������� �ε����� 2����Ʈ�� ����.( �� 10���� )
						// 4����Ʈ�� ���������� ��� ���� �׷���ī�忡���� �������� ����.
}; 

//================================================================================

//texture ��ǥ ����ü
struct SVtxDTxtr
{
	//-------------------------------
	D3DXVECTOR3 _pos;		//	���� ��ġ

	float _u, _v;			//	�ؽ��� ��ǥ.
	//-------------------------------
	SVtxDTxtr() { ZeroMemory(this, sizeof(this)); }
	//-------------------------------	

	SVtxDTxtr(float x, float y, float z, float u, float v) { SVtxDTxtr(D3DXVECTOR3(_pos.x, _pos.y, _pos.z), u, v); }
	SVtxDTxtr(D3DXVECTOR3 pos, float u, float v) { _pos = pos; _u = u; _v = v; }
	//-------------------------------
};

struct SVtxTxtrNormal
{
	//-------------------
	D3DXVECTOR3 _pos;	//	���� ��ġ	
	D3DXVECTOR3 _normal;	//	��� ��ġ
	float _u, _v;		//	�ؽ��� ��ǥ.
	//-------------------
	SVtxTxtrNormal() { ZeroMemory(this, sizeof(this)); }
	//-------------------
	SVtxTxtrNormal(D3DXVECTOR3 pos, D3DXVECTOR3 normal, float u, float v)
	{
		_pos = pos;
		_u = u;
		_v = v;
		_normal = normal;
	}
	//-------------------
};

#define D3DFVF_CUSTOM ( D3DFVF_XYZ | D3DFVF_DIFFUSE) //���� �ʿ�
#define D3DFVF_XYZTEX	(D3DFVF_XYZ | D3DFVF_TEX1)
#define D3DFVF_XYZTEXNORMAL	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)
//===============================================================