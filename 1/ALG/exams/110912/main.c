#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>


#define MAX_LEN 101

typedef struct _patient{
	char name[MAX_LEN];
	struct _patient * next;
}Patient;

typedef struct _pqueue{
	Patient * h;	//head
	Patient * t;	//tail
	int n; //patient in q
}PQueue;

void addPatient(PQueue * q){
	PQueue aux = *q;
	Patient * p = malloc(sizeof(Patient));
	scanf("%s", p->name);
	p->next = NULL;
	if(aux.h == NULL){
		aux.h = p;
		aux.t = p;
	}else{
		aux.t->next = p;
		aux.t = p;
	}
	*q = aux;
}

void removePatient(PQueue * q){
	PQueue aux = *q;
	if(aux.h != NULL){
		if(aux.h->next == NULL){
			free(aux.h);
			aux.h = NULL;
			aux.t = NULL;
		}else{
			Patient * p = aux.h->next;
			free(aux.h);
			aux.h = p;
		}
	}
	*q = aux;
}

void printArray(char** a, int n){
	for(int i=0; i<n; i++){
		printf("%s\n", a[i]);
	}
	printf("&\n");
}

int qname(const void * a, const void * b){
	char * x = *((char**)a);
	char * y = *((char**)b);
	return strcmp(x,y);
}

void sortPrint(PQueue q){
	Patient * curr = q.h;
	char ** a = malloc(q.n*sizeof(char*));
	for(int i=0; i<q.n; i++){
		a[i] = malloc(MAX_LEN*sizeof(char));
		a[i] = curr->name;
		curr = curr->next;
	}
	qsort(a, q.n, sizeof(char*), qname);
	printArray(a,q.n);
	for(int i=0; i<q.n; i++) free(a[i]);
	free(a);
}

int main(){
	PQueue queue;
	queue.h = NULL;
	queue.t = NULL;
	queue.n = 0;
	int e=0;

	do{
		scanf("%d" ,&e);
		if(e==1){
			addPatient(&queue);
			queue.n++;
		}else if(e==2){
			if(queue.h != NULL){
				removePatient(&queue);
			}
		}
	}while(e != 0);
	sortPrint(queue);
	return 0;
}
