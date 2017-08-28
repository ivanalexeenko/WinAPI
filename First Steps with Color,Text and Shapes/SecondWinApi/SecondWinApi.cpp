#include <windows.h>
//typedef struct {
//	UINT style;			// Window style;
//	WNDPROC lpfnWndProc;// Window procedure pointer;
//	int cbClsExtra;		// Additional bytes after class,always pick up 0;
//	int cbWndExtra;		// Additional bytes after window sample,always pick up 0;
//	HINSTANCE hInstance;// Application sample.Transmitted like WinMain parameter;
//	HICON hIcon;		// Icon style;
//	HCURSOR hCursor;	// Application cursor;
//	HBRUSH hbrBackGround;// Background color;
//	LPCTSTR lpszMenuName;// Menu name;
//	LPCTSTR lpszClassName;// Class name;
//} WNDCLASS, *PWNDCLASS;
//
//
//
//int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR szCmdLine,int iCmdShow) {
//	HWND CreateWindow{
//		LPCTSTR lpClassName,	// Class name;
//		LPCTSTR lpWindowName,	// Window name;
//		DWORD dwStyle,			// Window style;
//		int x,					// x coordinate;
//		int y,					// y coordinate;
//		int nWidth,				// Window width;
//		int nHeight,			// Window hight;
//		HWND hWndParent,		// Parent window;
//		HMENU hMenu,			// Menu describer;
//		HINSTANCE hInstance,	// Application sample;
//		LPVOID lpParam			// Parametr, always pick up NULL;
//
//	};
//
//	return NULL;
//}
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow) {
//	HWND Wind = CreateWindow("FirstOkWinApi","Just a window",0,400,400,400,400,0,0,hInstance,0);
//
//
//	return ;
//}