// Author: justin0u0 <justin0u0@gapp.nthu.edu.tw>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

// Example of creating new Node
// Node *newNode = createNode(1);
Node *createNode(int val) {
	Node newNodeInst = {
		.val = val,
		.prevPtr = NULL,
		.nextPtr = NULL
	};
	Node *newNode = (Node *)malloc(sizeof(Node));
	memcpy(newNode, &newNodeInst, sizeof(newNodeInst));
	return newNode;
}
void travel(Node *head) {
	Node *cur = head;
	while(cur->nextPtr != head){
		printf("%d ", cur->val);
		cur = cur->nextPtr;
	}
	printf("%d\n", cur->val);

	cur = head->prevPtr;
	while(cur->prevPtr != head->prevPtr){
		printf("%d ", cur->val);
		cur = cur->prevPtr;
	}
	printf("%d\n", cur->val);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif
	int n, m;
	scanf("%d%d", &n, &m);

	/* Build a circlular linked list from 1 ~ N */
	Node *node = buildDoublyCircularLinkedList(n);
	travel(node);
	/* Start N-1 rounds process */
	for (int i = n; i > 1; i--) {
		int peopleLeft = i;
		printf("Round %d\n", i);
		travel(node);
		// 1. Get the node that will get out of the circle this round
		Node *nextPersonOut = getNextPersonOut(peopleLeft, m, node);
		printf("Kill %d\n", nextPersonOut->val);
		// 2. Get it's neighbors, remove the person out of the circle (free the node)
		Node *personInFront = nextPersonOut->prevPtr;
		Node *personInBack = nextPersonOut->nextPtr;
		free(nextPersonOut);
		// 3. Build connection between 'personInFront' and 'personInBack'
		connectNodes(personInFront, personInBack);
		// 3. Swap the neighbors' position
		if (peopleLeft > 3)
		  swapNodes(personInFront, personInBack);
		// 4. Get the smaller value node
		if (personInFront->val < personInBack->val)
			node = personInFront;
		else
			node = personInBack;
	}
	
	// Output the value of the last person
	printf("%d\n", node->val);
	return 0;
}

