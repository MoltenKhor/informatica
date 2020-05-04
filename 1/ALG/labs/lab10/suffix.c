#include <stdlib.h>
#include <stdio.h>
#define P 999149

typedef struct _node{
	int key;
	struct _node * next;
}Node;

typedef struct _list{
	Node * t;
	Node * h;
}List;

void insertBottom(List * l, int k){
	Node * aux = malloc(sizeof(Node));
	aux->key = k;
	aux->next = NULL;

	if(l->t == NULL){
		l->t = aux;
		l->h = aux;
	}else{
		l->t->next = aux;
		l->t = aux;
	}
}

void readList(List * l){
	int n, k;
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		scanf("%d", &k);
		insertBottom(l, k);
	}
}

void printList(List l){
	Node * curr = l.h;
	while(curr != NULL){
		printf("%d ", curr->key);
		curr = curr->next;
	}
}

int getSumm(Node * n){
	if(n == NULL){ return 0; }
	else{ return n->key + getSumm(n->next); }
}

void suffix(List l){
	while(l.h != NULL){
		l.h-> key = getSumm(l.h->next);
		l.h = l.h->next;
	}
}

int main(){
	List l;

	l.h = NULL;
	l.t = NULL;
	readList(&l);
	printList(l);
	printf("\n");
	suffix(l);
	printList(l);
	printf("\n");
	return 0;
}
