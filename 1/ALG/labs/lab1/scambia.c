#include <stdio.h>

int main(){
	int numeri[10000];
	int N;
	scanf("%d", &N);
	int i=0;
	for(i; i<N; i++){
		scanf("%d", &numeri[i]);		
	}

	for(i=0; i<(N/2); i++){
		int tmp;
		tmp = numeri[N-1-i];
		numeri[N-1-i]=numeri[i];
		numeri[i]=tmp;
	}

	for(i=0; i<N; i++){
		printf("%d\n", numeri[i]);
	}

	return 0;
}
