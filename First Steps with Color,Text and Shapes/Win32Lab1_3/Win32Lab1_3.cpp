#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#include<windows.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
LPCSTR szClassName = "WinAPI";
LPCSTR szTitle = "Создание окна Windows";
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	if (!hPrevInstance)
	{  
		if (!InitApplication(hInstance))
			return (FALSE);
	}
	if (!InitInstance(hInstance, nCmdShow))
		return (FALSE);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}
	return (msg.wParam);
}
	BOOL InitApplication(HINSTANCE hInstance)
	{
		WNDCLASS  wc;
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = (WNDPROC)WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(NULL, IDI_ASTERISK);
		wc.hCursor = LoadCursor(NULL, IDC_CROSS);
		wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE - 1);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = szClassName;
		return RegisterClass(&wc);
	}
	BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
	{
		HWND hWnd;
		hWnd = CreateWindow(
			szClassName,         
			szTitle,             
			WS_OVERLAPPEDWINDOW, 
			CW_USEDEFAULT,       
			CW_USEDEFAULT,       
			CW_USEDEFAULT,       
			CW_USEDEFAULT,       
			NULL,                
			NULL,                
			hInstance,          
			NULL);              

		if (!hWnd)    return (FALSE);
		ShowWindow(hWnd, SW_MAXIMIZE);
		UpdateWindow(hWnd);
		return (TRUE);
	}
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		HDC hdc;
		PAINTSTRUCT ps;
		static RECT Rect;
		switch (message)
		{
		case WM_PAINT:
			GetClientRect(hWnd, &Rect);
			hdc = BeginPaint(hWnd, &ps);
			DrawText(hdc, "Top Left Corner", strlen("Top Left Corner"), &Rect, (DT_SINGLELINE|DT_LEFT|DT_TOP));
			DrawText(hdc, "Bottom Left Corner", strlen("Bottom Left Corner"), &Rect,(DT_SINGLELINE|DT_BOTTOM|DT_LEFT));
			DrawText(hdc, "Top Right Corner", strlen("Top Right Corner"), &Rect, (DT_SINGLELINE|DT_TOP | DT_RIGHT));
			DrawText(hdc, "Bottom Right Corner", strlen("Bottom Right Corner"), &Rect, (DT_SINGLELINE|DT_BOTTOM | DT_RIGHT));
			TextOut(hdc,(Rect.left+Rect.right)/2-20, (Rect.bottom + Rect.top) / 2,"Center",strlen("Center"));
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;
	}