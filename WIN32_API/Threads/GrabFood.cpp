/*
;|**********************************************************************;
;* Project           : CPP-Language_practise
;*
;* Program name      : GrabFood.cpp
;*
;* Author            : SIO TOU LAI (laisiotou1997@gmail.com)
;*
;* Date created      : 03/12/2019
;*
;* Version           : internal
;*
;* Copyright         : GNU GENERAL PUBLIC LICENSE Version 3
;*
;* Purpose           : Simluate customer grab food using Semaphore and Event.
;*
;* Revision History  :
;* Date        Author      Ref    Revision (Date in DDMMYYYY format)
;* 07122019    lst97       1      First release
;*
;* Known Issue       :
;* 1. Can reduce code size, some code are identical just a bit different like case 0, case1
;* 2. Customer thread hardly focus on waiting table 1, can make it switch between waiting table1 & waiting table2;
;* 3. Only run one time.
;*
;* TODO              :
;*
;|**********************************************************************;
*/

#include "stdio.h"
#include "windows.h"
#include "resource.h"
#include "time.h"

BOOL CALLBACK CallBack_GrabFoodDlg(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam);

DWORD WINAPI Thread_GrabFood(LPVOID lpParameter);
DWORD WINAPI Thread_Chef(LPVOID lpParameter);
DWORD WINAPI Thread_Customer(LPVOID lpParameter);

unsigned int trimDish(_In_ char* dishNameBuffer, _Out_ char szDishhName[16][16]);
void popWaitingItem(unsigned int waitingIndex, char* szBuffer);

class FoodStatus {
private:
	// 1. Save handle to class please
	HANDLE Thread_hGrabFood = NULL;
	HANDLE Thread_hChef = NULL;
	HANDLE Thread_hCustomerArr[4] = { 0 };

public:
	char waiting1Item[8][16] = { 0 };
	char waiting2Item[8][16] = { 0 };

	//unsigned int timeToMake[16] = { 0 };
	//unsigned int timeToEat[4][16] = { 0 };

	unsigned int waiting1TotalItem = 0;
	unsigned int waiting2TotalItem = 0;

	bool isFinishCook = false;

	void CloseAllHandle() {
		CloseHandle(Thread_hGrabFood);
		CloseHandle(Thread_hChef);
		for (unsigned int i = 0; i < 4; i++) {
			CloseHandle(Thread_hCustomerArr[i]);
		}

		return;
	}

	// setter
	void setGrabFoodHandle(HANDLE Thread_hGrabFood) {
		this->Thread_hGrabFood = Thread_hGrabFood;
	}
	void setChefHandle(HANDLE Thread_hChef) {
		this->Thread_hChef = Thread_hChef;
	}
	void setCustomerThreadArray(HANDLE Thread_hCustomerArr[4]) {
		for (int i = 0; i < 4; i++) {
			this->Thread_hCustomerArr[i] = Thread_hCustomerArr[i];
		}
	}

	// getter
	HANDLE getGrabFoodHandle() {
		return this->Thread_hGrabFood;
	}
	HANDLE getChefHandle() {
		return this->Thread_hChef;
	}
	HANDLE* getCustomerThreadArray() {
		return Thread_hCustomerArr;
	}
};

class DlgItemHwnd{
public:
	HWND hwndEdit_Orders = NULL;
	HWND hwndEdit_Waiting1 = NULL;
	HWND hwndEdit_Waiting2 = NULL;
	HWND hwndEdit_Customer1 = NULL;
	HWND hwndEdit_Customer2 = NULL;
	HWND hwndEdit_Customer3 = NULL;
	HWND hwndEdit_Customer4 = NULL;
};

HANDLE g_hSemaphore = NULL;
HANDLE g_hEvent_Waiting[2] = { 0 };
DlgItemHwnd* g_pcDlgItemHwnd = NULL;
FoodStatus* g_pcFoodStatus = NULL;

int APIENTRY WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
) {

	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_GRABFOOD), NULL, CallBack_GrabFoodDlg);

	return 0;
}

