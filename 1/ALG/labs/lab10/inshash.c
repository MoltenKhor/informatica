#include <stdlib.h>
#include <stdio.h>
#define P 999149

typedef struct _node{
	struct _node * next;
	int key;
}item;

typedef struct _HashTab{
	int slots;
	int a;
	int b;
	int p;
	int conflicts;
	int max_list_size;
	struct _node ** tab;
}hTab;

int hash(int x, int n, int a, int b, int p){
	return((a*x+b)%p)%n;
}

void insertHash(hTab * t, int k){
	int listLen = 0;
	int h = hash(k, t->slots, t->a, t->b, t->p);
	item * aux = (item*)malloc(sizeof(item));
	aux->key = k;
	aux->next = NULL;
	if(t->tab[h]==NULL){
		t->tab[h] = aux;
		listLen++;
	}else{
		t->conflicts++;
		listLen++;
		item * curr = t->tab[h];
		while(curr->next != NULL){
			listLen++;
			curr = curr->next;
		}
		curr->next = aux;
		listLen++;
	}
	if(listLen > t->max_list_size){ t->max_list_size = listLen; }
}

void readHash(hTab * t){
	int a,b,n;
	int k;
	scanf("%d", &n);
	scanf("%d", &a);
	scanf("%d", &b);

	t->slots = 2*n;
	t->a = a;
	t->b = b;
	t->p = P;
	t->conflicts = 0;
	t->max_list_size = 0;

	t->tab = (item**)malloc(t->slots * sizeof(item*));
	for(int i=0; i<t->slots; i++){
		t->tab[i] = NULL;
	}
	for(int i=0; i<n; i++){
		scanf("%d", &k);
		insertHash(t, k);
	}
}

int main(){
	hTab tab;
	readHash(&tab);
	printf("%d\n%d\n", tab.max_list_size, tab.conflicts);
	return 0;
}
