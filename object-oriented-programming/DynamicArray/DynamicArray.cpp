/*
;|**********************************************************************;
;* Project           : CPP-Language_practise
;*
;* Program name      : DynamicArray.cpp
;*
;* Author            : SIO TOU LAI (laisiotou1997@gmail.com)
;*
;* Date created      : 20/10/2019
;*
;* Version           : internal
;*
;* Copyright         : GNU GENERAL PUBLIC LICENSE Version 3
;*
;* Purpose           : Introduce List (Dynamic Array)
;*
;* Revision History  :
;* Date        Author      Ref    Revision (Date in DDMMYYYY format)
;* 20102019    lst97       1      First release
;*
;* Known Issue       :
;* 1. Missing some validations.
;*
;* TODO              :
;*
;|**********************************************************************;
*/
#include "header.h"

int main(int argc, char *argv[]) {
    Vector<int> *cVector = new Vector<int>;
    
    printf("IsEmpty(): %d\n", cVector->isEmpty());
    cVector->fnPrint();
    printf("\n");

    printf("Generating Numbers...\n");
    for (int loopCounter = 0; loopCounter < 3; loopCounter++) {
        cVector->fnPush(rand());
    }
    cVector->fnPrint();

    printf("Capacity: %d\nLength: %d\n", cVector->fnCapacity(), cVector->fnLength());

    printf("\nfnInsert():\t");
    cVector->fnInsert(1, -1);
    cVector->fnPrint();

    printf("\nfnDelete():\t");
    cVector->fnDelete(1);
    cVector->fnPrint();

    printf("\nfnPush():\t");
    cVector->fnPush(-88);
    cVector->fnPrint();

    printf("\nfnPop():\t");
    cVector->fnPop();
    cVector->fnPrint();

    printf("\nfnReplace():\t");
    cVector->fnReplace(1, -123);
    cVector->fnPrint();

    printf("\nfnClear():\t");
    cVector->fnClear();
    cVector->fnPrint();

    printf("\n");
    delete cVector;

    getchar();
    return 0;
}
