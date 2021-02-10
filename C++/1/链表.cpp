#include <stdio.h>
#include <stdlib.h>

struct node {
	int n;
	struct node * pNext;
};

int main() {

	struct node *pHead = NULL, *pEnd = NULL, *pNode = NULL;
	int i = 1;
	printf ("Please input a integer : \n");
	printf("end by inputing 0:");
	do {
		scanf("%d", &i);
		if(i != 0) {
			pNode = (struct node *)malloc(sizeof(struct node));
			if(pNode != NULL) {
				pNode -> n = i;
				pNode -> pNext = NULL;
				if(pHead == NULL) {
					pHead = pNode;
					pEnd = pNode;
				} else {

					pNode -> pNext = pHead;
					pHead = pNode;
				}
			}
		}
	}
while(i != 0);
pNode = pHead;
while(pNode != NULL) {
	printf("%d\t", pNode->n);
	pHead = pNode;
	pNode = pNode->pNext;
	free(pHead);
}
printf("\n");

}
