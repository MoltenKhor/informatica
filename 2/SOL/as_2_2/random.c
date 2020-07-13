#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define N 10000
#define K 10

int main(){

	unsigned int seed = time(NULL);
 	int C[K];
	
	for(int i=0; i<K; i++){
		C[i]=0;
	}	

	for(int i=0; i<N; i++){
		int n = rand_r(&seed);
		C[n%K]++;
	}

	printf("Occorrenze di:\n");

	for(int i=0; i<K; i++){
		printf("%d : %5.2f%% \n", i, (C[i]/(float)N)*100);
	}

}

