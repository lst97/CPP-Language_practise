#pragma once
#include "stdio.h"
#include "string.h"

class Monster {
public:
	int monsterID;
	int monsterLevel;
	char monsterName[20];

public:
	Monster() {}
	Monster(int ID, int Level, const char* Name) {
		this->monsterID = ID;
		this->monsterLevel = Level;
		memcpy(&this->monsterName, Name, strlen(Name) + 1);
	}
};

template<class T_Monster>
class TreeNode {
public:
	T_Monster element;
	TreeNode<T_Monster>* pLeftNode;
	TreeNode<T_Monster>* pRightNode;

	TreeNode(T_Monster& element) {
		// Init node
		memset(&this->element, 0, sizeof(TreeNode));

		// Set chacteristic
		memcpy(&this->element, &element, sizeof(T_Monster));
		pLeftNode = pRightNode = NULL;
	}
};

template<class T_Monster>
class BSortTree {
public:
	BSortTree();
	~BSortTree();

public:
	void PreOrderTraverse(TreeNode<T_Monster>* pNode);
	void InOrderTraverse(TreeNode<T_Monster>* pNode);
	void PostOrderTraverse(TreeNode<T_Monster>* pNode);
	TreeNode<T_Monster>* GetRoot();
	int GetDepth(TreeNode<T_Monster>* pNode);

private:
	void Init();

private:
	TreeNode<T_Monster>* m_pRoot;
	int size;
};

template<class T_Monster>
BSortTree<T_Monster>::BSortTree() {
	Init();
}

template<class T_Monster>
BSortTree<T_Monster>::~BSortTree() {
	// Free all the heap
}

template <class T_Monster>
void BSortTree<T_Monster>::Init() {
	Monster m1(1, 1, "Dog");
	Monster m2(2, 2, "Cat");
	Monster m3(3, 3, "Train");
	Monster m4(4, 4, "Pig");
	Monster m5(5, 5, "Woft");
	Monster m6(6, 6, "Rumbat");
	Monster m7(7, 7, "Fish");
	Monster m8(8, 8, "PC");

	TreeNode<Monster>* n1 = new TreeNode<Monster>(m1);
	TreeNode<Monster>* n2 = new TreeNode<Monster>(m2);
	TreeNode<Monster>* n3 = new TreeNode<Monster>(m3);
	TreeNode<Monster>* n4 = new TreeNode<Monster>(m4);
	TreeNode<Monster>* n5 = new TreeNode<Monster>(m5);
	TreeNode<Monster>* n6 = new TreeNode<Monster>(m6);
	TreeNode<Monster>* n7 = new TreeNode<Monster>(m7);
	TreeNode<Monster>* n8 = new TreeNode<Monster>(m8);

	m_pRoot = n5;
	n5->pLeftNode = n4;
	n5->pRightNode = n6;
	n4->pLeftNode = n1;
	n1->pRightNode = n2;
	n1->pLeftNode = n8;
	n6->pLeftNode = n3;
	n3->pRightNode = n7;
	size = 8;
}

template<class T_Monster>
TreeNode<T_Monster>* BSortTree<T_Monster>::GetRoot() {
	return m_pRoot;
}


template<class T_Monster>
int BSortTree<T_Monster>:: GetDepth(TreeNode<T_Monster>* pNode) {
	if (pNode == NULL) {
		return 0;
	}
	else {
		int m = GetDepth(pNode->pLeftNode);
		int n = GetDepth(pNode->pRightNode);
		return (m > n) ? (m + 1) : (n + 1);
	}
}

template<class T_Monster>
void BSortTree<T_Monster>::PreOrderTraverse(TreeNode<T_Monster>* pNode) {
	// Travel
	if (pNode == NULL) {
		return;
	}
	else {
		PreOrderTraverse(pNode->pLeftNode);
		printf("Depth: %d\nMonsterID: %d\nMonsterLevel: %d\nMonsterName: %s\n\n",
			(int)GetDepth(pNode),
			*(int*)(&pNode->element),
			*((int*)(&pNode->element) + 1),
			(char*)((int*)(&pNode->element) + 2)
		);
		PreOrderTraverse(pNode->pRightNode);
	}
}

template<class T_Monster>
void BSortTree<T_Monster>::InOrderTraverse(TreeNode<T_Monster>* pNode) {
	//
	if (pNode == NULL) {
		return;
	}
	else {
		printf("Depth: %d\nMonsterID: %d\nMonsterLevel: %d\nMonsterName: %s\n\n",
			(int)GetDepth(pNode),
			*(int*)(&pNode->element),
			*((int*)(&pNode->element) + 1),
			(char*)((int*)(&pNode->element) + 2)
		);
		InOrderTraverse(pNode->pLeftNode);
		InOrderTraverse(pNode->pRightNode);
	}
}

template<class T_Monster>
void BSortTree<T_Monster>::PostOrderTraverse(TreeNode<T_Monster>* pNode) {
	// Travel
	if (pNode == NULL) {
		return;
	}
	else {
		PostOrderTraverse(pNode->pLeftNode);
		PostOrderTraverse(pNode->pRightNode);
		printf("Depth: %d\nMonsterID: %d\nMonsterLevel: %d\nMonsterName: %s\n\n",
			(int)GetDepth(pNode),
			*(int*)(&pNode->element),
			*((int*)(&pNode->element) + 1),
			(char*)((int*)(&pNode->element) + 2)
		);
	}
}
