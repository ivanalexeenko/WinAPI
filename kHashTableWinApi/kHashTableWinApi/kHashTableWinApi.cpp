#include "stdafx.h"
#include "kHashTableWinApi.h"
#include "kHashTable.h"
#include "Controller.h"
#define MAX_LOADSTRING 100

// Global Variables:
int size_1 = 10;
int size_2 = 21;
kHashTable Table_ONE(size_1);
kHashTable Table_TWO(size_2);


HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    HashTable(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE,szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_KHASHTABLEWINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KHASHTABLEWINAPI));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KHASHTABLEWINAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_KHASHTABLEWINAPI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static string s = "Check my HashTable realisation out =)";
	static int FontSize = 20;
	static HDC hdc;
	static POINT Center;
	static RECT Rect;
	static HBITMAP BG_BIT = LoadBitmap((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDB_CHALK));
	static HBRUSH BG = CreatePatternBrush(BG_BIT);
	static HFONT hFont = CreateFont(FontSize, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Snap ITC"));
	static View view;
	switch (message)
	{
	case WM_CREATE:
	{
		SetWindowTextW(hWnd, (LPCWSTR)s.c_str());
		SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)BG);
		GetClientRect(hWnd, &Rect);
		Center.x = (Rect.right - Rect.left) / 2;
		Center.y = (Rect.bottom - Rect.top) / 2;
		break;
	}

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case ID_CHECKTHISOUT_MYHASHTABLE:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_TABLE), hWnd, HashTable);
			InvalidateRect(hWnd, &Rect, TRUE);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		View v(Table_ONE, Table_TWO, hdc, hWnd, hFont, Center);
		view = v;
		view.update();
		break;
	}
	
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK HashTable(HWND hTab, UINT message, WPARAM wParam, LPARAM lParam)
{
	static string key_1, key_2, value_1, value_2;
	static string del_key_1, del_key_2;
	static Controller control;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		key_1.clear();
		key_2.clear();
		value_1.clear();
		value_2.clear();

		del_key_1.clear();
		del_key_2.clear();

		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hTab, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		switch (LOWORD(wParam))
		{
		case IDC_EQUAL:
		{
			control.equalize(Table_ONE, Table_TWO);
			break;
		}
		case IDC_SWAP:
		{
			control.swap(Table_ONE, Table_TWO);
			break;
		}
		case IDC_KEY_1:
		{
			control.read_str(lParam, wParam, key_1);
			break;
		}
		case IDC_VALUE_1:
		{
			control.read_str(lParam,wParam,value_1);
			break;
		}
		case IDC_KEY_2:
		{
			control.read_str(lParam, wParam, key_2);
			break;
		}
		case IDC_VALUE_2:
		{
			control.read_str(lParam, wParam, value_2);
			break;
		}
		case ID_EMPLACE_1:
		{
			control.emplace(Table_ONE, key_1, value_1);
			break;
		}
		case ID_EMPLACE_2:
		{
			control.emplace(Table_TWO, key_2, value_2);
			break;
		}
		case IDC_DEL_K_1:
		{
			control.read_str(lParam, wParam, del_key_1);
			break;
		}
		case IDC_DEL_K_2:
		{
			control.read_str(lParam, wParam, del_key_2);
			break;
		}
		case IDC_DELETE_1:
		{
			control.delete_elem(Table_ONE, del_key_1);
			break;
		}
		case IDC_DELETE_2:
		{
			control.delete_elem(Table_TWO, del_key_2);
			break;
		}
		case IDC_CLEAR_1:
		{
			control.clear(Table_ONE);
			break;
		}
		case IDC_CLEAR_2:
		{
			control.clear(Table_TWO);
			break;
		}
		case IDC_FINITA:
		{
			
			string result = control.is_empty(Table_ONE);

			SendMessage(GetDlgItem(hTab, IDC_EMPTY_1), WM_SETTEXT, 0, (LPARAM)((result).c_str()));

			result = control.is_full(Table_ONE);

			SendMessage(GetDlgItem(hTab, IDC_FULL_1), WM_SETTEXT, 0, (LPARAM)((result).c_str()));

			result = control.size(Table_ONE);

			SendMessage(GetDlgItem(hTab, IDC_SIZE_1), WM_SETTEXT, 0, (LPARAM)(result).c_str());

			result = control.is_empty(Table_TWO);

			SendMessage(GetDlgItem(hTab, IDC_EMPTY_2), WM_SETTEXT, 0, (LPARAM)((result).c_str()));

			result = control.is_full(Table_TWO);

			SendMessage(GetDlgItem(hTab, IDC_FULL_2), WM_SETTEXT, 0, (LPARAM)((result).c_str()));

			result = control.size(Table_TWO);

			SendMessage(GetDlgItem(hTab, IDC_SIZE_2), WM_SETTEXT, 0, (LPARAM)(result).c_str());




			break;

		}
		}
		break;
	}
	}
	return (INT_PTR)FALSE;
}
