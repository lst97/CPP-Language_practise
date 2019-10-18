/*
;|**********************************************************************;
;* Project           : CPP-Language_practise
;*
;* Program name      : dynamicBinding.cpp
;*
;* Author            : SIO TOU LAI (laisiotou1997@gmail.com)
;*
;* Date created      : 18/10/2019
;*
;* Version           : internal
;*
;* Copyright         : GNU GENERAL PUBLIC LICENSE Version 3
;*
;* Purpose           : Introduce Dynamic Binding
;*
;* Revision History  :
;* Date        Author      Ref    Revision (Date in DDMMYYYY format)
;* 18102019    lst97       1      First release
;*
;* Known Issue       :
;*
;* TODO              :
;*
;|**********************************************************************;
*/
#include "stdio.h"
#include "stdlib.h"

class Base {
public:
	int x;
	int y;

public:
	Base (){
		x = 1;
		y = 2;
	}
	virtual void Print() {
		printf("Base:%X %X\n", x, y);
	}
};

class Sub1 :public Base {
public:
	int a;
public:
	Sub1(){
		x = 4;
		y = 5;
		a = 6;
	}
	
	virtual void Print() {
		printf("Sub1:%X %X %X\n", x, y, a);
	}
};

class Sub2 :public Base {
public:
	int b;
public:
	Sub2() {
		x = 7;
		y = 8;
		b = 9;
	}

	virtual void Print() {
		printf("Sub2:%X %X %X\n", x, y, b);
	}
};

void TestBound() {
	Base b;
	Sub1 s1;
	Sub2 s2;

	Base* arr[] = { &b, &s1, &s2 };

	for (int i = 0; i < 3; i++) {
		arr[i]->Print();
	}
}

int main(int argc, char* argv[]) {

	TestBound();
	return 0;
}
