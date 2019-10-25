/*
;|**********************************************************************;
;* Project           : CPP-Language_practise
;*
;* Program name      :  BinaryTree.cpp
;*
;* Author            : SIO TOU LAI (laisiotou1997@gmail.com)
;*
;* Date created      : 25/10/2019
;*
;* Version           : internal
;*
;* Copyright         : GNU GENERAL PUBLIC LICENSE Version 3
;*
;* Purpose           : Introduce what is Binary Tree
;*
;* Revision History  :
;* Date        Author      Ref    Revision (Date in DDMMYYYY format)
;* 25102019    lst97       1      First release
;*
;* Known Issue       :
;* 1. Only for demo, not well tested!
;*
;* TODO              :
;*
;|**********************************************************************;
*/
#include "Header.h"

int main(int argc, char *argv[]) {
	BSortTree<Monster>* pcBSortTree = new BSortTree<Monster>;
	printf("Root: %X\n", (unsigned int)pcBSortTree->GetRoot());
	printf("Depth: %d\n\n", (unsigned int)pcBSortTree->GetDepth(pcBSortTree->GetRoot()));

	printf("= = = = = PreOrderTraverse = = = = =\n");
	pcBSortTree->PreOrderTraverse(pcBSortTree->GetRoot());
	printf("= = = = = PreOrderTraverse (END) = = = = =\n\n");

	printf("= = = = = InOrderTraverse = = = = =\n");
	pcBSortTree->InOrderTraverse(pcBSortTree->GetRoot());
	printf("= = = = = InOrderTraverse (END) = = = = =\n");

	printf("= = = = = PostOrderTraverse = = = = =\n");
	pcBSortTree->PostOrderTraverse(pcBSortTree->GetRoot());
	printf("= = = = = PostOrderTraverse = = = = =\n");
	return 0;
}
