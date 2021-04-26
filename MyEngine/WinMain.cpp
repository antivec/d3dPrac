//================================================
#include "Global.h"
//================================================
CMyGame*	g_pMyGame;
//================================================
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
	CMyGame	myGAme;

	g_pMyGame = &myGAme;

	if (FAILED(myGAme.Create(hInst)))
		return -1;

	return myGAme.Run();
}