#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 101

typedef struct _item{
	char txt[MAX_LEN];
	int val;
	struct _item * next;
}Item;

typedef struct _hashtab{
	int n; //number of lists
	Item **tab;
}HashTab;

int hash(char* str, int n){
	unsigned x=0;
	int i=0;
	while(str[i] != '\0'){
		x += s[i];
		i++;
	}
	return (x%n);
}

HashTab insertItem(HashTab t, char *name, int value){
	int h = hash(name, t.n);
	Item * curr = t.tab[h];
	while(curr != NULL){
		if(strcmp(name, curr->txt)==0){
			if(value > curr->val){
				curr->val = value;
				return t;
			}else{
				return t;
			}
		}
		curr = curr->next;
	}
	//item not found already existing
	Item * item = malloc(sizeof(Item));
	item->val = value;
	strcpy(item->txt, name);
	item->next = t.tab[h];
	t.tab[h] = item;
	return t;
}

HashTab readTab(HashTab t){
	char name[MAX_LEN];
	int value;
	int n;
	scanf("%d", &n);
	t.n = 2*n;
	t.tab =(Item**) malloc(t.n*sizeof(Item*));

	for(int i=0; i<t.n; i++){
		t.tab[i] = NULL;
	}

	for(int i=0; i<n; i++){
		scanf("%s", name);
		scanf("%d", &value);
		t=insertItem(t, name, value);
	}
	return t;
}

int compare(const void * a, const void * b){
	Item x = *((Item*)a);
	Item y = *((Item*)b);
	
	if(x.val > x.val) return x.val - y.val;
	else return y.val - x.val;
}

void printSortedTab(HashTab t){
	int count = 0;
	Item * curr = NULL;
	Item * a;
	if(t.tab == NULL) return;

	for(int i=0; i<t.n; i++){
		curr = t.tab[i];
		while(curr != NULL){
			count++;
			curr = curr->next;
		}
	}

	if(count > 0){
		a = malloc(count*sizeof(Item));
		int j=0;
		for(int i=0; i<t.n && j<count; i++){
			curr = t.tab[i];
			while(curr!=NULL){
				a[j].val = curr->val;
				strcpy(a[j].txt, curr->txt);
				curr=curr->next;
				j++;
			}
		}
		qsort(a,count, sizeof(Item), compare);
		for(int i=0; i<15; i++){
			printf("%s\n", a[i].txt);
		}
	}
	
}

void deallocate(HashTab t){
	Item * curr;
	Item * aux;
	for(int i=0; i<t.n; i++){
		curr = t.tab[i];
		while(curr != NULL){
			aux = curr->next;
			ree(curr);
			curr = aux;
		}
		t.tab[i] = NULL;
	}
	free(t.tab);
	t.tab = NULL;
}

int main(){
	HashTab tab;
	tab = readTab(tab);
	printSortedTab(tab);
	deallocate(tab);
	return 0;
}