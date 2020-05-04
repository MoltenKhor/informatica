#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
	int key;
	struct _node * next;
	struct _node * prev;
}Node;

void addBottom(Node **h, Node **t, int k){
	Node * aux = malloc(sizeof(Node));

	aux->key = k;
	aux->next = NULL;
	if(*t == NULL){
		*h = aux;
		*t = aux;
		aux->prev = NULL;
	}else{
		(*t)->next = aux;
		aux->prev = *t;
		*t = aux;
	}
}

void readList(Node **h, Node **t, int *n){
	Node * head = NULL;
	Node * tail = NULL;
	int val;

	scanf("%d", n);

	for(int i=0; i<*n; i++){
		scanf("%d", &val);
		addBottom(&head, &tail, val);
	}
	*h = head;
	*t = tail;
}

void printList(Node *t){
	if(t!=NULL){
		printf("%d\n", t->key);
		printList(t->prev);
	}
}

int main(){
	Node *head = NULL;
	Node *tail = NULL;
	int n;
	readList(&head, &tail, &n);
	printList(tail);
	return 0;
}
