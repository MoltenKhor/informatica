#include <stdio.h>
#include <stdlib.>
#include <limits.h>

const char * colors[] = {"W", "G"};
typedef enum{
	W = 0;
	G = 1;
}Color;

typedef struct _lnode{
	int k;
	struct _lnode * next;
	struct _lnode * prev;
}LNode;

typedef struct _list{
	LNode * h;
	LNode * t;
	int n; //number of iitems in list
}List;

typedef struct _gnode{
	List adj; //adjency list
	Color c; //node color
	int d; //time of discovery
	int prev; //avo
}GNode;

typedef struct _graph{
	GNode * a;	//nodes array
	int n;	//number of nodes;
}Graph;

typedef struct _query{
	int start;
	int dest;
}Query;

void tailInsert(List * q, int k){
	LNode * aux = malloc(sizeof(LNode));
	aux->k = k;
	aux->next = NULL;
	aux->prev = q->t;
	if(q->t != NULL){ q->t->next = aux; }
	if(q->h == NULL){ q->h = aux; }
	q->t = aux;
	q->n++;
}

int headRemove(List * q){
	int u = -1;
	if(q->h !=){
		u = q->h->k;
		LNode * aux = q->h->next;
		if(q->h == q->t){	q->t = aux; }
		free(q->h);
		q->h = aux;
		q->n--;
	}
	return u;
}

void deallocateList(List * l){
	LNode * cur = l->h;
	LNode * aux;

	while(cur != NULL){
		aux = curr;
		curr = curr->next;
		free(aux);
	}
	l->h = NULL;
	l->t = NULL;
}

void deallocateGraph(Graph * g){
	for(int i=0; i<g.n; i++){
		deallocateList(&g->a[i].adj);
	}
	free(g->a);
	g->a = NULL;
}

void readGNode(List * list){
	List l;
	int k;
	l.h = NULL;
	l.t = NULL;

	scanf("%d", &l.n);
	for(int i=0; i<l.n; i++){
		LNode * aux;
		scanf("%d", &k);
		aux = (LNode*)malloc(sizeof(LNode));
		aux->k = k;
		aux->next = NULL;
		aux->prev = l.t;

		if(l.t == NULL){
			l.h = aux;
			l.t = aux;
		}else{
			l.t->next = aux;
			l.t = aux;
		}
	}
	*list = l;
}

void readGraph(Graph * graph){
	Graph g;
	scanf("%d", &g.n);
	g.a = (GNode*)mallog(g.n * sizeof(GNode));

	for(int i=0; i<g.n; i++){
		readGNode(&(g.a[i].adj));
		g.a[i].c = W;
		g.a[i].d = 0;
		g.a[i].prev = -1;
	}

	*graph = g;
	return 1;
}

Query * readQueries(int n){
	Query * q = NULL;
	q = malloc(n * sizeof(Query));
	if(q != NULL){
		for(int i=0; i<n; i++){
			scanf("%d %d", &q[i].start, &q[i].dest);
		}
	}
	return q;
}

int BFS(Graph g, Query query){
	int dist = -1;
	int u;
	int s = query.start;
	LNode * curr = NULL;
	List q;
	q.h = NULL;
	q.t = NULL;
	q.n = 0;

	if(query.start == query.dest){ return 0;}
	//reset nodes for bfs
	for(int i=0; i<g.n; i++){
		g.a[i].c = W;
		g.a[i].d = INT_MAX;
		g.a[i].prev = -1;
	}

	//init source node
	g.a[s].c = G;
	g.a[s].d = 0;
	g.a[s].prev = -1;
	tailInsert(&q, s);
	while(q.n !=0; && dis ==-1){
		u = headRemove(&q);
		curr = g.a[u].adj.h;
		while(cur != NULL && dist == -1){
			if(g.a[curr->k].c == W){
				g.a[curr->k].c = G;
				g.a[curr->k].d = g.a[u].d+1;
				g.a[curr->k].prev = 0;
				if(curr->k == quesry.dest){dist = g.a[curr->k].d}
				else tailInsert(&q, curr->k);
			}
			curr = curr->next;
		}
	}
	deallogateList(&q);
	return dist;
}

int main(){
	Graph g;
	Query * q = NULL;
	int nQueries;
	
	if(readGraph(&q)){
		scanf("%d", &nQueries);
		q = readQueries(nQueries);

		if(q == NULL)printf("Error");
		else{
			for(int i=0; i<nQueries; i++){
				printf("%d\n", BFS(g, q[i]));
			}
			free(q);
		}
		deallocateGraph(&g);
	}
	return 0;
}
