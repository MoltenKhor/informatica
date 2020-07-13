#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 101
#define MAX_NUM 21

typedef struct _node{
	char name[MAX_NAME];
	char num[MAX_NUM];
	struct _node * next;
}Node;

typedef struct _list{
	int n; //number of elements
	Node * h; //first element of list
}List;

typedef struct _hashtab{
	int n; //num di liste
	int m; //effective elements
	List * tab; //array of list
}HashTab;

int hash(char* str, int n){
	unsigned int x = 0;
	int i=0;
	while(str[i] != '\0'){
		x += str[i];
		i++;
	}
	return (x%n);
}
void insertHash(HashTab * t, char* name, char* num){
	int h = hash(name, t->n);
	Node * aux = malloc(sizeof(Node));
	strcpy(aux->name, name);
	strcpy(aux->num, num);
	aux->next=NULL;

	Node * curr = (t->tab[h]).h;
	Node * prec = NULL;

	while(curr != NULL && strcmp(name, curr->name) >=0){
		prec = curr;
		curr = curr->next;
	}
	if(prec == NULL){ //head insert
		aux->next = (t->tab[h]).h;
		(t->tab[h]).h = aux;
	}else{
		aux->next = curr;
		prec->next = aux;
	}

}
HashTab readTab(){
	HashTab t;
	int n;
	char name[MAX_NAME];
	char num[MAX_NUM];
	scanf("%d", &n);
	t.n = 2*n;
	t.m=0;
	t.tab = malloc(t.n * sizeof(List));
	for(int i = 0; i<t.n; i++){
		t.tab[i].n = 0;
		t.tab[i].h = NULL;
	}
	for(int i=0; i<n; i++){
		scanf("%s", name);
		scanf("%s", num);
		insertHash(&t, name, num);
	}
}

void print(HashTab t, int k){
	if(k<0 || k >=t.n) return;
	Node * curr = t.tab[k].h;
	while(curr != NULL){
		printf("%s %s\n", curr->name, curr->num);
		curr = curr->next;
	}
}

int main(){
	HashTab tab;
	int k;
	tab = readTab();
	scanf("%d", &k);
	print(tab, k);

	Node * curr;
	Node *aux;
	for(int i=0; i<tab.n; i++){
		curr = tab.tab[i].h;
		aux = NULL;
		while(curr != NULL){
			aux = curr->next;
			free(curr);
			curr = aux;
		}
	}
	free(tab.tab);
	return 0;
}