BOOL CALLBACK CallBack_GrabFoodDlg(
	_In_ HWND   hwnd,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {

	switch (uMsg) {
	case WM_INITDIALOG: {
		g_pcDlgItemHwnd = new DlgItemHwnd;
		for (unsigned int i = 0; i < 7; i++) {
			*((HWND*)g_pcDlgItemHwnd + i) = GetDlgItem(hwnd, IDC_EDIT_ORDERS + i);
		}

		return false;
	}

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTON_START: {
			EnableWindow(GetDlgItem(hwnd, IDC_BUTTON_START), false);
			FoodStatus* g_pcFoodStatus = new FoodStatus;
			g_pcFoodStatus->setGrabFoodHandle(CreateThread(NULL, 0, Thread_GrabFood, (void*)g_pcFoodStatus, 0, NULL));
			return true;
		}
		case IDC_BUTTON_CLOSE:
			EndDialog(hwnd, 0);
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

DWORD WINAPI Thread_GrabFood(LPVOID lpParameter) {
	g_pcFoodStatus = (FoodStatus*)lpParameter;
	g_hSemaphore = CreateSemaphore(NULL, 0, 4, "CustomerSemaphore");

	g_pcFoodStatus->setChefHandle(CreateThread(NULL, 0, Thread_Chef, (void*)g_pcFoodStatus, 0, NULL));
	HANDLE threadTemp[4] = { 0 };

	// create 4 thread execute same code, use 'g_pcFoodStatus' and 'g_hSemaphore' to determent which thread should run.
	for (int i = 0; i < 4; i++) {
		threadTemp[i] = CreateThread(NULL, 0, Thread_Customer, (void*)i, 0, NULL);
	}
	g_pcFoodStatus->setCustomerThreadArray(threadTemp);

	WaitForMultipleObjects(4, g_pcFoodStatus->getCustomerThreadArray(), true, INFINITE);
	g_pcFoodStatus->CloseAllHandle();
	free(g_pcFoodStatus);
	free(g_pcDlgItemHwnd);
	MessageBox(0, "All food cleared!", "Information", MB_ICONINFORMATION | MB_OK);
	return 0;
}

DWORD WINAPI Thread_Chef(LPVOID lpParameter) {
	// manage dishTotal, put food on waiting table;

	char dishNameBuffer[256] = { 0 };
	char szDishName[16][16] = { 0 };
	unsigned int dishTotal = 0;
	unsigned int targetDish = 0;
	GetWindowText(g_pcDlgItemHwnd->hwndEdit_Orders, dishNameBuffer, 256);
	dishTotal = trimDish(dishNameBuffer, szDishName);

	g_hEvent_Waiting[0] = CreateEvent(NULL, false, false, "Waiting1");
	g_hEvent_Waiting[1] = CreateEvent(NULL, false, false, "Waiting2");

	char waiting1Buffer[128] = { 0 };
	char waiting2Buffer[128] = { 0 };
	unsigned int randValue = 0;

	unsigned int waiting1Index = 0;
	unsigned int waiting2Index = 0;

	srand((unsigned int)time(0));
	for (unsigned int i = 0; i < dishTotal; i++) {
		randValue = rand() % 1000;


		if (g_pcFoodStatus->waiting1TotalItem <= g_pcFoodStatus->waiting2TotalItem) {
			GetWindowText(g_pcDlgItemHwnd->hwndEdit_Waiting1, waiting1Buffer, 128);
			if (g_pcFoodStatus->waiting1TotalItem)
				WaitForSingleObject(g_hEvent_Waiting[0], INFINITE);

			if (!waiting1Buffer[0]) {
				memcpy(g_pcFoodStatus->waiting1Item[g_pcFoodStatus->waiting1TotalItem], szDishName[i], 16);
				SetWindowText(g_pcDlgItemHwnd->hwndEdit_Waiting1, g_pcFoodStatus->waiting1Item[g_pcFoodStatus->waiting1TotalItem]);
			}
			else {
				strcat(waiting1Buffer, ", ");
				memcpy(g_pcFoodStatus->waiting1Item[g_pcFoodStatus->waiting1TotalItem], szDishName[i], 16);
				strcat(waiting1Buffer, g_pcFoodStatus->waiting1Item[g_pcFoodStatus->waiting1TotalItem]);
				SetWindowText(g_pcDlgItemHwnd->hwndEdit_Waiting1, waiting1Buffer);
			}

			g_pcFoodStatus->waiting1TotalItem++;
			SetEvent(g_hEvent_Waiting[0]);
			memset(waiting1Buffer, 0, 128);

		} else {
			GetWindowText(g_pcDlgItemHwnd->hwndEdit_Waiting2, waiting2Buffer, 128);
			if(g_pcFoodStatus->waiting2TotalItem)
				WaitForSingleObject(g_hEvent_Waiting[1], INFINITE);

			if (!waiting2Buffer[0]) {
				memcpy(g_pcFoodStatus->waiting2Item[g_pcFoodStatus->waiting2TotalItem], szDishName[i], 16);
				SetWindowText(g_pcDlgItemHwnd->hwndEdit_Waiting2, g_pcFoodStatus->waiting2Item[g_pcFoodStatus->waiting2TotalItem]);
			} else {
				strcat(waiting2Buffer, ", ");
				memcpy(g_pcFoodStatus->waiting2Item[g_pcFoodStatus->waiting2TotalItem], szDishName[i], 16);
				strcat(waiting2Buffer, g_pcFoodStatus->waiting2Item[g_pcFoodStatus->waiting2TotalItem]);
				SetWindowText(g_pcDlgItemHwnd->hwndEdit_Waiting2, waiting2Buffer);

			}

			g_pcFoodStatus->waiting2TotalItem++;
			SetEvent(g_hEvent_Waiting[1]);
			memset(waiting2Buffer, 0, 128);
		}

		ReleaseSemaphore(g_hSemaphore, 1, NULL);
		Sleep(randValue);
	}
	g_pcFoodStatus->isFinishCook = true;
	
	return 0;
}

DWORD WINAPI Thread_Customer(LPVOID lpParameter) {
	// Have to wait for event to set before start
	// Delete from waiting when grab.
	int threadNumber = (int)lpParameter;

	char szBuffer[128] = { 0 };
	char szPopItem[16] = { 0 };
	char waitingTableBuffer[128] = { 0 };

	while (g_pcFoodStatus->waiting1TotalItem + g_pcFoodStatus->waiting2TotalItem || !g_pcFoodStatus->isFinishCook) {
		switch (WaitForMultipleObjects(2, g_hEvent_Waiting, false, INFINITE)) {
		case 0:
			// Set wintext(Customer), 2. delete item from foodstatus 3. Order Item 4. total-- 5. Set windowstext(Waiting 1)
			// case that both have signal, both will run at the same time?
			if ((int)(g_pcFoodStatus->waiting1TotalItem - 1) >= 0) {
				popWaitingItem(0, szPopItem);
				GetWindowText(*(&(g_pcDlgItemHwnd->hwndEdit_Customer1) + threadNumber), szBuffer, 128);
				for (unsigned int i = 0; i < g_pcFoodStatus->waiting1TotalItem; i++) {
					if (*szBuffer == 0) {
						strcat(szBuffer, szPopItem);
					}
					else {
						if (!i)
							memset(szBuffer, 0, 128);
						GetWindowText(*(&(g_pcDlgItemHwnd->hwndEdit_Customer1) + threadNumber), szBuffer, 128);
						strcat(szBuffer, ", ");
						strcat(szBuffer, szPopItem);
					}
				}
				SetWindowText(*(&(g_pcDlgItemHwnd->hwndEdit_Customer1) + threadNumber), szBuffer);
				memset(szBuffer, 0, 128);

				// Set waiting text
				for (unsigned int i = 0; i < (g_pcFoodStatus->waiting1TotalItem - 1); i++) {
					if (!i)
						strcat(szBuffer, g_pcFoodStatus->waiting1Item[0]);
					else {
						strcat(szBuffer, ", ");
						strcat(szBuffer, g_pcFoodStatus->waiting1Item[i]);
					}
				}
				SetWindowText(g_pcDlgItemHwnd->hwndEdit_Waiting1, szBuffer);
				g_pcFoodStatus->waiting1TotalItem--;
				SetEvent(g_hEvent_Waiting[0]);
				memset(szBuffer, 0, 128);

				// Process to eat
				Sleep(5000);

				if (!(g_pcFoodStatus->waiting1TotalItem) && g_pcFoodStatus->isFinishCook == true)
					ResetEvent(g_hEvent_Waiting[0]);
			}

			break;

		case 1:

			if ((int)(g_pcFoodStatus->waiting2TotalItem - 1) >= 0) {
				popWaitingItem(1, szPopItem);
				GetWindowText(*(&(g_pcDlgItemHwnd->hwndEdit_Customer1) + threadNumber), szBuffer, 128);
				for (unsigned int i = 0; i < g_pcFoodStatus->waiting2TotalItem; i++) {
					if (*szBuffer == 0) {
						strcat(szBuffer, szPopItem);
					}
					else {
						if (!i)
							memset(szBuffer, 0, 128);
						GetWindowText(*(&(g_pcDlgItemHwnd->hwndEdit_Customer1) + threadNumber), szBuffer, 128);
						strcat(szBuffer, ", ");
						strcat(szBuffer, szPopItem);
					}
				}
				SetWindowText(*(&(g_pcDlgItemHwnd->hwndEdit_Customer1) + threadNumber), szBuffer);
				memset(szBuffer, 0, 128);

				// Set waiting text
				for (unsigned int i = 0; i < (g_pcFoodStatus->waiting2TotalItem - 1); i++) {
					if (!i)
						strcat(szBuffer, g_pcFoodStatus->waiting2Item[0]);
					else {
						strcat(szBuffer, ", ");
						strcat(szBuffer, g_pcFoodStatus->waiting2Item[i]);
					}
				}
				SetWindowText(g_pcDlgItemHwnd->hwndEdit_Waiting2, szBuffer);
				g_pcFoodStatus->waiting2TotalItem--;
				SetEvent(g_hEvent_Waiting[1]);
				memset(szBuffer, 0, 128);

				// Process to eat
				Sleep(5000);

				if (!(g_pcFoodStatus->waiting2TotalItem) && g_pcFoodStatus->isFinishCook == true)
					ResetEvent(g_hEvent_Waiting[1]);
			}
			break;
		}
	}

	return 0;
}

unsigned int trimDish(_In_ char* dishNameBuffer, _Out_ char szDishName[16][16]) {
	// return how many dishs and output dish name.
	memset(szDishName, 0, 256);
	char* tempDishNameBuffer = dishNameBuffer;
	unsigned int totalDish = 0;
	unsigned int charOffset = 0;

	while (*(tempDishNameBuffer + 1) != 0) {
		if (*tempDishNameBuffer == ',' && *(tempDishNameBuffer + 1) == ' ') {
			tempDishNameBuffer += 2;
			totalDish++;
			charOffset = 0;

		} else if(*tempDishNameBuffer != ',') {
			szDishName[totalDish][charOffset] = *tempDishNameBuffer;
			tempDishNameBuffer++;
			charOffset++;

		} else {
			tempDishNameBuffer++;
			totalDish++;
			charOffset = 0;
		}
	}
	szDishName[totalDish][charOffset] = *tempDishNameBuffer;

	return ++totalDish;
}

void popWaitingItem(unsigned int waitingIndex, char* szBuffer) {

	switch (waitingIndex) {
	case 0:
		// have a chance case array out of bounce
		memcpy(szBuffer, g_pcFoodStatus->waiting1Item[0], 16);
		for (unsigned int i = 0; i < g_pcFoodStatus->waiting1TotalItem; i++) {
			memcpy(g_pcFoodStatus->waiting1Item[i], g_pcFoodStatus->waiting1Item[i + 1], 16);
		}
		memset(g_pcFoodStatus->waiting1Item[g_pcFoodStatus->waiting1TotalItem], 0, 16);
		break;

	case 1:
		memcpy(szBuffer, g_pcFoodStatus->waiting2Item[0], 16);
		for (unsigned int i = 0; i < g_pcFoodStatus->waiting2TotalItem; i++) {
			memcpy(g_pcFoodStatus->waiting2Item[i], g_pcFoodStatus->waiting2Item[i + 1], 16);
		}
		memset(g_pcFoodStatus->waiting2Item[g_pcFoodStatus->waiting2TotalItem], 0, 16);
		break;
	}

	return;
}
