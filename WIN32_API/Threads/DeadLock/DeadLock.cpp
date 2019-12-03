/*
;|**********************************************************************;
;* Project           : CPP-Language_practise
;*
;* Program name      : DeadLock.cpp
;*
;* Author            : SIO TOU LAI (laisiotou1997@gmail.com)
;*
;* Date created      : 03/12/2019
;*
;* Version           : internal
;*
;* Copyright         : GNU GENERAL PUBLIC LICENSE Version 3
;*
;* Purpose           : thread Dead-Lock, Critical Section demo
;*
;* Revision History  :
;* Date        Author      Ref    Revision (Date in DDMMYYYY format)
;* 03122019    lst97       1      First release
;*
;* Known Issue       :
;*
;* TODO              :
;*
;|**********************************************************************;
*/

#include "windows.h"
#include "stdio.h"

CRITICAL_SECTION g_cs_x;
CRITICAL_SECTION g_cs_y;

DWORD WINAPI Thread_Thread1(LPVOID lpParameter);
DWORD WINAPI Thread_Thread2(LPVOID lpParameter);

int main(int argc, char* argv[]) {

	InitializeCriticalSection(&g_cs_x);
	InitializeCriticalSection(&g_cs_y);
	char* p_testChar = new char;


	HANDLE hThread1 = CreateThread(NULL, 0, Thread_Thread1, (void*)p_testChar, 0, NULL);
	HANDLE hThread2 = CreateThread(NULL, 0, Thread_Thread2, (void*)p_testChar, 0, NULL);

	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE);
	return 0;
}

DWORD WINAPI Thread_Thread1(LPVOID lpParameter) {
	char testChar = *((char*)lpParameter);

	while (true){
		EnterCriticalSection(&g_cs_x);
		testChar = 'x';
		printf("%c \n", testChar);
			EnterCriticalSection(&g_cs_y);
			testChar = 'y';
			printf("%c \n", testChar);
			LeaveCriticalSection(&g_cs_y);
		LeaveCriticalSection(&g_cs_x);
	}

	return 0;
}

DWORD WINAPI Thread_Thread2(LPVOID lpParameter) {
	char testChar = *((char*)lpParameter);

	while (true) {
		EnterCriticalSection(&g_cs_y);
		testChar = 'y';
		printf("%c \n", testChar);
			EnterCriticalSection(&g_cs_x);
			testChar = 'x';
			printf("%c \n", testChar);
			LeaveCriticalSection(&g_cs_x);
		LeaveCriticalSection(&g_cs_y);
	}
	return 0;
}
