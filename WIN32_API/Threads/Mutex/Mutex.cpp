/*
;|**********************************************************************;
;* Project           : CPP-Language_practise
;*
;* Program name      : Mutex.cpp
;*
;* Author            : SIO TOU LAI (laisiotou1997@gmail.com)
;*
;* Date created      : 04/12/2019
;*
;* Version           : internal
;*
;* Copyright         : GNU GENERAL PUBLIC LICENSE Version 3
;*
;* Purpose           : Mutex Demo
;*
;* Revision History  :
;* Date        Author      Ref    Revision (Date in DDMMYYYY format)
;* 04122019    lst97       1      First release
;*
;* Known Issue       :
;*
;* TODO              :
;*
;|**********************************************************************;
*/

#include "stdio.h"
#include "windows.h"
//#include "resource.h"
#include "Z:/#temp/Thread/resource.h"

HANDLE g_hMutex = NULL;

class PoolData {
public:
	HWND hwndEditControl = NULL;
	HWND hwndEditControl_Customer1 = NULL;
	HWND hwndEditControl_Customer2 = NULL;
	HWND hwndEditControl_Customer3 = NULL;
	HWND hwndStart = NULL;

	unsigned int numberOfRedEnvelope = 0;
	HANDLE hThreadArray[3] = { 0 };
};

BOOL CALLBACK CallBack_TimerDlg(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam);
void GrabStart(PoolData* pcPoolData);
DWORD WINAPI Thread_GrabRedEnvelope(LPVOID lpParameter);
DWORD WINAPI Thread_Customer1(LPVOID lpParameter);
DWORD WINAPI Thread_Customer2(LPVOID lpParameter);
DWORD WINAPI Thread_Customer3(LPVOID lpParameter);


int APIENTRY WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
) {

	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_TIMER), NULL, CallBack_TimerDlg);

	return 0;
}

BOOL CALLBACK CallBack_TimerDlg(
	_In_ HWND   hwnd,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {

	switch (uMsg) {
	case WM_INITDIALOG: {
		SetWindowText(GetDlgItem(hwnd, IDC_EDIT_TIMER), "0");

		return false;
	}

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTON_START: {
			PoolData* pcPoolData = new PoolData;
			pcPoolData->hwndEditControl = GetDlgItem(hwnd, IDC_EDIT_TIMER);
			pcPoolData->hwndEditControl_Customer1 = GetDlgItem(hwnd, IDC_EDIT_CUSTOMER1);
			pcPoolData->hwndEditControl_Customer2 = GetDlgItem(hwnd, IDC_EDIT_CUSTOMER2);
			pcPoolData->hwndEditControl_Customer3 = GetDlgItem(hwnd, IDC_EDIT_CUSTOMER3);
			GrabStart(pcPoolData);

			return true;		
		}

		default:
			return false;
		}

	case WM_CLOSE:
		EndDialog(hwnd, 0);
		return true;

	default:
		return false;
	}
}

void GrabStart(PoolData* pcPoolData) {
	g_hMutex = CreateMutex(NULL, false, "Pool1");
	char szNumber[8] = { 0 };
	GetWindowText(pcPoolData->hwndEditControl, szNumber, 8);
	sscanf(szNumber, "%d", &pcPoolData->numberOfRedEnvelope);

	// If not create a new thread, the main GUI thread will freeze.
	CreateThread(NULL, 0, Thread_GrabRedEnvelope, (void*)pcPoolData, 0, NULL);
	return;
}

DWORD WINAPI Thread_GrabRedEnvelope(LPVOID lpParameter) {
	PoolData* pcPoolData = (PoolData*)lpParameter;

	pcPoolData->hThreadArray[0] = CreateThread(NULL, 0, Thread_Customer1, (void*)pcPoolData, 0, NULL);
	pcPoolData->hThreadArray[1] = CreateThread(NULL, 0, Thread_Customer2, (void*)pcPoolData, 0, NULL);
	pcPoolData->hThreadArray[2] = CreateThread(NULL, 0, Thread_Customer3, (void*)pcPoolData, 0, NULL);

	WaitForMultipleObjects(3, pcPoolData->hThreadArray, true, INFINITE);
	CloseHandle(pcPoolData->hThreadArray[0]);
	CloseHandle(pcPoolData->hThreadArray[1]);
	CloseHandle(pcPoolData->hThreadArray[2]);

	return 0;
}

DWORD WINAPI Thread_Customer1(LPVOID lpParameter) {
	PoolData* pcPoolData = (PoolData*)lpParameter;
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "Pool1");

	unsigned int cunsomerReadEnvelope = 0;
	char szBuffer[8] = { 0 };

	while (pcPoolData->numberOfRedEnvelope) {
		WaitForSingleObject(hMutex, INFINITE);
		pcPoolData->numberOfRedEnvelope--;
		ReleaseMutex(hMutex);
		sprintf(szBuffer, "%d", pcPoolData->numberOfRedEnvelope);
		SetWindowText(pcPoolData->hwndEditControl, szBuffer);

		cunsomerReadEnvelope++;
		sprintf(szBuffer, "%d", cunsomerReadEnvelope);
		SetWindowText(pcPoolData->hwndEditControl_Customer1, szBuffer);

		Sleep(20);
	}
	
	return 0;
}

DWORD WINAPI Thread_Customer2(LPVOID lpParameter) {
	PoolData* pcPoolData = (PoolData*)lpParameter;
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "Pool1");

	unsigned int cunsomerReadEnvelope = 0;
	char szBuffer[8] = { 0 };

	while (pcPoolData->numberOfRedEnvelope) {
		WaitForSingleObject(hMutex, INFINITE);
		pcPoolData->numberOfRedEnvelope--;
		ReleaseMutex(hMutex);
		sprintf(szBuffer, "%d", pcPoolData->numberOfRedEnvelope);
		SetWindowText(pcPoolData->hwndEditControl, szBuffer);

		cunsomerReadEnvelope++;
		sprintf(szBuffer, "%d", cunsomerReadEnvelope);
		SetWindowText(pcPoolData->hwndEditControl_Customer2, szBuffer);

		Sleep(20);
	}

	return 0;
}

DWORD WINAPI Thread_Customer3(LPVOID lpParameter) {
	PoolData* pcPoolData = (PoolData*)lpParameter;
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "Pool1");

	unsigned int cunsomerReadEnvelope = 0;
	char szBuffer[8] = { 0 };

	while (pcPoolData->numberOfRedEnvelope) {
		WaitForSingleObject(hMutex, INFINITE);
		pcPoolData->numberOfRedEnvelope--;
		ReleaseMutex(hMutex);
		sprintf(szBuffer, "%d", pcPoolData->numberOfRedEnvelope);
		SetWindowText(pcPoolData->hwndEditControl, szBuffer);

		cunsomerReadEnvelope++;
		sprintf(szBuffer, "%d", cunsomerReadEnvelope);
		SetWindowText(pcPoolData->hwndEditControl_Customer3, szBuffer);

		Sleep(20);
	}

	return 0;
}
