/*
;|**********************************************************************;
;* Project           : CPP-Language_practise
;*
;* Program name      : SimpleTimer.cpp
;*
;* Author            : SIO TOU LAI (laisiotou1997@gmail.com)
;*
;* Date created      : 03/12/2019
;*
;* Version           : internal
;*
;* Copyright         : GNU GENERAL PUBLIC LICENSE Version 3
;*
;* Purpose           : Create, Resume, Pause, Stop thread demo
;*
;* Revision History  :
;* Date        Author      Ref    Revision (Date in DDMMYYYY format)
;* 03122019    lst97       1      First release
;*
;* Known Issue       :
;*
;* TODO              :
;* 1. Can make the code less redundancy. 
;*
;|**********************************************************************;
*/

#include "stdio.h"
#include "windows.h"
//#include "resource.h"
#include "Z:/#temp/Thread/resource.h"

HANDLE g_hExistThread = NULL;

class TimerData {
public:
	HWND hwndEditControl = NULL;
	HWND hwndStart = NULL;
	HWND hwndPause = NULL;
	HWND hwndResume = NULL;
	HWND hwndStop = NULL;

	unsigned int timeValue = 0;
	HANDLE hTimerThread = 0;
};

BOOL CALLBACK CallBack_TimerDlg(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam);
void Timer(TimerData* pcTimerData);
DWORD WINAPI Thread_TimerThread(LPVOID lpParameter);


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
		HWND hwndEditControl = GetDlgItem(hwnd, IDC_EDIT_TIMER);
		HWND hwndStart = GetDlgItem(hwnd, IDC_BUTTON_START);
		HWND hwndPause = GetDlgItem(hwnd, IDC_BUTTON_PAUSE);
		HWND hwndResume = GetDlgItem(hwnd, IDC_BUTTON_RESUME);
		HWND hwndStop = GetDlgItem(hwnd, IDC_BUTTON_STOP);

		EnableWindow(hwndPause, false);
		EnableWindow(hwndResume, false);
		EnableWindow(hwndStop, false);

		SetWindowText(hwndEditControl, "0");
		return false;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTON_START: {
			HWND hwndStart = GetDlgItem(hwnd, IDC_BUTTON_START);
			EnableWindow(hwndStart, false);

			char szBuffer[16] = { 0 };
			HWND hwndEditControl = GetDlgItem(hwnd, IDC_EDIT_TIMER);

			HWND hwndPause = GetDlgItem(hwnd, IDC_BUTTON_PAUSE);
			HWND hwndResume = GetDlgItem(hwnd, IDC_BUTTON_RESUME);
			HWND hwndStop = GetDlgItem(hwnd, IDC_BUTTON_STOP);
			EnableWindow(hwndPause, true);
			EnableWindow(hwndResume, false);
			EnableWindow(hwndStop, true);

			GetWindowText(hwndEditControl, szBuffer, 16);
			TimerData* pcTimerData = new TimerData();
			pcTimerData->hwndEditControl = hwndEditControl;
			pcTimerData->hwndStart = hwndStart;
			pcTimerData->hwndPause = hwndPause;
			pcTimerData->hwndResume = hwndResume;
			pcTimerData->hwndStop = hwndStop;

			sscanf(szBuffer, "%d", &(pcTimerData->timeValue));
			Timer(pcTimerData);
			return true;		
		}
		case IDC_BUTTON_PAUSE:
			if (g_hExistThread) {
				SuspendThread(g_hExistThread);
				HWND hwndResume = GetDlgItem(hwnd, IDC_BUTTON_RESUME);
				HWND hwndPause = GetDlgItem(hwnd, IDC_BUTTON_PAUSE);
				EnableWindow(hwndPause, false);
				EnableWindow(hwndResume, true);
			}
			return true;

		case IDC_BUTTON_RESUME: {
			if (g_hExistThread) {
				ResumeThread(g_hExistThread);
				HWND hwndResume = GetDlgItem(hwnd, IDC_BUTTON_RESUME);
				HWND hwndPause = GetDlgItem(hwnd, IDC_BUTTON_PAUSE);
				EnableWindow(hwndPause, true);
				EnableWindow(hwndResume, false);
			}
			return true;
		}

		case IDC_BUTTON_STOP:
			if (g_hExistThread) {
				// ExitThread(0);

				TerminateThread(g_hExistThread, 0);
				WaitForSingleObject(g_hExistThread, INFINITE);

				HWND hwndEditControl = GetDlgItem(hwnd, IDC_EDIT_TIMER);
				SetWindowText(hwndEditControl, "0");
				HWND hwndStart = GetDlgItem(hwnd, IDC_BUTTON_START);
				HWND hwndPause = GetDlgItem(hwnd, IDC_BUTTON_PAUSE);
				HWND hwndResume = GetDlgItem(hwnd, IDC_BUTTON_RESUME);
				HWND hwndStop = GetDlgItem(hwnd, IDC_BUTTON_STOP);

				EnableWindow(hwndStart, true);
				EnableWindow(hwndPause, false);
				EnableWindow(hwndResume, false);
				EnableWindow(hwndStop, false);
			}
			return true;

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

void Timer(TimerData* pcTimerData) {
	HANDLE hThreadHandle = CreateThread(NULL, 0, Thread_TimerThread, (void*)pcTimerData, 0, NULL);
	g_hExistThread = hThreadHandle;

	pcTimerData->hTimerThread = hThreadHandle;
}


DWORD WINAPI Thread_TimerThread(LPVOID lpParameter) {
	TimerData* pcTimerData = (TimerData*)lpParameter;
	if (pcTimerData->timeValue <= 0) {
		EnableWindow(pcTimerData->hwndStart, true);
		EnableWindow(pcTimerData->hwndPause, false);
		EnableWindow(pcTimerData->hwndResume, false);
		EnableWindow(pcTimerData->hwndStop, false);
		return 0;
	}


	char szBuffer[16];

	do {
		sprintf(szBuffer, "%d", --(pcTimerData->timeValue));
		SetWindowText(pcTimerData->hwndEditControl, szBuffer);
		Sleep(1000);
	} while (pcTimerData->timeValue != 0);

	CloseHandle(pcTimerData->hTimerThread);
	EnableWindow(pcTimerData->hwndStart, true);
	EnableWindow(pcTimerData->hwndPause, false);
	EnableWindow(pcTimerData->hwndResume, false);
	EnableWindow(pcTimerData->hwndStop, false);
	free(pcTimerData);
	return 0;
}
