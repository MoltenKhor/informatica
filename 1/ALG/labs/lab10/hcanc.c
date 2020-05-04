#include <stdio.h>
#include <stdlib.h>
#define P 999149

typedef struct _node{
	int key;
	struct _node * next;
}Node;

typedef struct _list{
	Node * h;
	Node * t;
}List;

void insertBottom(List * l, int k){
	Node * aux = malloc(sizeof(Node));
	aux->key = k;
	aux->next = NULL;
	if(l->t == NULL){
		l->h = aux;
		l->t = aux;
	}else{
		l->t->next = aux;
		l->t = aux;
	}
}

int readList(List * l){
	int n, k, avg=0;
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		scanf("%d", &k);
		avg+=k;
		insertBottom(l,k);
	}
	return avg/n;
}

void printlist(List l){
	Node * curr = l.h;
	while(curr != NULL){
		printf("%d ", curr->key);
		curr = curr->next;
	}
}

void removeAVG(List * l, int avg){
	Node * curr = l->h;
	Node * prev = NULL;

	if(curr != NULL){
		while(curr!=NULL){
			if(curr->key <= avg){
				if(curr == l->h){
					l->h = curr->next;
					free(curr);
					curr = l->h;
					prev = NULL;
				}else{
					prev->next = curr->next;
					free(curr);
					curr = prev->next;
				}
			}else{
				prev = curr;
				curr = curr->next;
			}
		}
	}
}

int main(){
	List l;
	int avg;

	l.h = NULL;
	l.t = NULL;

	avg = readList(&l);
	printf("%d\n", avg);
	printlist(l);
	removeAVG(&l, avg);
	printf("\n");
	printlist(l);
	return 0;
}
