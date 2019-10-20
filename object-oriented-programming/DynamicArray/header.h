#ifndef DYNAMICARRAY_H_
#define DYNAMICARRAY_H_

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"

#define SUCCESS 1
#define ERROR -1
#define MALLOC_ERROR -2
#define INDEX_ERROR -3

#define BOOL bool
#define BYTE char
#define WORD short
#define DWORD int

#define OUT
#endif // !DYNAMICARRAY_H_

// CharShotInt
template <class T_CSI>
class Vector {
public:
	Vector();
	Vector(DWORD size);
	~Vector();

public:
	DWORD fnIndexOf(DWORD index, OUT T_CSI* pElement);
	DWORD fnReplace(DWORD index, T_CSI element);
	void fnPush(T_CSI element);
	T_CSI fnPop();
	DWORD fnInsert(DWORD index, T_CSI element);
	DWORD fnCapacity();
	void fnClear();
	BOOL isEmpty();
	void fnDelete(DWORD index);
	DWORD fnLength();
	void fnPrint();

private:
	BOOL fnExpand();

private:
	DWORD m_Index;
	DWORD m_Increment;
	DWORD m_Length;
	DWORD m_InitLength;
	T_CSI* m_pVector;

};

template <class T_CSI>
Vector<T_CSI>::Vector() :m_InitLength(1), m_Increment(2 * (1 * 4)) {
	m_pVector = new T_CSI[4]();
	m_Index = 0;
	m_Length = m_Index;
};

template <class T_CSI>
Vector<T_CSI>::Vector(DWORD size) {
	int arrayCapacity = 4 * ((size / 4) + 1);

	// There are no m_InitLength
	m_Increment = 2 * arrayCapacity;
	m_pVector = new T_CSI[arrayCapacity]();
	m_Index = 0;
	m_Length = m_Index;
	m_InitLength = -1;
};

template <class T_CSI>
Vector<T_CSI>::~Vector() {
	delete[] m_pVector;
	printf("List Free!\n");
};

template <class T_CSI>
BOOL Vector<T_CSI>::fnExpand() {
	int newCapacity = 2 * m_Increment;
	T_CSI* old_m_pVector = m_pVector;

	m_pVector = new T_CSI[m_Increment]();
	if (m_pVector == NULL) {
		printf("Fail to allocate memory! Code: %d", MALLOC_ERROR);
		return false;
	}
	else 
		memcpy(m_pVector, old_m_pVector, sizeof(T_CSI) * m_Length);

	delete[] old_m_pVector;

	m_Increment = newCapacity;

	return true;
}

template <class T_CSI>
void Vector<T_CSI>::fnPush(T_CSI element) {
	if (m_Index == fnCapacity()) {
		fnExpand();
	}
	*(m_pVector + m_Index) = element;
	m_Index++;
	m_Length++;
	return;
}

template <class T_CSI>
T_CSI Vector<T_CSI>::fnPop() {
	T_CSI buffer = *(m_pVector + m_Index);
	m_Index--;
	m_Length--;
	*(m_pVector + m_Index) = 0;

	return buffer;
}

template <class T_CSI>
DWORD Vector<T_CSI>::fnInsert(DWORD index, T_CSI element) {
	if ((m_Index + 1) > fnCapacity()) 
		fnExpand();

	T_CSI tempNum1 = *(m_pVector + index +1);
	*(m_pVector + index + 1) = *(m_pVector + index);
	T_CSI tempNum2 = tempNum1;
	for (int tempIndex = (index + 1); tempIndex < m_Length; tempIndex++) {
		tempNum1 = *(m_pVector + (tempIndex + 1));
		*(m_pVector + tempIndex + 1) = tempNum2;
		tempNum2 = tempNum1;
	}
	*(m_pVector + index) = element;
	m_Length++;

	return 0;
}

template <class T_CSI>
DWORD Vector<T_CSI>::fnIndexOf(DWORD index, OUT T_CSI* pElement) {
	*pElement = *(m_pVector + index);

	return 0;
}

template <class T_CSI>
DWORD Vector<T_CSI>::fnReplace(DWORD index, T_CSI element) {
	if (index > m_Length || index < 0) {
		printf("Access oversize! Code: %d", INDEX_ERROR);
		return INDEX_ERROR;
	}

	*(m_pVector + index) = element;

	return 0;
}

template <class T_CSI>
DWORD Vector<T_CSI>::fnCapacity() {
	return m_Increment / 2;
}

template <class T_CSI>
void Vector<T_CSI>::fnClear() {
	for (int loopCounter = 0; loopCounter < m_Length; loopCounter++) {
		*(m_pVector + loopCounter) = 0;
	}
	m_Index = 0;
	m_Length = 0;
	return;
}

template <class T_CSI>
BOOL Vector<T_CSI>::isEmpty() {
	if (m_Length == 0) 
		return true;
	
	return false;
}

template <class T_CSI>
void Vector<T_CSI>::fnDelete(DWORD index) {
	for (int loopCounter = index; loopCounter < m_Length; loopCounter++) {
		*(m_pVector + loopCounter) = *(m_pVector + loopCounter + 1);
	}
	*(m_pVector + m_Length -1) = 0;
	m_Length--;
	return;
}

template <class T_CSI>
DWORD Vector<T_CSI>::fnLength() {
	return m_Length;
}

template <class T_CSI>
void Vector<T_CSI>::fnPrint() {
	if (m_Length != 0) {
		for (int loopCounter = 0; loopCounter < m_Length; loopCounter++) {
			printf("%d ", *(m_pVector + loopCounter));
		}
		printf("\n");
	}
	else
		printf("Empty List!\n");
	return;
}
