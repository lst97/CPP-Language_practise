/*
;|**********************************************************************;
;* Project           : CPP-Language_practise
;*
;* Program name      : LinkedList.cpp
;*
;* Author            : SIO TOU LAI (laisiotou1997@gmail.com)
;*
;* Date created      : 23/10/2019
;*
;* Version           : internal
;*
;* Copyright         : GNU GENERAL PUBLIC LICENSE Version 3
;*
;* Purpose           : Introduce what is Linked List
;*
;* Revision History  :
;* Date        Author      Ref    Revision (Date in DDMMYYYY format)
;* 23102019    lst97       1      First release
;*
;* Known Issue       :
;* 1. Only for demo, not well tested!
;*
;* TODO              :
;*
;|**********************************************************************;
*/
#include "Header.h"

// Only for demo, not well tested!
int main(int argc, char *argv[]) {
	LinkedList<int>* cLinkedList = new LinkedList<int>;

	printf("fnIsEmpty(): %d \n\n", cLinkedList->fnIsEmpty());
	printf("Generating number for Linked List...\n");
	for (int loopCounter = 0; loopCounter < 5; loopCounter++) {
		cLinkedList->fnInsert(rand());
	}
	cLinkedList->fnPrintAll();

	printf("\nfnIsEmpty(): %d \n\n", cLinkedList->fnIsEmpty());

	int x;
	cLinkedList->fnGetElement(1, x);
	printf("fnGetElement(1): %d\n\n", x);

	printf("fnSearchElement(26500): %d\n\n", cLinkedList->fnSearchElement(26500));	// Only print last index

	cLinkedList->fnInsert(1, -1);
	printf("fnSearchElement(1, -1):\n");
	cLinkedList->fnPrintAll();
	printf("\n");

	cLinkedList->fnDelete(1);
	printf("fnDelete(1):\n");
	cLinkedList->fnPrintAll();
	printf("\n");

	delete cLinkedList;

	return 0;
}
