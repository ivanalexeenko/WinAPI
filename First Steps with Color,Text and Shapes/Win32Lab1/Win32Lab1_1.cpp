#undef UNICODE
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
HWND hWnd;
int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int) {
	MessageBox(NULL, " Word up,bro! =)", "Hello Program", MB_YESNO);
	int a=2326;
	TCHAR buffer[10];
	sprintf(buffer, TEXT("%d"), a);
	MessageBox(NULL, buffer, TEXT("Number output"), MB_OK);
	

}