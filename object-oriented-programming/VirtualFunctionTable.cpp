/*
;|**********************************************************************;
;* Project           : CPP-Language_practise
;*
;* Program name      : VirtualFunctionTable.cpp
;*
;* Author            : SIO TOU LAI (laisiotou1997@gmail.com)
;*
;* Date created      : 17/10/2019
;*
;* Version           : internal
;*
;* Copyright         : GNU GENERAL PUBLIC LICENSE Version 3
;*
;* Purpose           : Introduce what is VirtualFunctionTable
;*
;* Revision History  :
;* Date        Author      Ref    Revision (Date in DDMMYYYY format)
;* 17102019    lst97       1      First release
;*
;* Known Issue       :
;*
;* TODO              :
;*
;|**********************************************************************;
*/
#include "stdio.h"
#include "stdlib.h"

struct ClassA {
public:
	virtual void m_fn1() {
		printf("ClassA:m_fn1\n");
	}
	virtual void m_fn2() {
		printf("ClassA:m_fn2\n");
	}
	virtual void m_fn3() {
		printf("ClassA:m_fn3\n");
	}
};

struct ClassB:ClassA {
public:
	virtual void m_fn4() {
		printf("ClassB:m_fn4\n");
	}
	virtual void m_fn5() {
		printf("ClassB:m_fn5\n");
	}
	virtual void m_fn6() {
		printf("ClassB:m_fn6\n");
	}
};

// OverWrited
struct ClassC {
public:
	virtual void m_fn1() {
		printf("ClassC:m_fn1\n");
	}
	virtual void m_fn2() {
		printf("ClassC:m_fn2\n");
	}
	virtual void m_fn3() {
		printf("ClassC:m_fn3\n");
	}
};

struct ClassD:ClassC {
public:
	virtual void m_fn1() {
		printf("ClassD:m_fn1\n");
	}
	virtual void m_fn2() {
		printf("ClassD:m_fn2\n");
	}
	virtual void m_fn6() {
		printf("ClassD:m_fn6\n");
	}
};

int main(int argc, char* argv[]) {
	int ClassA_FunctionLength = 3;
	int ClassB_FunctionLength = ClassA_FunctionLength + 3;

	int ClassC_FunctionLength = 3;
	int ClassD_FunctionLength = ClassC_FunctionLength + 1;

	typedef ClassA* PClass;
	PClass pClassA;
	PClass pClassB;

	ClassA cClassA;
	ClassB cClassB;

	pClassA = &cClassA;
	pClassB = &cClassB;
	typedef void(*functionAddress)(void);
	functionAddress pFunctionAddress;

	// Run ClassA && ClassB Function
	for (int loopCounter = 0; loopCounter < ClassA_FunctionLength; loopCounter++) {
		pFunctionAddress = (void(__cdecl*)(void))*((int*)(*(int*)pClassA) + loopCounter);
		printf("[0x%08X]\n", pFunctionAddress);
		pFunctionAddress();
	}
	for (int loopCounter = ClassA_FunctionLength; loopCounter < ClassB_FunctionLength; loopCounter++) {
		pFunctionAddress = (void(__cdecl*)(void))*((int*)(*(int*)pClassB) + loopCounter);
		printf("[0x%08X]\n", pFunctionAddress);
		pFunctionAddress();
	}
	printf("\n");
	// Run ClassC && ClassD Function.

	typedef ClassC* PClass2;

	PClass2 pClassC;
	PClass2 pClassD;

	ClassC cClassC;
	ClassD cClassD;

	pClassC = &cClassC;
	pClassD = &cClassD;

	for (int loopCounter = 0; loopCounter < ClassC_FunctionLength; loopCounter++) {
		pFunctionAddress = (void(__cdecl*)(void)) * ((int*)(*(int*)pClassC) + loopCounter);
		printf("[0x%08X]\n", pFunctionAddress);
		pFunctionAddress();
	}
	for (int loopCounter = 0; loopCounter < ClassD_FunctionLength; loopCounter++) {
		pFunctionAddress = (void(__cdecl*)(void)) * ((int*)(*(int*)pClassD) + loopCounter);
		printf("[0x%08X]\n", pFunctionAddress);
		pFunctionAddress();
	}

	return 0;
}
