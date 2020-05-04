#include <stdio.h>
#include <stdlib.h>


int compare(const void * p_a, const void * p_b){
	int a = *((int*)p_a);
	int b = *((int*)p_b);

	if((a%2)==0 && (b%2)==0){
		return a-b;
	}else{
		if((a%2)!=0 && (b%2)!=0){
			return b-a;
		}if((a%2)==0){
			return -1;
		}
		return 1;
	}

}

int main(){
	int N;
	scanf("%d", &N);
	int* a;
	a = (int *) malloc(N*sizeof(int));	
	int i;
	for(i=0; i<N; i++){
		scanf("%d", &a[i]);
	}
	qsort(a, N, sizeof(int), compare);

	for(i=0; i<N; i++){
		printf("%d\n", a[i]);
	}
	free(a);
	return 0;
}
