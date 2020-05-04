#include <stdio.h>
#include <stdlib.h>

typedef struct _point{
	int x;
	int y;
}Point;

int counting(const void * p_a, const void * p_b){
	Point a = *((Point *)p_a);
	Point b = *((Point *)p_b);
	if(a.x == b.x){
		return b.y-a.y;
	}else{
		return a.x - b.x;
	}
}

int main(){
	Point *a;
	int n;
	scanf("%d", &n);
	int i;
	a = (Point*)malloc(n * sizeof(Point));
	for(i=0; i<n; i++){
		scanf("%d %d", &(a[i].x), &(a[i].y));
	}

	qsort(a, n, sizeof(Point), counting);
	for(i=0; i<n; i++){
		printf("%d %d\n", a[i].x, a[i].y);
	}
}
