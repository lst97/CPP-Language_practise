#pragma once
#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"

#define SUCCESS 1
#define ERROR -1
#define INDEX_IS_ERROR -2
#define BUFFER_IS_EMPTY -3

#define BOOL bool
#define WORD short
#define DWORD int

#define IN
#define OUT
#endif // !LINKEDLIST_H

template<class T_CSI>
class LinkedList {
public:
	LinkedList();
	~LinkedList();

public:
	BOOL fnIsEmpty();
	void fnClear();
	DWORD fnGetElement(IN DWORD index, OUT T_CSI& element);
	DWORD fnSearchElement(IN T_CSI element);
	DWORD fnInsert(IN T_CSI element);
	DWORD fnInsert(IN DWORD index, IN T_CSI element);
	DWORD fnDelete(IN DWORD index);
	DWORD fnGetSize();
	DWORD fnPrintAll();

private:
	typedef struct _NODE {
		T_CSI data;
		_NODE* pNext;
	}NODE, *PNODE;

	PNODE GetIndexCurrentNode(DWORD index);
	PNODE GetIndexPreviousNode(DWORD index);
	PNODE GetIndexNextNode(DWORD index);

private:
	PNODE m_pHead;
	DWORD m_Length;

};

template<class T_CSI>
LinkedList<T_CSI>::LinkedList() :m_pHead(NULL), m_Length(0) {

}

template<class T_CSI>
DWORD LinkedList<T_CSI>::fnInsert(IN T_CSI element) {
	if (fnIsEmpty()) {
		PNODE newNode = new NODE;
		newNode->data = element;
		newNode->pNext = NULL;

		m_pHead = newNode;
		m_Length++;
		return SUCCESS;
	}
	else {
		PNODE pPreviousNode_TEMP = GetIndexPreviousNode(m_Length - 1);

		PNODE newNode = new NODE;
		newNode->data = element;
		pPreviousNode_TEMP->pNext = newNode;
		newNode->pNext = NULL;
		m_Length++;
		return SUCCESS;
	}
	return SUCCESS;
}

template<class T_CSI>
DWORD LinkedList<T_CSI>::fnInsert(IN DWORD index, IN T_CSI element) {
	if ((fnIsEmpty() && index != 0) || index > m_Length || index < 0) {
		printf("Index Over Size! CODE: -2\n");
		return INDEX_IS_ERROR;
	}
	else {
		PNODE pPreviousNode = GetIndexPreviousNode(index);
		PNODE pCurrentNode = GetIndexCurrentNode(index);
		PNODE pNewNode = new NODE;
		pNewNode->data = element;
		if (index == (m_Length - 1)) {
			pPreviousNode->pNext = pNewNode;
			pNewNode->pNext = NULL;
		}
		else {
			PNODE pNextNode = GetIndexNextNode(index);
			pPreviousNode->pNext = pNewNode;
			pNewNode->pNext = pCurrentNode;
		}
		m_Length++;
		return SUCCESS;
	}
	
	return SUCCESS;
}

template<class T_CSI>
typename LinkedList<T_CSI>:: PNODE
LinkedList<T_CSI>:: GetIndexCurrentNode(DWORD index) {
	PNODE pNode_Current = m_pHead;
	for (int loopCounter = 0; loopCounter < index; loopCounter++) {
		pNode_Current = pNode_Current->pNext;
	}
	return pNode_Current;
}

template<class T_CSI>
typename LinkedList<T_CSI>::PNODE
LinkedList<T_CSI>:: GetIndexPreviousNode(DWORD index) {
	PNODE pNode_Pervious = m_pHead;
	int perviousIndex = index - 1;

	for (int loopCounter = 0; loopCounter < perviousIndex; loopCounter++) {
		pNode_Pervious = pNode_Pervious->pNext;
	}
	return pNode_Pervious;
}

template<class T_CSI>
typename LinkedList<T_CSI>::PNODE
LinkedList<T_CSI>:: GetIndexNextNode(DWORD index) {
	PNODE pNode_Next = m_pHead;
	int nextIndex = index + 1;

	for (int loopCounter = 0; loopCounter < nextIndex; loopCounter++) {
		pNode_Next = pNode_Next->pNext;
	}
	return pNode_Next;
}

template<class T_CSI>
BOOL LinkedList<T_CSI>:: fnIsEmpty() {
	if (m_pHead == NULL && m_Length == 0) {
		return true;
	}
	return false;
}

template<class T_CSI>
DWORD LinkedList<T_CSI>:: fnGetElement(IN DWORD index, OUT T_CSI& element) {
	if (index >= m_Length || index < 0) {
		printf("Index Over Size! CODE: -2\n");
		return INDEX_IS_ERROR;
	}
	element = GetIndexCurrentNode(index)->data;
	return SUCCESS;
}

template<class T_CSI>
DWORD LinkedList<T_CSI>::fnSearchElement(IN T_CSI element) {

	int indexCounter = 0;
	PNODE pNode = m_pHead;
	PNODE pPeriousNode;
	
	do {
		pPeriousNode = pNode->pNext;
		if (pNode->data == element)
			return indexCounter;
		pNode = pPeriousNode;
		indexCounter++;
	} while (pPeriousNode != NULL && indexCounter < m_Length);
	
	printf("Element Not Found!\n");
	return -1;
}

template<class T_CSI>
DWORD LinkedList<T_CSI>::fnGetSize() {

	return m_Length;
}

template<class T_CSI>
DWORD LinkedList<T_CSI>::fnDelete(IN DWORD index){

	if (index >= m_Length || index < 0) {
		printf("Index Over Size! CODE: -2\n");
		return INDEX_IS_ERROR;
	}
	PNODE pPeriousNode;
	PNODE pCurrentNode;

	if (index == (m_Length -1)) {
		pCurrentNode = GetIndexCurrentNode(index);
		pPeriousNode = GetIndexPreviousNode(index);
		pPeriousNode->pNext = NULL;
	}
	else {
		PNODE pNextNode = GetIndexNextNode(index);
		pCurrentNode = GetIndexCurrentNode(index);
		pPeriousNode = GetIndexPreviousNode(index);
		pPeriousNode->pNext = pNextNode;
	}
	delete pCurrentNode;
	m_Length--;

	return SUCCESS;
}

template<class T_CSI>
void LinkedList<T_CSI>::fnClear() {
	if (m_Length != 0) {
		PNODE pNode = m_pHead;
		PNODE pPeriousNode = m_pHead;

		do {
			if (pNode->pNext != NULL) {
				pNode = pNode->pNext;
				delete pPeriousNode;
				pPeriousNode = pNode;
				m_Length--;
			}
			else {
				delete pNode;
				pNode = NULL;
				m_Length = 0;
				printf("Clear!\n");
				break;
			}
		} while (pNode != NULL);
	}
	printf("LinkedList Not Found!\n");
}

template<class T_CSI>
DWORD LinkedList<T_CSI>::fnPrintAll() {
	if (m_Length > 0) {
		PNODE pNode = m_pHead;
		PNODE pPeriousNode = m_pHead;
		do {
			printf("%d ", pNode->data);
			pPeriousNode = pNode;
			pNode = pNode->pNext;

		} while (pNode != NULL);
		printf("%d\n[%d] element/s left\n", pPeriousNode->data, m_Length);

		return SUCCESS;
	}
	printf("Linked List is Empty!\n");
	return -1;
}

template<class T_CSI>
LinkedList<T_CSI>::~LinkedList(){
	fnClear();
}
