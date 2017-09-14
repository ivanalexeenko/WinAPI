#include "stdafx.h"
#include "kHashTableWinApi.h"
#include "kHashTable.h"
#define MAX_LOADSTRING 100

// Global Variables:
int size_1 = 10;
int size_2 = 21;
kHashTable Table_ONE(size_1);
kHashTable Table_TWO(size_2);

string ReadText(LPARAM lParam)
{
	int length = SendMessage((HWND)lParam, WM_GETTEXTLENGTH, 0, 0);
	char *buffer = new char[length];
	SendMessage((HWND)lParam, WM_GETTEXT, (WPARAM)(length + 1), (LPARAM)buffer);
	string temp_num_str(buffer);
	return temp_num_str;
}
int FromStrToInt(string& value_1 )
{
	int val_1 = 0;
	int deg = value_1.length() - 1;
	for (auto i : value_1)
	{
		val_1 += ((i - '0') * pow(10, deg));
		deg--;
	}
	return val_1;
}

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
	static int FontSize = 20;
	static HDC hdc;
	static POINT Center;
	static RECT Rect;
	static HBRUSH BG;
	static HBITMAP BG_BIT;
	static HFONT hFont;
	
    switch (message)
    {
	case WM_CREATE:
	{
		string s = "Check my HashTable realisation out =)";
		SetWindowTextW(hWnd, (LPCWSTR)s.c_str());
		
		hFont = CreateFont(FontSize, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Snap ITC"));
		BG_BIT = LoadBitmap((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDB_CHALK));
		BG = CreatePatternBrush(BG_BIT);
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
            PAINTSTRUCT ps;
            hdc = BeginPaint(hWnd, &ps);
			SetBkMode(hdc, TRANSPARENT);
			SelectObject(hdc, hFont);
			SetTextColor(hdc,RGB(255,255,255));
			TextOut(hdc, Center.x / 3, 0, (LPCSTR)"kHashTable_1", strlen("kHashTable_1"));
			TextOut(hdc, Center.x / 0.7, 0, (LPCSTR)"kHashTable_2", strlen("kHashTable_2"));
			int format = Center.y / 10;
			int index = 0;
			for (kHashTable::Iterator i = Table_ONE.Begin(); i != Table_ONE.End(); i++)
			{
				string str = "[" + to_string(index++) + "]" + "  Key : " + (i->first) + "  Value : " + to_string(i->second);
				TextOut(hdc, Center.x / 6, format += 20,str.c_str(), strlen(str.c_str()));
			}
			index = 0;
			format = Center.y / 10;
			for (kHashTable::Iterator i = Table_TWO.Begin(); i != Table_TWO.End(); i++)
			{
				string str = "[" + to_string(index++) + "]" + "  Key : " + (i->first) + "  Value : " + to_string(i->second);
				TextOut(hdc, Center.x / 0.8, format += 20, str.c_str(), strlen(str.c_str()));
			}

            EndPaint(hWnd, &ps);
			
        }
        break;
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
			Table_ONE = Table_TWO;

			break;
		}
		case IDC_SWAP:
		{
			Swap(Table_ONE, Table_TWO);
			break;
		}
		case IDC_KEY_1:
		{
			switch (HIWORD(wParam))
			{
			case EN_KILLFOCUS:
			{

				key_1 = ReadText(lParam);
				break;
			}

			}
			break;
		}
		case IDC_VALUE_1:
		{
			switch (HIWORD(wParam))
			{
			case EN_KILLFOCUS:
			{

				value_1 = ReadText(lParam);
				break;
			}

			}
			break;
		}
		case IDC_KEY_2:
		{
			switch (HIWORD(wParam))
			{
			case EN_KILLFOCUS:
			{
				key_2 = ReadText(lParam);
				break;
			}

			}
			break;
		}
		case IDC_VALUE_2:
		{
			switch (HIWORD(wParam))
			{
			case EN_KILLFOCUS:
			{
				value_2 = ReadText(lParam);
				break;
			}

			}
			break;
		}
		case ID_EMPLACE_1:
		{
			if (key_1.length() != 0 && value_1.length() != 0)
			{

				Table_ONE.Emplace(key_1, FromStrToInt(value_1));
			}

			break;
		}
		case ID_EMPLACE_2:
		{
			if (key_2.length() != 0 && value_2.length() != 0)
			{
				Table_TWO.Emplace(key_2, FromStrToInt(value_2));
			}

			break;
		}
		case IDC_DEL_K_1:
		{
			switch (HIWORD(wParam))
			{
			case EN_KILLFOCUS:
			{
				del_key_1 = ReadText(lParam);
				break;
			}

			}
			break;
		}
		case IDC_DEL_K_2:
		{
			switch (HIWORD(wParam))
			{
			case EN_KILLFOCUS:
			{
				del_key_2 = ReadText(lParam);
				break;
			}

			}
		}
		case IDC_DELETE_1:
		{
			if (del_key_1.length() != 0)
			{
				Table_ONE.Delete(del_key_1);
			}
			break;
		}
		case IDC_DELETE_2:
		{
			if (del_key_2.length() != 0)
			{
				Table_TWO.Delete(del_key_2);
			}
			break;
		}
		case IDC_CLEAR_1:
		{
			Table_ONE.Clear();
			break;
		}
		case IDC_CLEAR_2:
		{
			Table_TWO.Clear();
			break;
		}
		case IDC_FINITA:
		{
			string buf;
			bool result = Table_ONE.IsEmpty();
			if (result == true)
			{
				buf = "true";
			}
			else buf = "false";
			SendMessage(GetDlgItem(hTab, IDC_EMPTY_1), WM_SETTEXT, 0, (LPARAM)((buf).c_str()));

			result = Table_ONE.IsFull();
			if (result == true)
			{
				buf = "true";
			}
			else buf = "false";
			SendMessage(GetDlgItem(hTab, IDC_FULL_1), WM_SETTEXT, 0, (LPARAM)((buf).c_str()));

			SendMessage(GetDlgItem(hTab, IDC_SIZE_1), WM_SETTEXT, 0, (LPARAM)to_string(Table_ONE.Size()).c_str());

			result = Table_TWO.IsEmpty();

			if (result == true)
			{
				buf = "true";
			}
			else buf = "false";

			
			SendMessage(GetDlgItem(hTab, IDC_EMPTY_2), WM_SETTEXT, 0, (LPARAM)((buf).c_str()));

			result = Table_TWO.IsFull();
			if (result == true)
			{
				buf = "true";
			}
			else buf = "false";

			SendMessage(GetDlgItem(hTab, IDC_FULL_2), WM_SETTEXT, 0, (LPARAM)((buf).c_str()));

			SendMessage(GetDlgItem(hTab, IDC_SIZE_2), WM_SETTEXT, 0, (LPARAM)to_string(Table_TWO.Size()).c_str());




			break;

		}
		}
		break;
	}
	}
	return (INT_PTR)FALSE;
}