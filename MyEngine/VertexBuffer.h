//===============================================================
#pragma once
//===============================================================
// 정점 구조체
struct SVtxD
{
	//-------------------------------
	D3DXVECTOR3 _pos;	//	정점 위치
	DWORD		_color;	//	정점 색.
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
//	인덱스 버퍼 2)
//	-	인덱스 버퍼 구조체.
struct SIdx
{
	WORD _0, _1, _2;	// 일반적으로 인덱스는 2바이트로 선언.( 약 10년전 )
						// 4바이트도 가능하지만 당시 구형 그래픽카드에서는 지원되지 않음.
}; 

//================================================================================

//texture 좌표 구조체
struct SVtxDTxtr
{
	//-------------------------------
	D3DXVECTOR3 _pos;		//	정점 위치

	float _u, _v;			//	텍스쳐 좌표.
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
	D3DXVECTOR3 _pos;	//	정점 위치	
	D3DXVECTOR3 _normal;	//	노멀 위치
	float _u, _v;		//	텍스쳐 좌표.
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

#define D3DFVF_CUSTOM ( D3DFVF_XYZ | D3DFVF_DIFFUSE) //설정 필요
#define D3DFVF_XYZTEX	(D3DFVF_XYZ | D3DFVF_TEX1)
#define D3DFVF_XYZTEXNORMAL	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)
//===============================================================