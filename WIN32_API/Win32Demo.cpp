/*
;|**********************************************************************;
;* Project           : CPP-Language_practise
;*
;* Program name      : Win32Demo.cpp
;*
;* Author            : SIO TOU LAI (laisiotou1997@gmail.com)
;*
;* Date created      : 02/11/2019
;*
;* Version           : internal
;*
;* Copyright         : GNU GENERAL PUBLIC LICENSE Version 3
;*
;* Purpose           : Windows API demo
;*
;* Revision History  :
;* Date        Author      Ref    Revision (Date in DDMMYYYY format)
;* 02112019    lst97       1      First release
;*
;* Known Issue       :
;*
;* TODO              :
;*
;|**********************************************************************;
*/

#include "Header.h"

// Declear
void CreateButton(HWND hwnd);
LRESULT CALLBACK fnMainMsgHandler(IN HWND hwnd, IN UINT uMsg, IN WPARAM wParam, IN LPARAM lParam);
BOOL CALLBACK CallBack_LoginDialog(IN HWND hDlg, IN UINT uMsg, IN WPARAM wParam, IN LPARAM lParam);

// Groble
char debugStringBuffer[4096] = { 0 };
HINSTANCE hImageBase = 0;

// Code
int APIENTRY WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	hImageBase = hInstance;

	char szClassName[] = { "MainWindows" };
	WNDCLASS wndClass = { 0 };
	wndClass.hbrBackground = (HBRUSH)COLOR_MENU;
	wndClass.lpfnWndProc = fnMainMsgHandler;
	wndClass.lpszClassName = szClassName;
	wndClass.hInstance = hInstance;

	RegisterClass(&wndClass);

	HWND hwnd = CreateWindow(
		szClassName,
		"Main Windows",
		WS_OVERLAPPEDWINDOW,
		16, 16,
		600, 400,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!hwnd)
		return 0;

	CreateButton(hwnd);

	ShowWindow(hwnd, SW_SHOW);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);	// Translates virtual-key messages into character messages
		DispatchMessage(&msg);	// To Callback function
	}

	return 0; 
}

LRESULT CALLBACK fnMainMsgHandler(
	IN HWND hwnd,
	IN UINT uMsg,
	IN WPARAM wParam,
	IN LPARAM lParam
) {
	LPCSTR VirtualKey = 0;
	switch (uMsg) {
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case 1001:
			DialogBox(hImageBase, MAKEINTRESOURCE(IDD_DIALOG_LOGIN), hwnd, CallBack_LoginDialog);
			return 0;
		}

	case WM_LBUTTONDOWN:
		return 0;
	case WM_KEYDOWN:
		VirtualKey = (LPCSTR)&wParam;
		sprintf(debugStringBuffer, "%d\n", (int)*VirtualKey);
		OutputDebugString(debugStringBuffer);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);

}

void CreateButton(HWND hwnd) {
	HWND hwndPushButton;
	HWND hwndCheckBox;
	HWND hwndRadio;

	hwndPushButton = CreateWindow(
		"button",
		"stdButton",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_DEFPUSHBUTTON,
		16, 16,
		80, 20,
		hwnd,
		(HMENU)1001,
		hImageBase,
		NULL
	);

	// GetClassInfo
	TCHAR szBuffer[0x20];
	TCHAR szDebugStringBuffer[4096];
	GetClassName(hwndPushButton, szBuffer, 0x20);
	WNDCLASS wndClass;
	GetClassInfo(hImageBase, szBuffer, &wndClass);
	sprintf(szDebugStringBuffer, "%s\n%X\n", wndClass.lpszClassName, (unsigned int)wndClass.lpfnWndProc);
	OutputDebugString(szDebugStringBuffer);

	hwndCheckBox = CreateWindow(
		"button",
		"stdCheckBox",
		WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_DEFPUSHBUTTON,
		16, 64,
		80, 20,
		hwnd,
		(HMENU)1002,
		hImageBase,
		NULL
	);

	hwndRadio = CreateWindow(
		"button",
		"stdRadioButton",
		WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
		16, 128,
		80, 20,
		hwnd,
		(HMENU)1003,
		hImageBase,
		NULL
	);
}

BOOL CALLBACK CallBack_LoginDialog(
	IN HWND hDlg,
	IN UINT uMsg,
	IN WPARAM wParam,
	IN LPARAM lParam
) {
	switch (uMsg) {
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTON_OK: {
			char szBuffer_IDC_EDIT_NAME[32] = { 0 };
			char szBuffer_IDC_EDIT_PASSWORD[32] = { 0 };
			HWND h_IDC_EDIT_NAME = GetDlgItem(hDlg, IDC_EDIT_NAME);
			HWND h_IDC_EDIT_PASSWORD = GetDlgItem(hDlg, IDC_EDIT_PASSWORD);

			GetWindowText(h_IDC_EDIT_NAME, szBuffer_IDC_EDIT_NAME, 32);
			GetWindowText(h_IDC_EDIT_PASSWORD, szBuffer_IDC_EDIT_PASSWORD, 32);

			// validate
			if (!strcmp(szBuffer_IDC_EDIT_NAME, "lst97") && !strcmp(szBuffer_IDC_EDIT_PASSWORD, "1234")) {
				sprintf(debugStringBuffer, "SUCCESS!\n");
				OutputDebugString(debugStringBuffer);
			}
			return TRUE;
		}
			
		case IDC_BUTTON_CANCEL:
			EndDialog(hDlg, 0);
			return true;
		}
	}
	return FALSE;
}

//int main(int argc, char *argv[]) {
//
//
//	return 0;
//}
