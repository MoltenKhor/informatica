#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct _point{
	int x;
	int y;
	int c;
}Point;

typedef struct _query{
	int x1;
	int x2;
	int y1;
	int y2;
}Query;

Point * readPoints(int n){
	Point * points = NULL;
	points = (Point*)malloc(n*sizeof(Point));
	if(points == NULL){ printf("BAD Points ALLOCATION\n"); 
	}else{
		for(int i=0; i<n; i++){
			scanf("%d %d %d", &points[i].x, &points[i].y, &points[i].c);
		}	
	}
	return points;
}

Query * readQueries(int m){
	Query * q = NULL;
	q = (Query*)malloc(m*sizeof(Query));
	if(q == NULL){ printf("BAD Query ALLOCATION\n");
	}else{
		for(int i=0; i<m; i++){
			scanf("%d %d %d %d", &q[i].x1, &q[i].y1, &q[i].x2, &q[i].y2);
		}
	}
	return q;
}

int compare(const void * p_a, const void * p_b){
	Point a = *((Point*)p_a);
	Point b = *((Point*)p_b);
	return a.c-b.c;
}

int isPointInsideQuery(Point p, Query	q){
	return (q.x1 <= p.x && p.x <= q.x2) && (q.y1 <= p.y && p.y <= q.y2);
}

int countColors(Query  q, Point * p, int n){
	int nMatch = 0;
	int index = -1;
	for(int i=0; i<n; i++){
		if(isPointInsideQuery(p[i], q)){
			if(index == -1){
				nMatch++;
				index = i;
			}else{
				if(p[i].c != p[index].c){
					nMatch++;
					index = i;
				}
			}
		}
	}
	return nMatch;
}

int main(){
	int N, M;
	scanf("%d %d", &N, &M);
	Point *p;
	Query *q;
	p=readPoints(N);
	q=readQueries(M);

	if(p != NULL && q != NULL){
		qsort(p, N, sizeof(Point), compare);
	}

	for(int i=0; i<M; i++){
		printf("%d\n", countColors(q[i], p, N));
	}

	if(p!=NULL){ free(p); }
	if(q!=NULL){ free(q); }

	return 0;
}
