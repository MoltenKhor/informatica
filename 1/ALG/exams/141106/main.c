#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>

#define MAX_LEN 101

typedef struct _element{
	char txt[MAX_LEN];
	int val;
	struct _element * next;
}Elem;

typedef struct _hashTab{
	int n; //elements
	struct	_element ** tab;
}HashTab;

int hash(char* name, int len){
	unsigned int x = 0;
	int i=0;
	while(name[i]!= '\0'){
		x+=name[i];
		i++;
	}
	return(x%len);
}

HashTab insertItem(HashTab t, char* name, int val){
	int h = hash(name, t.n);

	Elem * curr = t.tab[h];
	while(curr != NULL){
		if(strcmp(curr->txt, name)){
			if(val <= curr->val){
				return t;
			}else{
				curr->val = val;
				return t;
			}
		}
		curr = curr->next;
	}
	Elem * aux = malloc(sizeof(Elem));
	strcpy(aux->txt, name);
	aux->val = val;
	aux->next = t.tab[h];
	t.tab[h] = aux;

	return t;
}

HashTab readHash(HashTab t){
	char name[MAX_LEN];
	int val;
	int n;
	scanf("%d", &n);
	t.n = 2*n;
	//mem allocation
	t.tab = (Elem**)malloc(t.n * sizeof(Elem*));
	//item init
	for(int i=0; i<n; i++){
		t.tab[i] = NULL;
	}
	//item insert
	for(int i=0; i<n; i++){
		scanf("%s", name);
		scanf("%d", &val);
		t = insertItem(t, name, val);
	}
	return t;
}

int compare(const void * a, const void * b){
	Elem x = *((Elem*)a);
	Elem y = *((Elem*)b);
	if(x.val != y.val) return y.val - x.val;
	else return strcmp(x.txt, y.txt);
}

void printSorted(HashTab tab){
	Elem * curr = NULL;
	int count; 
	Elem * a;
	count = 0;
	if(tab.tab == NULL) return;
	for(int i=0; i<tab.n; i++){
		curr = tab.tab[i];
		while(curr != NULL){
			count++;
			curr = curr->next;
		}
	}
	if(count>0){
		a = malloc(count * sizeof(Elem));
		int j=0;
		for(int i=0; i<tab.n && j<count; i++){
			curr = tab.tab[i];
			while(curr != NULL){
				a[j].val = curr->val;
				strcpy(a[j].txt, curr->txt);
				curr = curr->next;
				j++;
			}
		}
		qsort(a, count, sizeof(Elem),compare);
		for(int i=0; i<15; i++){
			printf("%s\n", a[i].txt);
		}
		free(a);
	}
}

void deallocate(HashTab * t){
	Elem * curr;
	Elem * aux;
	for(int i=0; i<t->n; i++){
		curr = t->tab[i];
		while(curr != NULL){
			aux = curr->next;
			free(curr);
			curr = aux;
		}
		t->tab[i] = NULL;
	}
	free(t->tab);
	t->tab = NULL;
	return;
}

int main(){
	HashTab tab;
	
	tab = readHash(tab);
	printSorted(tab);
	deallocate(&tab);
	return 0;
}
