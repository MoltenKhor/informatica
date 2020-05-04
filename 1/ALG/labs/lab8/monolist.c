#include <stdio.h>
#include <stdlib.h>

typedef struct _elem{
	int key;
	struct _elem *next;
}elem;

elem* inserisciCoda(elem *head, int key){
	if(head->next == NULL){
		elem *nuovo = (elem*)malloc(sizeof(elem));
		nuovo->key = key;
		nuovo->next == NULL;
		head->next = nuovo;
		return nuovo;
	}else{
		return inserisciCoda(head->next, key);
	}
}

void addBottom(elem **h, elem **t, int k){
	elem * aux = malloc(sizeof(elem));

	aux->key = k;
	aux->next = NULL;
	if(*t == NULL){
		*h = aux;
		*t = aux;
	}else{
		(*t)->next = aux;
		*t = aux;
	}
}


void readList(elem **h, elem **t, int *n){
	elem * head = NULL;
	elem * tail = NULL;
	int val;

	scanf("%d", n);
	for(int i=0; i<*n; i++){
		scanf("%d", &val);
		addBottom(&head, &tail, val);
	}

	*h = head;
	*t = tail;
}
void printList(elem **h){
	if(*h != NULL){
		printList(&((*h)->next));
		printf("%d\n", (*h)->key);
	}
}

int main(){
	int n;
	elem * head = NULL;
	elem * tail = NULL;

	readList(&head, &tail, &n);
	printList(&head);
	return 0;
}
