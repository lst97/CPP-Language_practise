#include "stdio.h"
#include "windows.h"
#include "resource.h"

class TimerData {
public:
	HWND hwndEditControl = NULL;
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
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTON_START: {
			char szBuffer[16] = { 0 };
			HWND hwndEditControl = GetDlgItem(hwnd, IDC_EDIT_TIMER);

			GetWindowText(hwndEditControl, szBuffer, 16);
			TimerData* pcTimerData = new TimerData();
			pcTimerData->hwndEditControl = hwndEditControl;
			sscanf(szBuffer, "%d", &(pcTimerData->timeValue));
			// memory leak.
			Timer(pcTimerData);
			return true;
		}
		default:
			return false;
		}
	default:
		return false;
	}
}

void Timer(TimerData* pcTimerData) {
	HANDLE hThreadHandle = CreateThread(NULL, 0, Thread_TimerThread, (void*)pcTimerData, 0, NULL);
	pcTimerData->hTimerThread = hThreadHandle;
}


DWORD WINAPI Thread_TimerThread(LPVOID lpParameter) {
	TimerData* pcTimerData = (TimerData*)lpParameter;
	if (pcTimerData->timeValue <= 0)
		return 0;

	char szBuffer[16];

	do {
		sprintf(szBuffer, "%d", --(pcTimerData->timeValue));
		SetWindowText(pcTimerData->hwndEditControl, szBuffer);
		Sleep(1000);
	} while (pcTimerData->timeValue != 0);

	CloseHandle(pcTimerData->hTimerThread);
	free(pcTimerData);
	return 0;
}
