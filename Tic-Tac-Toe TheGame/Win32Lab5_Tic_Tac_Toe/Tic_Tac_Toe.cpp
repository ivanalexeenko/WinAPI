#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#include <windows.h>
#include "resource.h"
using namespace std;
LRESULT CALLBACK WndProc(HWND, UINT,WPARAM, LPARAM);
BOOL CALLBACK About(HWND, UINT,WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,PSTR szCmdLine,int iCmdShow)
{
	DialogBox(hInstance, "IDD_DIALOG", 0, About);
	return 0;
}
BOOL CALLBACK About(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static char buf[20];
	switch (iMsg) {
	case WM_INITDIALOG:
		SetFocus(GetDlgItem(hDlg, IDC_EDIT));
		return TRUE;
	case WM_COMMAND: 
		switch (LOWORD(wParam)) 
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		case IDC_BUTTON:
			GetDlgItemText(hDlg, IDC_EDIT, buf, 20);
			SendMessage(GetDlgItem(hDlg, IDC_LIST), LB_ADDSTRING, 0, (LPARAM)buf);
			SetWindowText(GetDlgItem(hDlg, IDC_EDIT), "");
			SetFocus(GetDlgItem(hDlg, IDC_EDIT));
			return TRUE;
		}
		break;
	}
	return FALSE;
}