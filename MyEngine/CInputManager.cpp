//============================================================
//	참고 : https://blog.naver.com/jackielee2/10015178344
//============================================================
// 휠마우스를 쓰려면 이 구문은 반드시 필요.
#define _WIN32_WINNT 0x0400
//============================================================
#include "Global.h"
//============================================================
//------------------------------------
CInputManager::CInputManager()
{
	m_hWnd		= NULL; // for Mouse

	Init();

}//	CInputManager::CInputManager()
//------------------------------------
CInputManager::~CInputManager()	{}
//------------------------------------
void CInputManager::Init()
{
	memset(m_kbdBttnOld, 0, sizeof(m_kbdBttnOld));
	memset(m_kbdBttnCur, 0, sizeof(m_kbdBttnCur));
	memset(m_kbdBttnMap, 0, sizeof(m_kbdBttnMap));

	memset(m_mouseBtttnCur, 0, sizeof(m_mouseBtttnCur));
	memset(m_mouseBtttnOld, 0, sizeof(m_mouseBtttnOld));
	memset(m_mouseBtttnMap, 0, sizeof(m_mouseBtttnMap));

	m_vcCur = D3DXVECTOR3(0, 0, 0);
	m_vcOld = D3DXVECTOR3(0, 0, 0);
	m_vcEps = D3DXVECTOR3(0, 0, 0);

	m_dTimeDC = 0;
	memset(m_dBtnBgn, 0, sizeof(m_dBtnBgn));
	memset(m_dBtnCnt, 0, sizeof(m_dBtnCnt));

	//	주어진 배열의 상태에 따라서 키보드 상태를 세팅.
	//	참고 : http://egloos.zum.com/ieee/v/8985330
	SetKeyboardState(m_kbdBttnCur);
}
//------------------------------------
INT	CInputManager::Create(HWND hWnd)
{
	Init();	

	m_hWnd			= hWnd;
	
	//	GetDoubleClickTime()
	//	-	현재 Windows에 설정되어 있는 더블 클릭 시간간격을 반환.
	m_dTimeDC		= GetDoubleClickTime();

	//	GetTickCount()
	//	-	timeGetTime() 함수와 동일한 기능.
	//	-	정밀도가 더 높음.
	m_dBtnBgn[0]	= GetTickCount();
	for(int i=1; i< MAX_INPUT_MOUSEBTN; ++i)
		m_dBtnBgn[i]	= m_dBtnBgn[0];

	memset(m_dBtnCnt, 0, sizeof(m_dBtnCnt));

	//	마우스 스크롤 값 얻기.
	//	일반적으로 3으로 설정되어 잇음.
	UINT ucNumLines=0;
	SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &ucNumLines, 0);

	return 0;

}//	INT	CInputManager::Create(HWND hWnd)
//------------------------------------
INT CInputManager::FrameMove()	// Mouse
{
	INT curIdx	= 0;

	// 1.	current 값을 old에 복사, 이전 상태를 저장한다.
	memcpy(m_kbdBttnOld, m_kbdBttnCur, sizeof(m_kbdBttnOld));			//	키보드
	memcpy(m_mouseBtttnOld, m_mouseBtttnCur, sizeof(m_mouseBtttnOld));	//	마우스
	
	// 2.	Current 와 Map의 값을 0으로 초기화
	memset(m_kbdBttnCur, 0, sizeof(m_kbdBttnCur));			//	키보드
	memset(m_kbdBttnMap, 0, sizeof(m_kbdBttnMap));

	memset(m_mouseBtttnCur, 0, sizeof(m_mouseBtttnCur));	//	마우스
	memset(m_mouseBtttnMap, 0, sizeof(m_mouseBtttnMap));
	
	//3.	current 이벤트 를 가져옴
	//		키보드의 모든 키의 상태를 256개의 ASCII배열에 의해서 return
	/*
		1.	VK_LBUTTON ~ VK_OEM_CLEAR까지의 가상 키코드 상태를 얻어옴.(vs 2017기준)

		2.	256개의 상태중 사용하지 않는 키코드와 예약된 키코드가 있어서 
			256개의 가상 키코드가 다 유효하진 않다.( winuser.h 참고 )

		3.	반환값.

					|	이전 프레임		|		호출 시점 프레임
			------------------------------------------------------
			0x00	|		X			|			X
			0x01	|		O			|			X
			0x80	|		X			|			O
			0x81	|		O			|			O
	*/
	GetKeyboardState(m_kbdBttnCur);
		
	
	// Keyboard 값 세팅
	for(curIdx = 0; curIdx < MAX_INPUT_KEY; ++curIdx)
	{	
		BYTE	vKey = m_kbdBttnCur[curIdx] & 0x80;		//	현재의 키보드 상태를 읽어온다.
															
		m_kbdBttnCur[curIdx] = (vKey)? 1: 0;			// 키보드 상태를 0과 1로 정한다.

		INT nOld = m_kbdBttnOld[curIdx];
		INT nCur = m_kbdBttnCur[curIdx];

		if (0 == nOld && 1 == nCur)
			m_kbdBttnMap[curIdx] = DOWN;	// Down
		else if (1 == nOld && 0 == nCur)
			m_kbdBttnMap[curIdx] = UP;		// UP
		else if (1 == nOld && 1 == nCur)
			m_kbdBttnMap[curIdx] = PRESS;	// PRESS
		else
			m_kbdBttnMap[curIdx] = NONE;	// NONE

	}//	for(curIdx = 0; curIdx < MAX_INPUT_KEY; ++curIdx)

	// Mouse button 값 세팅
	m_mouseBtttnCur[0] = m_kbdBttnCur[VK_LBUTTON];	// 마우스 왼쪽
	m_mouseBtttnCur[1] = m_kbdBttnCur[VK_RBUTTON];	// 마우스 오른쪽
	m_mouseBtttnCur[2] = m_kbdBttnCur[VK_MBUTTON];	// 마우스 가운데

	for(curIdx = 0; curIdx < MAX_INPUT_MOUSEBTN; ++curIdx)
	{
		INT nOld = m_mouseBtttnOld[curIdx];
		INT nCur = m_mouseBtttnCur[curIdx];

		if		(0 == nOld && 1 ==nCur) m_mouseBtttnMap[curIdx] = DOWN;		// Down
		else if (1 == nOld && 0 ==nCur) m_mouseBtttnMap[curIdx] = UP;		// UP
		else if (1 == nOld && 1 ==nCur) m_mouseBtttnMap[curIdx] = PRESS;	// PRESS
		else							m_mouseBtttnMap[curIdx] = NONE;		// NONE
	}

	// 4. Update Mouse Position
	POINT pt;
	GetCursorPos(&pt);				//	바탕화면상의 마우스 좌표를 얻어옴.
	ScreenToClient(m_hWnd, &pt);	//	m_hWnd의 클라이언트 좌표로 변환.

	m_vcCur.x = FLOAT(pt.x);
	m_vcCur.y = FLOAT(pt.y);

	m_vcEps = m_vcCur - m_vcOld;

	m_vcOld = m_vcCur;

	//5. 더블 클릭 체크.
	DWORD dBtnCur = GetTickCount();	//	OS부팅할 때부터 지나간 시간을 msec 단위로 리턴.

	for(curIdx = 0; curIdx < MAX_INPUT_MOUSEBTN; ++curIdx)
	{
		//	버튼 다운 체크.
		if(DOWN == m_mouseBtttnMap[curIdx])
		{
			//	이전 프레임에서 한번 눌렸다.
			if( 1== m_dBtnCnt[curIdx])
			{
				//	더블 클릭 인터벌 시간이 지났는가?
				if( (dBtnCur - m_dBtnBgn[curIdx]) >= m_dTimeDC)
				{
					//	카운트 초기화.
					m_dBtnCnt[curIdx] = 0;
				}
			}
			
			//	카운트 증가.
			++m_dBtnCnt[curIdx];

			//	1회 눌렸는가?
			if(1 == m_dBtnCnt[curIdx])
				m_dBtnBgn[curIdx]	= dBtnCur;	//	현재 시간을 할당.

		}//	if(DOWN == m_mouseBtttnMap[curIdx])


		//	버튼 업 체크.
		if(UP == m_mouseBtttnMap[curIdx])
		{
			//	1회 눌렸는가?
			if( 1== m_dBtnCnt[curIdx])
			{
				//	경과 시간이 지났는가?
				if( (dBtnCur - m_dBtnBgn[curIdx]) >= m_dTimeDC)
					//	카운트 초기화.
					m_dBtnCnt[curIdx] = 0;
			}
			//	2회 눌렸는가?
			else if( 2 == m_dBtnCnt[curIdx])
			{
				//	경과시간이 지나지 않았는가?
				if( (dBtnCur- m_dBtnBgn[curIdx]) <= m_dTimeDC)
					//	더블 클릭으로 처리.
					m_mouseBtttnMap[curIdx] = DBLCLK;

				//	카운트 초기화.
				m_dBtnCnt[curIdx] =0;
			}

		}//	if(UP == m_mouseBtttnMap[curIdx])

	}//	for(curIdx = 0; curIdx < MAX_INPUT_BTN; ++curIdx)

	return 0;

}//	INT CInputManager::FrameMove()	// Mouse
//------------------------------------
LRESULT CInputManager::MsgProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch( msg )
	{
		//	#define _WIN32_WINNT 0x0400 처리 필요.
		case WM_MOUSEWHEEL:
		{
			INT wheelOffset = HIWORD(wParam);			

			wheelOffset = short(wheelOffset);
			m_vcCur.z += FLOAT(wheelOffset);
			break;

		}//	case WM_MOUSEWHEEL:

	}//	switch( msg )

	return 0;

}//	LRESULT CInputManager::MsgProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
//------------------------------------