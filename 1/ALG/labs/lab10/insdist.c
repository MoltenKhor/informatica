#include <stdlib.h>
#include <stdio.h>
#define P 999149

typedef struct _node{
	int key;
	struct _node * next;
}Node;

typedef struct _hTab{
	int slots;
	int usedSlots;
	int a;
	int b;
	int p;
	int conflicts;
	int max_list_size;
	struct _node ** tab;
}HashTab;

int hash(int x, int n, int a, int b, int p){
	return((a*x + b)%p)%n;
}

void insertDistinct(HashTab * t, int k){
	int listLen = 0;
	int distinct = 1;
	int h = hash(k, t->slots, t->a, t->b, t->p);
	Node * aux = (Node*)malloc(sizeof(Node));
	aux->key = k;
	aux->next = NULL;
	if(t->tab[h] == NULL){
		t->tab[h] = aux;
		listLen++;
		t->usedSlots++;
	}else{
		listLen++;
		Node * curr = t->tab[h];
		if(curr->key == k){ distinct = 0; }
		while(curr->next != NULL){
			if(curr->key == k){ distinct =0; }
			listLen++;
			curr = curr->next;
		}
		if(distinct == 1){
			curr->next = aux;
			listLen++;
			t->usedSlots++;
			t->conflicts++;
		}
	}
	if(listLen > t->max_list_size){ t->max_list_size = listLen; }
}

void readHTab(HashTab * t){
	int n, a, b;
	int k;
	scanf("%d", &n);
	scanf("%d", &a);
	scanf("%d", &b);

	t->slots = 2*n;
	t->usedSlots = 0;
	t->a = a;
	t->b = b;
	t->p = P;
	t->conflicts = 0;
	t->max_list_size = 0;

	t->tab = (Node **)malloc(t->slots * sizeof(Node*));
	for(int i=0; i<n; i++){ t->tab[i]=NULL; }
	for(int i=0; i<n; i++){
		scanf("%d", &k);
		insertDistinct(t, k);
	} 

}

int main(){
	HashTab tab;
	readHTab(&tab);
	printf("%d\n%d\n%d\n", tab.conflicts, tab.max_list_size, tab.usedSlots);
	return 0;
}
