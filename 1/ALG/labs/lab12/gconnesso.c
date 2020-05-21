#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

const char * colors[] = {"W", "G"};
typedef enum{
	W = 0;
	G = 1;
}Color;

typedef struct _list{
	LNode * h;
	LNode * t;
	int n;
}List;

typedef struct _lNode{
	struct _lNode * prev;
	struct _lNode * next;
	int k;
}LNode;

typedef struct _node{
	List adj;
	Color c;
	int d;
	int prev;
}GNode;

typedef struct _graph{
	GNode * a;
	int n;
}Graph;

void readNodes(List list){
	List l;
	int k;
	l.h = NULL;
	l.t = NULL;
	scanf("%d", l.n);
	for(int i=0; i<l.n; i++){
		LNode * aux;
		scanf("%d", &k);
		aux = (LNode*) malloc(sizeof(LNode));
		aux->k = k;
		aux->next = NULL;
	 	aux->prev = l.t;
		if(l.t == NULL){
			l.t = aux;
			l.h = aux;
		}else{
			l.t->next = aux;
			l.h = aux;
		}	
	}
	*list = l;
}

int readGraph(Graph graph){
	Graph g;
	scnaf("%d", &g.n);
	for(int i=0; i<g.n; i++){
		readNodes(&(g.a[i].adj));
		g.a[i].c = W;
		g.a[i].d = 0;
		g.a[i].prev = -1;
	}
	*graph = g;
	return 1;
}

void deallocateList(List * l){
	LNode * curr = l->h;
	LNode * aux;
	while(curr != NULL){
		aux = curr;
		curr = curr->next;
		free(aux);
	}

	l->h = NULL;
	l->t = NULL;
}

void tailInsert(List * q, int k){
	LNode * aux = malloc(sizeof(LNode));
	aux->k = k;
	aux->next = NULL;
	aux->prev = q->t;
	if(q->t != NULL) q->t->next = aux;
	if(q->h == NULL) q->h = aux;
	q->t = aux;
	q->n++;
}

int tailRemove(List * q){
	int u = -1;
	if(q->t != NULL){
		u = q->t->k;
		LNode * aux = q->t->prev;
		if(q->h == q->t) q->h = aux;
		free(q->t);
		q->t = aux;
		if(q->t != NULL) q->t->next = NULL;
		q->n--;
	}
	return u;
}

void deallocateGpraph(Graph * g){
	for(int i=0; i<g->n; i++){
		deallocateList(&(g->a[i].adj));
	}
	free(g->a);
	g->a = NULL;
}

void BFS(Graph g, int s){
	int isBipartite = 1;
	int u;
	LNode * curr = NULL;
	List q;

	q.h = NULL;
	q.t = NULL;
	q.n = 0;

	g.a[s].c = G;
	g.a[s].d = 0;
	g.a[s].prev = -1;
	tailInsert(&q,s);
	while(q.n != 0 && isBipartite==1){
		u = tailRemove(&q);
		curr = g.a[u].adj.h;
		if(g.a[curr->k].c == W){
			g.a[curr->k].c = G;
			g.a[curr->k].d =g.a[u].d+1;
			g.a[curr->k].prev = u;
			tailInsert(&q, curr->k);
		}
		curr = curr->next;
	}
	deallocateList(&q);
}

int isLinked(Graph g){
	for(int i=0; i<g.n; i++){
		g.a[i].c = W;
		g.a[i].d = INT_MAX;
		g.a[i].prev = -1;
	}
	for(int i=0; i<g.n; i++){
		if(g.a[i].c == W){
			if(i>0) return 0;
			else BFS(g, i);
		}
	}
	return 1;
}

int main(){
	Graph g;
	if(readGraph(&g)){
		printf("%d", isLinked(&d));
		deallocateGraph(&g);
	}
	return 0;
}
