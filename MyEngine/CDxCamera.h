//============================================================
#pragma once
//============================================================
#ifndef _DXCAMERA_H_
#define _DXCAMERA_H_
//============================================================
class CDxCamera
{
protected:
	//----------------------------
	LPDIRECT3DDEVICE9 m_pDev;
	//----------------------------
	D3DXMATRIX	m_matView;
	D3DXMATRIX	m_matProj;
	//----------------------------
	D3DXVECTOR3	m_vecEyePos;
	D3DXVECTOR3	m_vecLookAt;
	D3DXVECTOR3	m_vecUp;
	//----------------------------
	float m_fMoveSpeed;
	float m_fRotSpeed;
	//----------------------------
	void MoveForward(float fSpeed);
	void MoveSide(float fSpeed);
	void MoveUp(float fSpeed);
	void Rotate(D3DXVECTOR3 *pvecDelta, float fSpeed);
	//----------------------------
public:	
	CDxCamera();
	virtual ~CDxCamera() {}
	//----------------------------
	int	Create(LPDIRECT3DDEVICE9 pDev, DWORD dwScreenWidth, DWORD dwScreenHeight, float fMoveSpeed, float fRotSpeed);
	int FrameMove(bool isForward, bool isBack, bool isLeft, bool isRight, bool isUp, bool isDown, bool isMouseRBttnPress, D3DXVECTOR3 mouseEps);
	//----------------------------

};//	class CDxCamera
//============================================================
#endif	//	 _DXCAMERA_H_